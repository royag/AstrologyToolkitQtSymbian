#include "qhwdatechooser.h"
#include "ui_qhwdatechooser.h"

QHWDateChooser::QHWDateChooser(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::QHWDateChooser),
    currentYear(2000),
    currentMonth(1),
    currentDay(1),
    maxYear(2099),
    minYear(1892)
{
    ui->setupUi(this);
    connect(ui->btnYearLessLarge, SIGNAL(clicked()), this, SLOT(yearDecMuch()));
    connect(ui->btnYearLessStep, SIGNAL(clicked()), this, SLOT(yearDecStep()));
    connect(ui->btnYearMoreLarge, SIGNAL(clicked()), this, SLOT(yearAddMuch()));
    connect(ui->btnYearMoreStep, SIGNAL(clicked()), this, SLOT(yearAddStep()));

    connect(ui->btnMonthLessLarge, SIGNAL(clicked()), this, SLOT(monthDecMuch()));
    connect(ui->btnMonthLessStep, SIGNAL(clicked()), this, SLOT(monthDecStep()));
    connect(ui->btnMonthMoreLarge, SIGNAL(clicked()), this, SLOT(monthAddMuch()));
    connect(ui->btnMonthMoreStep, SIGNAL(clicked()), this, SLOT(monthAddStep()));

    connect(ui->btnDayLessLarge, SIGNAL(clicked()), this, SLOT(dayDecMuch()));
    connect(ui->btnDayLessStep, SIGNAL(clicked()), this, SLOT(dayDecStep()));
    connect(ui->btnDayMoreLarge, SIGNAL(clicked()), this, SLOT(dayAddMuch()));
    connect(ui->btnDayMoreStep, SIGNAL(clicked()), this, SLOT(dayAddStep()));

    QAction *inpDone = new QAction(tr("Done"), this);
    inpDone->setSoftKeyRole(QAction::PositiveSoftKey);
    addAction(inpDone);
    connect(inpDone, SIGNAL(triggered()), this, SLOT(done()));

    QAction *inpCancelled = new QAction(tr("Cancel"), this);
    inpCancelled->setSoftKeyRole(QAction::NegativeSoftKey);
    addAction(inpCancelled);
    connect(inpCancelled, SIGNAL(triggered()), this, SLOT(cancel()));
}

void QHWDateChooser::done() {
    emit dateSelected(currentYear, currentMonth, currentDay);
}

void QHWDateChooser::cancel() {
    emit cancelled();
}

void QHWDateChooser::yearDecMuch() {
    changeYear(currentYear-10);
}
void QHWDateChooser::yearDecStep() {
    changeYear(currentYear-1);
}
void QHWDateChooser::yearAddStep() {
    changeYear(currentYear+1);
}
void QHWDateChooser::yearAddMuch() {
    changeYear(currentYear+10);
}

void QHWDateChooser::monthDecMuch() {
    changeMonth(currentMonth-5);
}
void QHWDateChooser::monthDecStep() {
    changeMonth(currentMonth-1);
}
void QHWDateChooser::monthAddStep() {
    changeMonth(currentMonth+1);
}
void QHWDateChooser::monthAddMuch() {
    changeMonth(currentMonth+5);
}

void QHWDateChooser::dayDecMuch() {
    changeDay(currentDay-10);
}
void QHWDateChooser::dayDecStep() {
    changeDay(currentDay-1);
}
void QHWDateChooser::dayAddStep() {
    changeDay(currentDay+1);
}
void QHWDateChooser::dayAddMuch() {
    changeDay(currentDay+10);
}
QString QHWDateChooser::monthName(int month) {
    switch(month) {
    case 1:return "January";
    case 2:return "February";
    case 3:return "Mars";
    case 4:return "April";
    case 5:return "May";
    case 6:return "June";
    case 7:return "July";
    case 8:return "August";
    case 9:return "September";
    case 10:return "October";
    case 11:return "November";
    case 12:return "December";
    }
    return "Unknown";
}

void QHWDateChooser::changeYear(int year) {
    if (year > maxYear) {
        year = maxYear;
    }
    if (year < minYear) {
        year = minYear;
    }
    currentYear = year;
    ui->labelYearValue->setText(QString::number(currentYear));
}

void QHWDateChooser::changeMonth(int month) {
    if (month > 12) {
        month = 12;
    }
    if (month < 1) {
        month = 1;
    }
    currentMonth = month;
    ui->labelMonthValue->setText(monthName(currentMonth));
}

void QHWDateChooser::changeDay(int day) {
    if (day < 1) {
        day = 1;
    }
    if (day > 31) {
        day = 31;
    }
    currentDay = day;
    ui->labelDayValue->setText(QString::number(currentDay));
}


QHWDateChooser::~QHWDateChooser()
{
    delete ui;
}
