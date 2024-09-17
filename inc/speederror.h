#ifndef SPEEDERROR_H
#define SPEEDERROR_H

#include <QDialog>

namespace Ui {
class SpeedError;
}

class SpeedError : public QDialog
{
    Q_OBJECT

public:
    explicit SpeedError(QWidget *parent = nullptr);
    ~SpeedError();

private:
    Ui::SpeedError *ui;
};

#endif // SPEEDERROR_H
