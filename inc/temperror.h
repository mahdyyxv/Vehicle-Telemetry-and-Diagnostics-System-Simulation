#ifndef TEMPERROR_H
#define TEMPERROR_H

#include <QDialog>

namespace Ui {
class TempError;
}

class TempError : public QDialog
{
    Q_OBJECT

public:
    explicit TempError(QWidget *parent = nullptr);
    ~TempError();

private:
    Ui::TempError *ui;
};

#endif // TEMPERROR_H
