#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QScreen>
#include <QResizeEvent>
#include <QLayout>
#include <QGraphicsLayout>
#include <numeric> // std::accumulate用


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serial(new QSerialPort(this))
    , timer(new QTimer(this))
    , displayTimer(new QTimer(this))
{
    ui->setupUi(this);

    setWindowTitle("LuLo");

    baseSize = this->size(); // 初期ウィンドウサイズ（Qt Designerで設定したサイズ）を保存
    // すべてのウィジェットの初期幾何情報をマップに登録
    const auto widgets = this->findChildren<QWidget*>();
    for (auto *widget : widgets) {
        widgetBaseGeometry[widget] = widget->geometry();
    }
    for (auto *widget : widgets) {
        widgetInitialFontSizes[widget] = widget->font().pointSize();
    }

    // 画面解像度を取得
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int width = screenGeometry.width() * 0.6; // 幅を画面のx％に
    int height = screenGeometry.height() * 0.85; // 高さを画面のy％に

    // MainWindowのサイズを設定
    this->resize(width, height);

    ui->lineEditRecordingTime->setAlignment(Qt::AlignRight);
    ui->lineEditRecordingTime->setText("5.0");
    ui->lineEditBaudRate->setAlignment(Qt::AlignRight);
    ui->lineEditBaudRate->setText("9600");
    ui->lineEditDisplayInterval->setAlignment(Qt::AlignRight);
    ui->lineEditDisplayInterval->setText("0.1");

    // 利用可能なシリアルポートをcomboBoxに追加
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->comboBoxPortName->addItem(info.portName(), info.portName());
    }

    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readFromSerial);
    connect(timer, &QTimer::timeout, this, &MainWindow::on_pushButtonLogStart_clicked);
    connect(timer, &QTimer::timeout, this, &MainWindow::readFromSerial); // タイマーのtimeoutシグナルをreadFromSerialスロットに接続
    connect(ui->pushButtonLogStop, &QPushButton::clicked, this, &MainWindow::on_pushButtonLogStop_clicked);

    setupChart(); // チャートのセットアップ

    setTabOrder(ui->comboBoxPortName, ui->lineEditBaudRate);
    setTabOrder(ui->lineEditBaudRate, ui->lineEditRecordingTime);
    setTabOrder(ui->lineEditRecordingTime, ui->pushButtonLogStart);
    setTabOrder(ui->pushButtonLogStart, ui->pushButtonLogStop);
    setTabOrder(ui->pushButtonLogStop, ui->pushButtonOutputData);
    setTabOrder(ui->pushButtonOutputData, ui->pushButtonSelectFile);
    setTabOrder(ui->pushButtonSelectFile, ui->lineEditDisplayInterval);
    setTabOrder(ui->lineEditDisplayInterval, ui->pushButtonStartDisplay);
    setTabOrder(ui->pushButtonStartDisplay, ui->pushButtonStopDisplay);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    const QSize newSize = event->size();
    const qreal widthRatio = static_cast<qreal>(newSize.width()) / baseSize.width();
    const qreal heightRatio = static_cast<qreal>(newSize.height()) / baseSize.height();
    qreal sizeRatio = std::sqrt(widthRatio * heightRatio); // 面積の比に基づく平均的なサイズ比


    for (auto it = widgetBaseGeometry.begin(); it != widgetBaseGeometry.end(); ++it) {
        QWidget *widget = it.key();
        const QRect &baseGeometry = it.value();

        QRect newGeometry(
            baseGeometry.x() * widthRatio,
            baseGeometry.y() * heightRatio,
            baseGeometry.width() * widthRatio,
            baseGeometry.height() * heightRatio
            );

        widget->setGeometry(newGeometry);
    }

    for (auto *widget : findChildren<QWidget*>()) {
        int initialFontSize = widgetInitialFontSizes.value(widget, 10); // デフォルト値を10に設定
        QFont font = widget->font();
        int newFontSize = std::max(1, static_cast<int>(initialFontSize * sizeRatio)); // 最小フォントサイズを5に設定
        font.setPointSize(newFontSize);
        widget->setFont(font);
    }

