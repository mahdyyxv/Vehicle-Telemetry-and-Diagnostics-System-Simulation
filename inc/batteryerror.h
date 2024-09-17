#ifndef BATTERYERROR_H
#define BATTERYERROR_H

#include <QDialog>

namespace Ui {
class BatteryError;
}

class BatteryError : public QDialog
{
    Q_OBJECT

public:
    explicit BatteryError(QWidget *parent = nullptr);
    ~BatteryError();


private:
    Ui::BatteryError *ui;
};

#endif // BATTERYERROR_H
