#include "batteryerror.h"
#include "ui_batteryerror.h"

BatteryError::BatteryError(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BatteryError)
{
    ui->setupUi(this);
}

BatteryError::~BatteryError()
{
    delete ui;
}

