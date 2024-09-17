#include "mainwindow.h"
#include "Logger.hpp"
#include "common.hpp"
#include "ui_mainwindow.h"
#include <QPlainTextEdit>
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), tempui(nullptr),
    distui(nullptr), batui(nullptr), speedui(nullptr) {
    diagnosticsObj.setLimits(this->limits);
    ui->setupUi(this);

    ui->SaveLoggerName->setEnabled(false); // Disable the "Save" button
    timer = new QTimer(this);
    timer2 = new QTimer(this);
    timer2->stop();
    timer->stop();

    connect(ui->LoggerFileName, &QPlainTextEdit::textChanged, this,
            &MainWindow::checkLogFilename); // Check filename entry
    connect(ui->SaveLoggerName, &QPushButton::clicked, this,
            &MainWindow::loggerUpdatePath);

    connect(timer, &QTimer::timeout, this, &MainWindow::updateTemp);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateSpeed);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateDistance);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateBat);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateRpm);
    connect(timer2, &QTimer::timeout, this, &MainWindow::runAcc);
    connect(timer2, &QTimer::timeout, this, &MainWindow::runDiag);

    /**
   *
   *
   *
   *
   */
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    mSpeedGauge = new QcGaugeWidget;
    mSpeedGauge->addBackground(99);
    QcBackgroundItem *bkg1 = mSpeedGauge->addBackground(92);
    bkg1->clearrColors();
    bkg1->addColor(0.1, Qt::black);
    bkg1->addColor(1.0, Qt::white);

    QcBackgroundItem *bkg2 = mSpeedGauge->addBackground(88);
    bkg2->clearrColors();
    bkg2->addColor(0.1, Qt::gray);
    bkg2->addColor(1.0, Qt::darkGray);

    mSpeedGauge->addArc(60);
    mSpeedGauge->addArc(59);
    mSpeedGauge->addArc(58);
    mSpeedGauge->addArc(57);
    mSpeedGauge->addArc(56);


    auto ii = mSpeedGauge->addDegrees(65);
    ii->setValueRange(0,300);
    ii->setStep(10);
    mSpeedGauge->update();

    ii = mSpeedGauge->addDegrees(70);
    ii->setValueRange(0,300);
    ii->setStep(20);
    mSpeedGauge->update();

    auto Item = mSpeedGauge->addValues(80);
    Item->setValueRange(0, 300); // Set minimum and maximum range
    Item->setStep(20);           // Set step size

    // Update the gauge to apply changes
    mSpeedGauge->update();
    mSpeedGauge->addColorBand(50);
    // mSpeedGauge->addValues(90)->setValueRange(0,180);

    mSpeedGauge->addLabel(70)->setText("Km/h");
    QcLabelItem *lab = mSpeedGauge->addLabel(40);
    lab->setText("0");
    mSpeedNeedle = mSpeedGauge->addNeedle(60);
    mSpeedNeedle->setLabel(lab);
    mSpeedNeedle->setColor(Qt::white);
    mSpeedNeedle->setValueRange(0, 300);
    mSpeedGauge->addBackground(7);
    mSpeedGauge->addGlass(88);
    ui->_SpeedGauge->addWidget(mSpeedGauge);
    /**
   *
   *
   *
   *
   */
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    mRpmGauge = new QcGaugeWidget;
    mRpmGauge->addBackground(99);
    QcBackgroundItem *bkg3 = mRpmGauge->addBackground(92);
    bkg3->clearrColors();
    bkg3->addColor(0.1, Qt::black);
    bkg3->addColor(1.0, Qt::white);

    QcBackgroundItem *bkg4 = mRpmGauge->addBackground(88);
    bkg4->clearrColors();
    bkg4->addColor(0.1, Qt::gray);
    bkg4->addColor(1.0, Qt::darkGray);

    mRpmGauge->addArc(55);
    mRpmGauge->addArc(54);
    mRpmGauge->addArc(53);
    mRpmGauge->addArc(52);
    mRpmGauge->addArc(51);

    auto Item2 = mRpmGauge->addDegrees(65);
    Item2->setValueRange(0, 6);
    Item2->setStep(1);
    mRpmGauge->update();

    Item2 = mRpmGauge->addDegrees(60);
    Item2->setValueRange(0, 600);
    Item2->setStep(10);
    mRpmGauge->update();

    // Configure values for the gauge
    auto Item3 = mRpmGauge->addValues(80);
    Item3->setValueRange(0, 6);
    Item3->setStep(1);
    mRpmGauge->update();

    mRpmGauge->addLabel(70)->setText("x1000");


    QcLabelItem *lab2 = mRpmGauge->addLabel(40);
    lab2->setText("0");
    mRpmNeedle = mRpmGauge->addNeedle(60);
    mRpmNeedle->setLabel(lab2);
    mRpmNeedle->setColor(Qt::white);
    mRpmNeedle->setValueRange(0, 6);
    mRpmGauge->addBackground(7);
    mRpmGauge->addGlass(88);
    ui->_RPM->addWidget(mRpmGauge);
    /**
   *
   *
   *
   *
   */
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    mTempGauge = new QcGaugeWidget;
    mTempGauge->addBackground(60);
    QcBackgroundItem *bkg5 = mTempGauge->addBackground(53);
    bkg5->clearrColors();
    bkg5->addColor(0.1, Qt::black);
    bkg5->addColor(1.0, Qt::white);

    QcBackgroundItem *bkg6 = mTempGauge->addBackground(49);
    bkg6->clearrColors();
    bkg6->addColor(0.1, Qt::gray);
    bkg6->addColor(1.0, Qt::darkGray);


    mTempGauge->addArc(30);
    auto Item4 = mTempGauge->addDegrees(35);
    Item4->setValueRange(-40, 125);
    Item4->setStep(15);
    mTempGauge->update();

    // Configure values for the gauge
    auto Item5 = mTempGauge->addValues(42);
    Item5->setValueRange(-40, 125);
    Item5->setStep(15);
    mTempGauge->update();

    mTempGauge->addColorBand(15);
    mTempGauge->addLabel(40)->setText("C");

    QcLabelItem *lab3 = mTempGauge->addLabel(25);
    lab3->setText("0");
    mTempNeedle = mTempGauge->addNeedle(40);
    mTempNeedle->setLabel(lab3);
    mTempNeedle->setColor(Qt::white);
    mTempNeedle->setValueRange(-40, 125);
    mTempGauge->addBackground(7);
    mTempGauge->addGlass(30);
    mTempNeedle->setCurrentValue(-40);
    ui->_Temp->addWidget(mTempGauge);

    /**
   *
   *
   *
   *
   */
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    mBatPercGauge = new QcGaugeWidget;
    mBatPercGauge->addBackground(60);
    QcBackgroundItem *bkg7 = mBatPercGauge->addBackground(53);
    bkg7->clearrColors();
    bkg7->addColor(0.1, Qt::black);
    bkg7->addColor(1.0, Qt::white);

    QcBackgroundItem *bkg8 = mBatPercGauge->addBackground(49);
    bkg8->clearrColors();
    bkg8->addColor(0.1, Qt::gray);
    bkg8->addColor(1.0, Qt::darkGray);

    mBatPercGauge->addArc(30);
    Item4 = mBatPercGauge->addDegrees(35);
    Item4->setValueRange(0, 100);
    Item4->setStep(10);
    mBatPercGauge->update();

    // Configure values for the gauge
    Item5 = mBatPercGauge->addValues(42);
    Item5->setValueRange(0, 100);
    Item5->setStep(10);
    mBatPercGauge->update();
    mBatPercGauge->addColorBand(15);
    mBatPercGauge->addLabel(40)->setText("%");

    QcLabelItem *lab4 = mBatPercGauge->addLabel(25);
    lab4->setText("0");
    mBatPercNeedle = mBatPercGauge->addNeedle(40);
    mBatPercNeedle->setLabel(lab4);
    mBatPercNeedle->setColor(Qt::white);
    mBatPercNeedle->setValueRange(0, 100);
    mBatPercGauge->addBackground(7);
    mBatPercGauge->addGlass(30);
    ui->_Bat_Perc->addWidget(mBatPercGauge);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::updateSpeed() {
    int speed = std::stoi(speedSensor.getValue());
    mSpeedNeedle->setCurrentValue(speed);
}

