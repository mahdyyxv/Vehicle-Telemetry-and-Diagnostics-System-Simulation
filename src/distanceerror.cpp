#include "distanceerror.h"
#include "ui_distanceerror.h"

DistanceError::DistanceError(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DistanceError)
{
    ui->setupUi(this);
}

DistanceError::~DistanceError()
{
    delete ui;
}

