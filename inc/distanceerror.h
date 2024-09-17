#ifndef DISTANCEERROR_H
#define DISTANCEERROR_H

#include <QDialog>

namespace Ui {
class DistanceError;
}

class DistanceError : public QDialog
{
    Q_OBJECT

public:
    explicit DistanceError(QWidget *parent = nullptr);
    ~DistanceError();

private:
    Ui::DistanceError *ui;
};

#endif // DISTANCEERROR_H