void MainWindow::updateTemp() {
    mTempNeedle->setCurrentValue(std::stoi(tempSensor.getValue()));
}

void MainWindow::updateDistance() {
    int dist = std::stoi(distSensor.getValue()); // Get distance value
    ui->Radar->display(dist);                    // Display distance on your Radar
}

void MainWindow::updateBat() {
    auto value = batSensor.getValue();
    int intValue = 0;

    intValue = std::stoi(value);
    mBatPercNeedle->setCurrentValue(intValue);

    auto it = std::find(value.begin(), value.end(), '%');
    if (it != value.end()) {
        value.erase(0, std::distance(value.begin(), it + 1));
        intValue = std::stoi(value);
    }
    ui->BatteryTemp->display(intValue);
}
void MainWindow::updateRpm() {
    int Rpm = std::stoi(rpmSensor.getValue());
    mRpmNeedle->setCurrentValue(Rpm);
}
void MainWindow::runAcc() {
    Acc.tackAction(tempSensor, distSensor, speedSensor);
}

void MainWindow::loggerUpdatePath() {
    std::string filePath = (ui->LoggerFileName->toPlainText()).toStdString();

    // Set the log path using Logger instance
    Logger::getInstance().setPath(filePath);

    // Start the timer once the log file path is set
    timer->start(50);
    timer2->start(1);
}