//    chartView->resize(ui->widgetLvGraph->size());
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        QWidget *focusWidget = this->focusWidget();
        if (focusWidget) {
            QPushButton *button = dynamic_cast<QPushButton *>(focusWidget);
            if (button) {
                button->click();
            }
        }
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::on_pushButtonLogStart_clicked()
{
    setupSerialPort(); // シリアルポートの設定

    bool ok;
    double durationInSeconds = ui->lineEditRecordingTime->text().toDouble(&ok);
    if (!ok || durationInSeconds <= 0) {
        // エラー処理: durationが正の数値に変換できない
        ui->statusbar->showMessage("Invalid log duration.");
        return;
    }

    int durationInMilliseconds = static_cast<int>(durationInSeconds * 1000.0);

    // タイマーのシグナル・スロット接続を解除して、以前の接続をクリア
    timer->disconnect();

    // タイマーがすでに動作していたら停止
    if (timer->isActive()) {
        timer->stop();
    }

    // シリアルポートからの読み取りをタイマーで開始
    timer->start(durationInMilliseconds);

    // タイムアウト後にタイマーを止めるためのシグナルとスロットの接続
    connect(timer, &QTimer::timeout, this, [this, durationInMilliseconds](){
        static int elapsed = 0;
        elapsed += durationInMilliseconds;
        if (elapsed >= durationInMilliseconds) {
            timer->stop(); // タイマー停止
            ui->statusbar->showMessage("Log completed."); // ステータスバーにメッセージ表示
            serial->close(); // シリアルポートを閉じる

            // ここから平均値計算と表示のコード
            if (!lumiValues.isEmpty()) {
                double sum = std::accumulate(lumiValues.begin(), lumiValues.end(), 0.0);
                double average = sum / lumiValues.size();
                ui->labelAverageValue->setText(QString::number(average, 'f', 2)); // 小数点以下2桁で表示
                displayAverageOnChart(average); // 平均値をグラフに表示
            }
            elapsed = 0; // カウンタリセット
        }
    });

    lumiValues.clear();
}

void MainWindow::displayAverageOnChart(double average) {
    series->clear(); // ここでシリーズをクリア

    // 平均値を表示する新しいバーセットを作成
    QBarSet *averageSet = new QBarSet("Average");
    *averageSet << average; // 平均値をバーセットに追加

    // バーセットの色を設定
    averageSet->setBrush(QBrush(QColor(0, 191, 255))); // averageSet->setBrush(QBrush(QColor("#00bfff")));
//    averageSet->setBrush(QBrush(Qt::green)); // 任意の色に変更可能

//    // バーセットの境界線の色とスタイルを設定
//    averageSet->setPen(QPen(Qt::darkGreen, 2)); // 線の太さを2に設定

    // グラフに平均値のバーセットを追加
    series->append(averageSet);

    // シリーズに棒グラフの幅を設定
    series->setBarWidth(0.4); // 棒グラフの幅をカテゴリ全体の40%に設定

    // グラフの更新
    chart->removeSeries(series);
    chart->addSeries(series);
    series->attachAxis(chart->axes(Qt::Vertical).first());
    series->attachAxis(chart->axes(Qt::Horizontal).first());

    // グラフビューの再描画
    chartView->repaint();
}


void MainWindow::readFromSerial()
{
    if(serial->canReadLine()) {
        QByteArray line = serial->readLine();
        QString data = QString::fromLatin1(line).trimmed(); // データの処理とトリミング
        bool ok;
        double lumiVal = data.toDouble(&ok);
        if (ok) {
            ui->lcdNumberLumiVal->display(lumiVal); // LCDに表示
            lumiValues.push_back(lumiVal); // ベクターに輝度値を追加
//            updateChart(lumiVal); // リアルタイムで読みこんだ値をグラフに表示するとき
        }
    }
}

//void MainWindow::updateChart(double newValue)　// リアルタイムで読みこんだ値をグラフに表示するとき
//{
//    // 現在のデータを保持するQBarSetを作成
//    QBarSet *newSet = new QBarSet("Luminance");
//    *newSet << newValue; // 新しい値をQBarSetに追加

//    // 以前のバーセットを削除してから新しいセットを追加
//    series->clear();
//    series->append(newSet);

//    // グラフを更新して表示
//    chart->removeSeries(series);
//    chart->addSeries(series);
//    series->attachAxis(chart->axes(Qt::Vertical).first());
//    series->attachAxis(chart->axes(Qt::Horizontal).first());

//    // グラフビューに変更を通知
//    chartView->repaint();
//}

void MainWindow::setupChart()
{
    chart = new QChart();
    series = new QBarSeries();

    chart->addSeries(series);
//    chart->setTitle("Real time Value");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setMargins(QMargins(0, 0, 10, 0)); // setMargins(int left, int top, int right, int bottom);
    chart->setBackgroundRoundness(0);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    QStringList categories;
    // カテゴリーのリストを作成し、それに合わせてデータを追加する
    categories << "data";
    axisX->append(categories);
//    axisX->append("輝度値");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    qDebug() << "X axis setup complete.";

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 1024); // 適切な範囲に設定
    axisY->setTitleText("Value");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    qDebug() << "Y axis setup complete.";

    QVBoxLayout *layout = new QVBoxLayout(); // あるいは、必要に応じたレイアウトタイプを使用
