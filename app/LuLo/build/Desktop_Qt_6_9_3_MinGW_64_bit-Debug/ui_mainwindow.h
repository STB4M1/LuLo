/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLCDNumber *lcdNumberLumiVal;
    QPushButton *pushButtonLogStart;
    QLineEdit *lineEditRecordingTime;
    QPushButton *pushButtonOutputData;
    QComboBox *comboBoxPortName;
    QLabel *labelSerialPort;
    QLabel *labelAverageValue;
    QLabel *labelRecordingTimeUnit;
    QLabel *labelRecordingTime;
    QLabel *labelAverageValueTitle;
    QLineEdit *lineEditBaudRate;
    QLabel *labelBaudRate;
    QChartView *widgetLvGraph;
    QPushButton *pushButtonLogStop;
    QPushButton *pushButtonSelectFile;
    QPushButton *pushButtonStartDisplay;
    QPushButton *pushButtonStopDisplay;
    QLabel *labelDisplayInterval;
    QLineEdit *lineEditDisplayInterval;
    QLabel *labelDisplayIntervalUnit;
    QFrame *line;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(586, 584);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        lcdNumberLumiVal = new QLCDNumber(centralwidget);
        lcdNumberLumiVal->setObjectName("lcdNumberLumiVal");
        lcdNumberLumiVal->setGeometry(QRect(30, 20, 321, 221));
        lcdNumberLumiVal->setFrameShadow(QFrame::Raised);
        lcdNumberLumiVal->setLineWidth(2);
        pushButtonLogStart = new QPushButton(centralwidget);
        pushButtonLogStart->setObjectName("pushButtonLogStart");
        pushButtonLogStart->setGeometry(QRect(220, 260, 121, 31));
        QFont font;
        font.setPointSize(11);
        pushButtonLogStart->setFont(font);
        lineEditRecordingTime = new QLineEdit(centralwidget);
        lineEditRecordingTime->setObjectName("lineEditRecordingTime");
        lineEditRecordingTime->setGeometry(QRect(30, 280, 151, 41));
        QFont font1;
        font1.setPointSize(13);
        lineEditRecordingTime->setFont(font1);
        pushButtonOutputData = new QPushButton(centralwidget);
        pushButtonOutputData->setObjectName("pushButtonOutputData");
        pushButtonOutputData->setGeometry(QRect(390, 360, 161, 51));
        QFont font2;
        font2.setPointSize(12);
        pushButtonOutputData->setFont(font2);
        comboBoxPortName = new QComboBox(centralwidget);
        comboBoxPortName->setObjectName("comboBoxPortName");
        comboBoxPortName->setGeometry(QRect(140, 340, 201, 31));
        labelSerialPort = new QLabel(centralwidget);
        labelSerialPort->setObjectName("labelSerialPort");
        labelSerialPort->setGeometry(QRect(50, 345, 81, 21));
        labelSerialPort->setFont(font);
        labelSerialPort->setAlignment(Qt::AlignCenter);
        labelAverageValue = new QLabel(centralwidget);
        labelAverageValue->setObjectName("labelAverageValue");
        labelAverageValue->setGeometry(QRect(390, 290, 161, 51));
        QFont font3;
        font3.setPointSize(20);
        labelAverageValue->setFont(font3);
        labelAverageValue->setFrameShape(QFrame::Box);
        labelAverageValue->setFrameShadow(QFrame::Raised);
        labelAverageValue->setLineWidth(3);
        labelAverageValue->setAlignment(Qt::AlignCenter);
        labelRecordingTimeUnit = new QLabel(centralwidget);
        labelRecordingTimeUnit->setObjectName("labelRecordingTimeUnit");
        labelRecordingTimeUnit->setGeometry(QRect(190, 290, 21, 31));
        labelRecordingTimeUnit->setFont(font3);
        labelRecordingTime = new QLabel(centralwidget);
        labelRecordingTime->setObjectName("labelRecordingTime");
        labelRecordingTime->setGeometry(QRect(50, 250, 111, 31));
        QFont font4;
        font4.setPointSize(10);
        labelRecordingTime->setFont(font4);
        labelRecordingTime->setAlignment(Qt::AlignCenter);
        labelAverageValueTitle = new QLabel(centralwidget);
        labelAverageValueTitle->setObjectName("labelAverageValueTitle");
        labelAverageValueTitle->setGeometry(QRect(380, 260, 181, 21));
        labelAverageValueTitle->setFont(font);
        labelAverageValueTitle->setAlignment(Qt::AlignCenter);
        lineEditBaudRate = new QLineEdit(centralwidget);
        lineEditBaudRate->setObjectName("lineEditBaudRate");
        lineEditBaudRate->setGeometry(QRect(140, 380, 201, 31));
        lineEditBaudRate->setFont(font4);
        labelBaudRate = new QLabel(centralwidget);
        labelBaudRate->setObjectName("labelBaudRate");
        labelBaudRate->setGeometry(QRect(50, 385, 81, 21));
        labelBaudRate->setFont(font);
        labelBaudRate->setAlignment(Qt::AlignCenter);
        widgetLvGraph = new QChartView(centralwidget);
        widgetLvGraph->setObjectName("widgetLvGraph");
        widgetLvGraph->setGeometry(QRect(380, 10, 201, 241));
        pushButtonLogStop = new QPushButton(centralwidget);
        pushButtonLogStop->setObjectName("pushButtonLogStop");
        pushButtonLogStop->setGeometry(QRect(220, 300, 121, 31));
        pushButtonLogStop->setFont(font);
        pushButtonSelectFile = new QPushButton(centralwidget);
        pushButtonSelectFile->setObjectName("pushButtonSelectFile");
        pushButtonSelectFile->setGeometry(QRect(221, 470, 91, 31));
        QFont font5;
        font5.setPointSize(9);
        pushButtonSelectFile->setFont(font5);
        pushButtonStartDisplay = new QPushButton(centralwidget);
        pushButtonStartDisplay->setObjectName("pushButtonStartDisplay");
        pushButtonStartDisplay->setGeometry(QRect(330, 470, 91, 31));
        pushButtonStopDisplay = new QPushButton(centralwidget);
        pushButtonStopDisplay->setObjectName("pushButtonStopDisplay");
        pushButtonStopDisplay->setGeometry(QRect(441, 470, 91, 31));
        labelDisplayInterval = new QLabel(centralwidget);
        labelDisplayInterval->setObjectName("labelDisplayInterval");
        labelDisplayInterval->setGeometry(QRect(220, 509, 111, 31));
        labelDisplayInterval->setFont(font);
        labelDisplayInterval->setAlignment(Qt::AlignCenter);
        lineEditDisplayInterval = new QLineEdit(centralwidget);
        lineEditDisplayInterval->setObjectName("lineEditDisplayInterval");
        lineEditDisplayInterval->setGeometry(QRect(340, 510, 171, 31));
        lineEditDisplayInterval->setFont(font4);
        labelDisplayIntervalUnit = new QLabel(centralwidget);
        labelDisplayIntervalUnit->setObjectName("labelDisplayIntervalUnit");
        labelDisplayIntervalUnit->setGeometry(QRect(520, 520, 21, 21));
        QFont font6;
        font6.setPointSize(16);
        labelDisplayIntervalUnit->setFont(font6);
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(20, 430, 551, 20));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 460, 131, 31));
        label->setFont(font2);
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 586, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButtonLogStart->setText(QCoreApplication::translate("MainWindow", "Log Start", nullptr));
        pushButtonOutputData->setText(QCoreApplication::translate("MainWindow", "Output Log data", nullptr));
        labelSerialPort->setText(QCoreApplication::translate("MainWindow", "Serial Port", nullptr));
        labelAverageValue->setText(QString());
        labelRecordingTimeUnit->setText(QCoreApplication::translate("MainWindow", "s", nullptr));
        labelRecordingTime->setText(QCoreApplication::translate("MainWindow", "Recording Time", nullptr));
        labelAverageValueTitle->setText(QCoreApplication::translate("MainWindow", "Average Value", nullptr));
        labelBaudRate->setText(QCoreApplication::translate("MainWindow", "Baud Rate", nullptr));
        pushButtonLogStop->setText(QCoreApplication::translate("MainWindow", "Log Stop", nullptr));
        pushButtonSelectFile->setText(QCoreApplication::translate("MainWindow", "Select File", nullptr));
        pushButtonStartDisplay->setText(QCoreApplication::translate("MainWindow", "Start Display", nullptr));
        pushButtonStopDisplay->setText(QCoreApplication::translate("MainWindow", "Stop Display", nullptr));
        labelDisplayInterval->setText(QCoreApplication::translate("MainWindow", " Display Interval", nullptr));
        labelDisplayIntervalUnit->setText(QCoreApplication::translate("MainWindow", "s", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Data Verification", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