void MainWindow::runDiag() {
    ////////////////////////////////////////////////////////////////////////////////////
    auto diagResult = diagnosticsObj.runDiagnostics(batSensor, sensorsName[0]);
    auto diagResult2 = diagnosticsObj.runDiagnostics(batSensor, sensorsName[1]);
    if (diagResult != common::ErrorCodes::NORMAL || diagResult2 != common::ErrorCodes::NORMAL) {
        if (batui == nullptr) {
            batui = new BatteryError(this);
        }
        batui->show();
    } else {
        if (batui != nullptr && batui->isVisible()) {
            batui->close();
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////
    diagResult = diagnosticsObj.runDiagnostics(distSensor, sensorsName[2]);
    if (diagResult != common::ErrorCodes::NORMAL) {
        if (distui == nullptr) {
            distui = new DistanceError(this);
        }
        distui->show();
    } else {
        if (distui != nullptr && distui->isVisible()) {
            distui->close();
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////
    diagResult = diagnosticsObj.runDiagnostics(speedSensor, sensorsName[3]);
    if (diagResult != common::ErrorCodes::NORMAL) {
        if (speedui == nullptr) {
            speedui = new SpeedError(this);
        }
        speedui->show();
    } else {
        if (speedui != nullptr && speedui->isVisible()) {
            speedui->close();
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////
    diagResult = diagnosticsObj.runDiagnostics(tempSensor, sensorsName[4]);
    if (diagResult != common::ErrorCodes::NORMAL) {

        if (tempui == nullptr) {
            tempui = new TempError(this);
        }

        tempui->show();
    } else {
        if (tempui != nullptr && tempui->isVisible()) {
            tempui->close();
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////
    diagnosticsObj.logIssue();
}

void MainWindow::checkLogFilename() {
    QString filePath = ui->LoggerFileName->toPlainText();

    // Enable the "Save" button only if the filename is not empty
    if (!filePath.isEmpty()) {
        ui->SaveLoggerName->setEnabled(true);
    } else {
        ui->SaveLoggerName->setEnabled(false);
    }
}