//    layout->setContentsMargins(0, 0, 0, 0); // すべてのマージンをゼロに設定
//    layout->setSpacing(0); // スペーシングをゼロに設定

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing); // アンチエイリアスを有効化
    chartView->setMinimumSize(ui->widgetLvGraph->size()); // widgetLvGraphのサイズを最小サイズとして設定
    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(chartView); // layout に chartView を追加
    qDebug() << "ChartView added to layout.";

    ui->widgetLvGraph->setLayout(layout);
    qDebug() << "QChartView created.";
}


void MainWindow::setupSerialPort()
{
    QString selectedPortName = ui->comboBoxPortName->currentText();
    serial->setPortName(selectedPortName);
    // その他のシリアルポート設定...
    if (!serial->isOpen()) {
        if (!serial->open(QIODevice::ReadWrite)) {
            // ポートが開けなかった場合のエラー処理
            ui->statusbar->showMessage("Cannot open serial port: " + serial->portName());
            return;
        }
    }
    // lineEditBaudRateからボーレートの値を取得
    int baudRate = ui->lineEditBaudRate->text().toInt();

    // QSerialPortのsetBaudRateメソッドを使用してボーレートを設定
    serial->setBaudRate(baudRate);

    // その他のシリアルポート設定...
    if (!serial->isOpen()) {
        if (!serial->open(QIODevice::ReadWrite)) {
            // ポートが開けなかった場合のエラー処理
            ui->statusbar->showMessage("Cannot open serial port: " + serial->portName());
            return;
        }
    }
    ui->statusbar->showMessage("Serial port opened: " + serial->portName());
}


void MainWindow::on_pushButtonOutputData_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Data"), "", tr("Dat Files (*.dat);;Text Files (*.txt);;CSV Files (*.csv)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        // ファイルが開けなかった場合のエラー処理
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file for writing"));
        return;
    }

    QTextStream out(&file);
    for (double value : lumiValues) {
        out << value << '\n'; // ファイルに輝度値を書き込む
    }
    file.close();
}


void MainWindow::on_pushButtonLogStop_clicked()
{
    timer->stop(); // タイマーを停止
    serial->close(); // シリアルポートを閉じる
    ui->statusbar->showMessage("Logging stopped."); // ステータスバーにメッセージを表示
}


void MainWindow::on_pushButtonSelectFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Data File"), "", tr("Dat Files (*.dat);;All Files (*)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file"));
        return;
    }

    QTextStream in(&file);
    selectedLumiValues.clear(); // 既存のデータをクリア

    // ファイルの終わりまで各行を読み込む
    while (!in.atEnd()) {
        QString line = in.readLine();
        bool ok;
        double lumiValue = line.toDouble(&ok);
        if (ok) {
            selectedLumiValues.append(lumiValue); // QVectorに値を追加
        }
    }

    file.close();

    // 選択された値が正しく読み込まれたことを確認（デバッグ用）
    qDebug() << "Loaded values:" << selectedLumiValues;
}

void MainWindow::on_pushButtonStartDisplay_clicked()
{
    if (selectedLumiValues.isEmpty()) {
        QMessageBox::information(this, tr("Information"), tr("No values loaded."));
        return;
    }

    currentDisplayIndex = 0; // インデックスをリセット

    // タイマーの接続解除を確実に行う
    disconnect(displayTimer, &QTimer::timeout, nullptr, nullptr);

    connect(displayTimer, &QTimer::timeout, this, [this]() {
        if (currentDisplayIndex < selectedLumiValues.size()) {
            ui->lcdNumberLumiVal->display(selectedLumiValues[currentDisplayIndex]);
            currentDisplayIndex++;
        } else {
            displayTimer->stop(); // 値の末尾に達したら停止
            // ここで平均値の計算と表示を行う
            double sum = std::accumulate(selectedLumiValues.begin(), selectedLumiValues.end(), 0.0);
            double average = sum / selectedLumiValues.size(); // 計算の修正: lumiValues -> selectedLumiValues
            ui->labelAverageValue->setText(QString::number(average, 'f', 2)); // 小数点以下2桁で表示
            displayAverageOnChart(average); // 平均値をグラフに表示
        }
    });

    double displayRate = ui->lineEditDisplayInterval->text().toDouble();
    displayTimer->start(displayRate*1000); // 0.05秒間隔でタイマーを開始
}

void MainWindow::on_pushButtonStopDisplay_clicked()
{
    displayTimer->stop(); // タイマーを停止し、値の表示を中止
}

