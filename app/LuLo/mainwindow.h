#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QTimer>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonLogStart_clicked();
    void on_pushButtonLogStop_clicked();
    void readFromSerial();
    void on_pushButtonOutputData_clicked();

    void on_pushButtonSelectFile_clicked();
    void on_pushButtonStartDisplay_clicked();
    void on_pushButtonStopDisplay_clicked();

private:
    Ui::MainWindow *ui;
    QSize baseSize; // ベースとなるウィンドウサイズ
    QMap<QWidget*, QRect> widgetBaseGeometry; // ウィジェットとその基本幾何情報のマップ
    QMap<QWidget*, int> widgetInitialFontSizes; // ウィジェットの初期フォントサイズを保存
    QSerialPort *serial; // このメンバ変数を追加
    QTimer *timer; // タイマーのメンバ変数を追加
    void setupSerialPort(); // シリアルポートの設定関数
    QVector<double> lumiValues; // 輝度値を保存するためのベクター

    QVector<double> selectedLumiValues;
    QTimer *displayTimer; // 表示用タイマー
    int currentDisplayIndex = 0; // 表示中の値のインデックス

    QChart *chart;
    QBarSeries *series; // 棒グラフのシリーズ
    QChartView *chartView;
    void setupChart(); // チャート設定のためのメソッド
//    void updateChart(double newValue); // リアルタイムで値をグラフに表示するとき
    void displayAverageOnChart(double average);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H
