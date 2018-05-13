#ifndef QHWTIMECHOOSER_H
#define QHWTIMECHOOSER_H

#include <QFrame>

namespace Ui {
    class QHWTimeChooser;
}

class QHWTimeChooser : public QFrame
{
    Q_OBJECT

public:
    explicit QHWTimeChooser(QWidget *parent = 0);
    ~QHWTimeChooser();
signals:
    void timeSelected(int hour, int minute);
    void cancelled();
protected slots:
    void hourDecMuch();
    void hourDecStep();
    void hourAddStep();
    void hourAddMuch();
    void minuteDecMuch();
    void minuteDecStep();
    void minuteAddStep();
    void minuteAddMuch();
    void done();
    void cancel();
    void changeHour(int year);
    void changeMinute(int month);
    void updateTimeLabel();
private:
    QAction *inpDone;
    QAction *inpCancelled;
    int currentHour;
    int currentMinute;
    Ui::QHWTimeChooser *ui;
};

#endif // QHWTIMECHOOSER_H
