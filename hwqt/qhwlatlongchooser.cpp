#include "qhwlatlongchooser.h"
#include "ui_qhwlatlongchooser.h"

QHWLatLongChooser::QHWLatLongChooser(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::QHWLatLongChooser),
    curLat(0),
    curLong(0)
{
    ui->setupUi(this);

    QAction *inpDone = new QAction(tr("Done"), this);
    inpDone->setSoftKeyRole(QAction::PositiveSoftKey);
    addAction(inpDone);
    connect(inpDone, SIGNAL(triggered()), this, SLOT(done()));

    QAction *inpCancelled = new QAction(tr("Cancel"), this);
    inpCancelled->setSoftKeyRole(QAction::NegativeSoftKey);
    addAction(inpCancelled);
    connect(inpCancelled, SIGNAL(triggered()), this, SLOT(cancel()));

    connect(ui->btnLatDegLessLarge, SIGNAL(clicked()), this, SLOT(latDegDecMuch()));
    connect(ui->btnLatDegLessStep, SIGNAL(clicked()), this, SLOT(latDegDecStep()));
    connect(ui->btnLatDegMoreLarge, SIGNAL(clicked()), this, SLOT(latDegIncMuch()));
    connect(ui->btnLatDegMoreStep, SIGNAL(clicked()), this, SLOT(latDegIncStep()));

    connect(ui->btnLatMinLessLarge, SIGNAL(clicked()), this, SLOT(latMinDecMuch()));
    connect(ui->btnLatMinLessStep, SIGNAL(clicked()), this, SLOT(latMinDecStep()));
    connect(ui->btnLatMinMoreLarge, SIGNAL(clicked()), this, SLOT(latMinIncMuch()));
    connect(ui->btnLatMinMoreStep, SIGNAL(clicked()), this, SLOT(latMinIncStep()));

    connect(ui->btnLongDegLessLarge, SIGNAL(clicked()), this, SLOT(longDegDecMuch()));
    connect(ui->btnLongDegLessStep, SIGNAL(clicked()), this, SLOT(longDegDecStep()));
    connect(ui->btnLongDegMoreLarge, SIGNAL(clicked()), this, SLOT(longDegIncMuch()));
    connect(ui->btnLongDegMoreStep, SIGNAL(clicked()), this, SLOT(longDegIncStep()));

    connect(ui->btnLongMinLessLarge, SIGNAL(clicked()), this, SLOT(longMinDecMuch()));
    connect(ui->btnLongMinLessStep, SIGNAL(clicked()), this, SLOT(longMinDecStep()));
    connect(ui->btnLongMinMoreLarge, SIGNAL(clicked()), this, SLOT(longMinIncMuch()));
    connect(ui->btnLongMinMoreStep, SIGNAL(clicked()), this, SLOT(longMinIncStep()));

}

void QHWLatLongChooser::done() {
    emit latLongSelected(curLat, curLong);
}

void QHWLatLongChooser::cancel() {
    emit cancelled();
}

QString QHWLatLongChooser::formatLatitude(int totalLatCents) {
    QString sLat = "N";
    if (totalLatCents < 0) {
        sLat = "S";
        totalLatCents = -totalLatCents;
    }
    int latWhole = totalLatCents / 100;
    int latCents = totalLatCents - (latWhole * 100);
    QString ret =
            QString::number(latWhole).rightJustified(2, QChar::fromAscii('0')) +
            sLat +
            QString::number(latCents).rightJustified(2, QChar::fromAscii('0'));
    return ret;
}

QString QHWLatLongChooser::formatLongitude(int totalLongCents) {
    QString sLong = "E";
    if  (totalLongCents < 0) {
        sLong = "W";
        totalLongCents = -totalLongCents;
    }
    int longWhole = totalLongCents / 100;
    int longCents = totalLongCents - (longWhole * 100);
    QString ret =
            QString::number(longWhole).rightJustified(2, QChar::fromAscii('0')) +
            sLong +
            QString::number(longCents).rightJustified(2, QChar::fromAscii('0'));
    return ret;
}

void QHWLatLongChooser::updateLat(int diff) {
    curLat += diff;
    if (curLat > 9000) {
        curLat = 9000;
    }
    if (curLat < -9000) {
        curLat = -9000;
    }
    ui->latitudeLabel->setText(formatLatitude(curLat));
}

void QHWLatLongChooser::updateLong(int diff) {
    curLong += diff;
    if (curLong > 18000) {
        curLong = 18000;
    }
    if (curLong < -18000) {
        curLong = -18000;
    }
    ui->longitudeLabel->setText(formatLongitude(curLong));
}


void QHWLatLongChooser::latDegDecMuch() {
    updateLat(-1000);
}

void QHWLatLongChooser::latDegDecStep() {
    updateLat(-100);
}

void QHWLatLongChooser::latDegIncMuch() {
    updateLat(1000);
}

void QHWLatLongChooser::latDegIncStep() {
    updateLat(100);
}

void QHWLatLongChooser::latMinDecMuch() {
    updateLat(-10);
}

void QHWLatLongChooser::latMinDecStep() {
    updateLat(-1);
}

void QHWLatLongChooser::latMinIncMuch() {
    updateLat(10);
}

void QHWLatLongChooser::latMinIncStep() {
    updateLat(1);
}

void QHWLatLongChooser::longDegDecMuch() {
    updateLong(-1000);
}

void QHWLatLongChooser::longDegDecStep() {
    updateLong(-100);
}

void QHWLatLongChooser::longDegIncMuch() {
    updateLong(1000);
}

void QHWLatLongChooser::longDegIncStep() {
    updateLong(100);
}

void QHWLatLongChooser::longMinDecMuch() {
    updateLong(-10);
}

void QHWLatLongChooser::longMinDecStep() {
    updateLong(-1);
}

void QHWLatLongChooser::longMinIncMuch() {
    updateLong(10);
}

void QHWLatLongChooser::longMinIncStep() {
    updateLong(1);
}


QHWLatLongChooser::~QHWLatLongChooser()
{
    delete ui;
}
