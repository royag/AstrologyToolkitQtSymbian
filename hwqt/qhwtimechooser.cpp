#include "qhwtimechooser.h"
#include "ui_qhwtimechooser.h"

QHWTimeChooser::QHWTimeChooser(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::QHWTimeChooser),
    currentHour(12),
    currentMinute(0)
{
    ui->setupUi(this);

    connect(ui->btnHourLessLarge, SIGNAL(clicked()), this, SLOT(hourDecMuch()));
    connect(ui->btnHourLessStep, SIGNAL(clicked()), this, SLOT(hourDecStep()));
    connect(ui->btnHourMoreLarge, SIGNAL(clicked()), this, SLOT(hourAddMuch()));
    connect(ui->btnHourMoreStep, SIGNAL(clicked()), this, SLOT(hourAddStep()));

    connect(ui->btnMinuteLessLarge, SIGNAL(clicked()), this, SLOT(minuteDecMuch()));
    connect(ui->btnMinuteLessStep, SIGNAL(clicked()), this, SLOT(minuteDecStep()));
    connect(ui->btnMinuteMoreLarge, SIGNAL(clicked()), this, SLOT(minuteAddMuch()));
    connect(ui->btnMinuteMoreStep, SIGNAL(clicked()), this, SLOT(minuteAddStep()));

    QAction *inpDone = new QAction(tr("Done"), this);
    inpDone->setSoftKeyRole(QAction::PositiveSoftKey);
    addAction(inpDone);
    connect(inpDone, SIGNAL(triggered()), this, SLOT(done()));

    QAction *inpCancelled = new QAction(tr("Cancel"), this);
    inpCancelled->setSoftKeyRole(QAction::NegativeSoftKey);
    addAction(inpCancelled);
    connect(inpCancelled, SIGNAL(triggered()), this, SLOT(cancel()));

    changeHour(12);
    changeMinute(0);
}

void QHWTimeChooser::done() {
    emit timeSelected(currentHour, currentMinute);
}

void QHWTimeChooser::cancel() {
    emit cancelled();
}

void QHWTimeChooser::hourDecMuch() {
    changeHour(currentHour-5);
}
void QHWTimeChooser::hourDecStep() {
    changeHour(currentHour-1);
}
void QHWTimeChooser::hourAddStep() {
    changeHour(currentHour+1);
}
void QHWTimeChooser::hourAddMuch() {
    changeHour(currentHour+5);
}

void QHWTimeChooser::minuteDecMuch() {
    changeMinute(currentMinute-10);
}
void QHWTimeChooser::minuteDecStep() {
    changeMinute(currentMinute-1);
}
void QHWTimeChooser::minuteAddStep() {
    changeMinute(currentMinute+1);
}
void QHWTimeChooser::minuteAddMuch() {
    changeMinute(currentMinute+10);
}

void QHWTimeChooser::updateTimeLabel() {
    ui->timeLabel->setText(
            QString::number(currentHour).rightJustified(2, '0') +
            ":" +
            QString::number(currentMinute).rightJustified(2, '0'));
}

void QHWTimeChooser::changeHour(int hour) {
    if (hour > 23) {
        hour = 23;
    }
    if (hour < 0) {
        hour = 0;
    }
    currentHour = hour;
    updateTimeLabel();
}

void QHWTimeChooser::changeMinute(int minute) {
    if (minute > 59) {
        minute = 59;
    }
    if (minute < 0) {
        minute = 0;
    }
    currentMinute = minute;
    updateTimeLabel();
}

QHWTimeChooser::~QHWTimeChooser()
{
    delete ui;
}
