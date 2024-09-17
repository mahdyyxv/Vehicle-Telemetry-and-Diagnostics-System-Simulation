#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Battery.hpp"
#include "Diagnostics.hpp"
#include "Ecu.hpp"
#include "RadarSensor.hpp"
#include "Rpm.hpp"
#include "SpeedSensor.hpp"
#include "TempSesnor.hpp"
#include "batteryerror.h"
#include "distanceerror.h"
#include "qcguagewidget.h"
#include "speederror.h"
#include "temperror.h"
#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QTimer>
#include <QTransform>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateSpeed();
    void updateTemp();
    void updateDistance();
    void updateBat();
    void updateRpm();
    void runAcc();
    void loggerUpdatePath();
    void runDiag();
    void checkLogFilename();

private:
    std::map<std::string, std::pair<int, int>> limits = {
                                                         {"Battery Percentage", {10, 100}},
        {"Battery Temp", {0, 150}},
        {"Distance", {20, 500}},
        {"Speed", {0, 300}},
        {"Temp", {-40, 125}}};
    ;
    std::vector<std::string> sensorsName = {"Battery Percentage", "Battery Temp",
                                            "Distance", "Speed", "Temp"};
    Ui::MainWindow *ui;
    TempError *tempui;
    BatteryError *batui;
    SpeedError *speedui;
    DistanceError *distui;
    sensors::Battery batSensor;
    sensors::Radar distSensor;
    sensors::Speed speedSensor;
    sensors::Temp tempSensor;
    sensors::Rpm rpmSensor;
    Diagnostics diagnosticsObj;
    ecu::Acc Acc;
    QTimer *timer;
    QTimer *timer2;
    void rotateLabelImage(QLabel *label, int angle);

    QcGaugeWidget *mSpeedGauge;
    QcNeedleItem *mSpeedNeedle;

    QcGaugeWidget *mRpmGauge;
    QcNeedleItem *mRpmNeedle;

    QcGaugeWidget *mTempGauge;
    QcNeedleItem *mTempNeedle;

    QcGaugeWidget *mBatPercGauge;
    QcNeedleItem *mBatPercNeedle;
};
#endif // MAINWINDOW_H
