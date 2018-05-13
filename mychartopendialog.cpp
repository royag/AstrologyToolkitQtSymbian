#include "mychartopendialog.h"
#include "ui_mychartopendialog.h"

#include "hwqt/qhwlistselect.h"
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include "downloaddialog.h"

MyChartOpenDialog::MyChartOpenDialog(QWidget *parent, const QString & dir,
                                     bool isDownloadable,
                                     const QString & url) :
    QDialog(parent),
    directory(dir),
    downloadable(isDownloadable),
    downloadUrl(url),
    ui(new Ui::MyChartOpenDialog),
    inDialog(false)
{
    ui->setupUi(this);

    resize(parent->size());

    listSelect = new QHWListSelect("Open", this);
    listSelect->setHeaderText("Select chart to open");

    QDir mydir(dir);
    QHWListWidget* listWidget = listSelect->getListWidget();
    listWidget->addItems(mydir.entryList(QStringList("*.chr")));

    if (downloadable) {
        QPushButton* downloadButton = new QPushButton("Download more", listSelect);
        listSelect->addWidgetToLayout(downloadButton);
        connect(downloadButton, SIGNAL(clicked()), this, SLOT(downloadMore()));
    }

    //listSelect->getListWidget()->addItem("TRALALALA");
    //listSelect->getListWidget()->addItem("tralalal2");

    connect(listSelect, SIGNAL(itemSelected(QString)), this, SLOT(selectedName(QString)));
    connect(listSelect, SIGNAL(selectCancelled()), this, SLOT(cancel()));
    connect(listSelect, SIGNAL(itemLongTapped(QString)), this, SLOT(longTappedName(QString)));
}

void MyChartOpenDialog::downloadMore() {
    /*if (QMessageBox::question(listSelect,
                          "Download Charts",
                          "Look for more downloadable charts on the internet?",
                          QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {

        // Do the downloading
        DownloadDialog dialog(directory, downloadUrl, this);
        dialog.exec();
    }*/
    DownloadDialog dialog(directory, downloadUrl, this);
    dialog.exec();
    QDir mydir(directory);
    QHWListWidget* listWidget = listSelect->getListWidget();
    listWidget->clear();
    listWidget->addItems(mydir.entryList(QStringList("*.chr")));
}


void MyChartOpenDialog::resizeEvent(QResizeEvent * event) {
    qDebug("My Chart open got resize event oldHeight=%i newHeight=%i",
    event->oldSize().height(),
    event->size().height() );

    QDialog::resizeEvent(event);
    listSelect->resize(this->size());
    //listSelect->repaint();
    //listSelect->update();
}

void MyChartOpenDialog::selectedName(QString name) {
    this->selectedFileName = directory + "/" + name;
    //this->selectedFileName = directory + "/" + "19784121920_NO.chr";
    selectPressed();
}

void MyChartOpenDialog::longTappedName(QString name) {
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

QString MyChartOpenDialog::getOpenFileName(QWidget * parent, const QString & dir,
                                           bool isDownloadable,
                                           const QString & url) {
    MyChartOpenDialog* dialog = new MyChartOpenDialog(parent, dir, isDownloadable, url);
    dialog->exec();
    QString name = dialog->selectedFileName;
    delete dialog;
    return name;
}

void MyChartOpenDialog::cancel() {
    this->selectedFileName = QString::null;
    emit done(0); //selectCancelled();
}

void MyChartOpenDialog::selectPressed() {
    /*if (activateByPositiveSoftkey) {
        itemActivated(ui->listWidget->currentItem());
    } else {
        emit selectActionTriggered();
    }*/
    if (!inDialog) {
        emit done(0);
    }
}

MyChartOpenDialog::~MyChartOpenDialog()
{
    delete ui;
}
