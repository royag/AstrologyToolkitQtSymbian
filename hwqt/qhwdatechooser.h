#ifndef QHWDATECHOOSER_H
#define QHWDATECHOOSER_H

#include <QFrame>

namespace Ui {
    class QHWDateChooser;
}

class QHWDateChooser : public QFrame
{
    Q_OBJECT

public:
    explicit QHWDateChooser(QWidget *parent = 0);
    ~QHWDateChooser();
signals:
    void dateSelected(int year, int month, int day);
    void cancelled();
protected slots:
    void yearDecMuch();
    void yearDecStep();
    void yearAddStep();
    void yearAddMuch();
    void monthDecMuch();
    void monthDecStep();
    void monthAddStep();
    void monthAddMuch();
    void dayDecMuch();
    void dayDecStep();
    void dayAddStep();
    void dayAddMuch();
    void done();
    void cancel();
    void changeYear(int year);
    void changeMonth(int month);
    void changeDay(int day);
protected:
    QString monthName(int month);
private:
    QAction *inpDone;
    QAction *inpCancelled;
    int maxYear;
    int minYear;
    Ui::QHWDateChooser *ui;
    int currentYear;
    int currentMonth;
    int currentDay;

};

#endif // QHWDATECHOOSER_H
