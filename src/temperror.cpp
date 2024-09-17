#include "temperror.h"
#include "ui_temperror.h"

TempError::TempError(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TempError)
{
    ui->setupUi(this);
}

TempError::~TempError()
{
    delete ui;
}

