#include "infoframe.h"
#include "ui_infoframe.h"
#include <QDesktopServices>
#include <QUrl>
#include <QStringList>

InfoFrame::InfoFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::InfoFrame),
    m_escapable(true),
    searchForChartData(QString::null)
{
    ui->setupUi(this);
    ui->label->setAcceptDrops(true);
    ui->label->setWordWrap(true);
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okPressed()));
    //ui->label->
    connect(ui->label, SIGNAL(linkActivated(const QString&)), this, SLOT(openLink(QString)));
    //connect(ui->labelHeader, SIGNAL(linkActivated(const QString&)), this, SLOT(openLink(QString)));
    setDialogMode(false);
    connect(ui->buttonYes, SIGNAL(clicked()), this, SLOT(searchGo()));
    connect(ui->buttonNo, SIGNAL(clicked()), this, SLOT(searchCancel()));

    connect(ui->searchChartsButton, SIGNAL(clicked()), this, SLOT(searchCharts()));
}

void InfoFrame::setEscapable(bool escapable) {
    m_escapable = escapable;
    ui->okButton->setVisible(m_escapable);
    ui->okButton->update();
}

void InfoFrame::setLabelName(const QString &name) {
    ui->label->setObjectName(name);
}

void InfoFrame::openLink(QString url) {
    if (url.indexOf('|') >= 0) {
        QStringList part1_2 = url.split('|');
        url = part1_2[0];
        searchForChartData = part1_2[1];
    } else {
        searchForChartData = QString::null;
    }
    searchQuery = url;
    setDialogMode(true);
    ui->labelDialog->setText("Search the WEB for <br>" +
                             searchQuery + "?");
    //QDesktopServices::openUrl(QUrl(url));
}

#define SEARCH_URL "http://www.google.com/search?q="

void InfoFrame::searchCharts() {
    QStringList data = searchForChartData.split(',');
    int planet = data.at(0).toInt();
    int sign = data.at(1).toInt();
    int house = data.at(2).toInt();
    int aspect = data.at(3).toInt();
    int planet2 = data.at(4).toInt();
    emit wantSearchForPlacement(planet,sign,house,aspect,planet2);
}

void InfoFrame::searchGo() {

    setDialogMode(false);
    QString url = SEARCH_URL + searchQuery.replace(" ","+");
    qDebug(url.toLatin1());
    QDesktopServices::openUrl(QUrl(url));
}

void InfoFrame::searchCancel() {
    setDialogMode(false);
}

void InfoFrame::setDialogMode(bool dialog) {
    ui->searchChartsButton->setVisible(dialog && !searchForChartData.isNull());
    ui->labelDialog->setVisible(dialog);
    ui->buttonNo->setVisible(dialog);
    ui->buttonYes->setVisible(dialog);
    ui->label->setVisible(!dialog);
    ui->okButton->setVisible(m_escapable && !dialog);
}

void InfoFrame::setBodyText(QString txt) {
    setDialogMode(false);
    ui->label->setText(txt);
}

void InfoFrame::okPressed() {

    this->setVisible(false);
}

InfoFrame::~InfoFrame()
{
    delete ui;
}
