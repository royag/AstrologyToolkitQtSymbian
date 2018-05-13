#ifndef QHWTIMECHOOSER_H
#define QHWTIMECHOOSER_H

#include <QDialog>

namespace Ui {
    class QHWTimeChooser;
}

class QHWTimeChooser : public QDialog
{
    Q_OBJECT

public:
    explicit QHWTimeChooser(QWidget *parent = 0);
    ~QHWTimeChooser();

private:
    Ui::QHWTimeChooser *ui;
};

#endif // QHWTIMECHOOSER_H
