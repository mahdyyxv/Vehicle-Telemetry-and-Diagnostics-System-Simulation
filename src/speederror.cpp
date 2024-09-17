#include "speederror.h"
#include "ui_speederror.h"

SpeedError::SpeedError(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SpeedError)
{
    ui->setupUi(this);
}

SpeedError::~SpeedError()
{
    delete ui;
}
