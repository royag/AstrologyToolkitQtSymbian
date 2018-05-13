#include "mychartopenwindow.h"
//#include "ui_mychartopendialog.h"

#include "hwqt/qhwlistselect.h"
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include "downloaddialog.h"

MyChartOpenWindow::MyChartOpenWindow(QWidget *parent, QString dir,
                                     bool isDownloadable,
                                     QString url) :
    QFrame(parent),
    directory(dir),
    downloadable(isDownloadable),
    downloadUrl(url),
    //ui(new Ui::MyChartOpenDialog),
    inDialog(false)
{
    resize(parent->size());

    listSelect = new QHWListSelect("Open", this);
    listSelect->setHeaderText("Select chart to open");

    if (downloadable) {
        QPushButton* downloadButton = new QPushButton("Download more", listSelect);
        listSelect->addWidgetToLayout(downloadButton);
        connect(downloadButton, SIGNAL(clicked()), this, SLOT(downloadMore()));
    }

    connect(listSelect, SIGNAL(itemSelected(QString)), this, SLOT(selectedName(QString)));
    connect(listSelect, SIGNAL(selectCancelled()), this, SLOT(cancel()));
    connect(listSelect, SIGNAL(itemLongTapped(QString)), this, SLOT(longTappedName(QString)));
}

void MyChartOpenWindow::setHeaderText(QString txt) {
    listSelect->setHeaderText(txt);
}


void MyChartOpenWindow::resizeEvent ( QResizeEvent * event )  {
    QFrame::resizeEvent(event);
    QRect r = geometry();
    listSelect->setGeometry(0,0,r.width(),r.height());
}

void MyChartOpenWindow::reloadDir() {
    QDir mydir(directory);
    QHWListWidget* listWidget = listSelect->getListWidget();
    listWidget->clear();
    listWidget->addItems(mydir.entryList(QStringList("*.chr")));
}

void MyChartOpenWindow::setFilenames(QStringList list) {
    QHWListWidget* listWidget = listSelect->getListWidget();
    listWidget->clear();
    listWidget->addItems(list);
}


void MyChartOpenWindow::downloadMore() {
    DownloadDialog dialog(directory, downloadUrl, this);
    dialog.exec();
    QDir mydir(directory);
    QHWListWidget* listWidget = listSelect->getListWidget();
    listWidget->clear();
    listWidget->addItems(mydir.entryList(QStringList("*.chr")));
}

void MyChartOpenWindow::selectedName(QString name) {
    if (directory.isNull()) {
        this->selectedFileName = name;
    } else {
        this->selectedFileName = directory + "/" + name;
    }
    selectPressed();
}

void MyChartOpenWindow::longTappedName(QString name) {
    if (directory.isNull()) {
        return; // we're not able to reload after a delete...
    }
    inDialog = true;
    int answer = QMessageBox::question(listSelect, "Delete file", "Want to delete " + name + "?",
                                       QMessageBox::Yes, QMessageBox::No);
    if (answer == QMessageBox::Yes) {
        QFile file(directory + "/" + name);
        if (!file.remove()) {
            QMessageBox::warning(listSelect, "Error", "Could not delete file");
        } else {
            QDir mydir(directory);
            listSelect->getListWidget()->clear();
            listSelect->getListWidget()->addItems(mydir.entryList(QStringList("*.chr")));
        }
    }
    inDialog = false;
}

void MyChartOpenWindow::cancel() {
    this->selectedFileName = QString::null;
    emit cancelled(); //selectCancelled();
}

void MyChartOpenWindow::selectPressed() {
    if (!inDialog) {
        emit selectedFile(selectedFileName);
    }
}

void MyChartOpenWindow::focusInEvent ( QFocusEvent * event ) {
    listSelect->setFocus(event->reason());
}

MyChartOpenWindow::~MyChartOpenWindow()
{
}
