#include "mylistselect.h"
#include "ui_mylistselect.h"
#include "hwqt/qhwlistwidget.h"
#include <QMessageBox>


MyListSelect::MyListSelect(const QString &selectText, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MyListSelect),
    activateByPositiveSoftkey(true)
{
    ui->setupUi(this);

    actionSelect = new QAction(selectText, this);
    actionSelect->setSoftKeyRole(QAction::PositiveSoftKey);
    addAction(actionSelect);
    connect(actionSelect, SIGNAL(triggered()), this, SLOT(selectPressed()));

    actionCancel = new QAction(tr("Cancel"), this);
    actionCancel->setSoftKeyRole(QAction::NegativeSoftKey);
    addAction(actionCancel);
    connect(actionCancel, SIGNAL(triggered()), this, SLOT(cancel()));

    //connect(ui->listWidget, SIGNAL(activated(
    //connect(ui->listWidget, SIGNAL(activated(QModelIndex)))
    connect(ui->listWidget, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(itemActivated(QListWidgetItem*)));
    //connect(ui->listWidget, SIGNAL(longTapHasHappened(QPoint,QListWidgetItem*)), this, SLOT(longTapHasHappened(QPoint,QListWidgetItem*)));
    //ui->listWidget->setCurrentItem();
}

void MyListSelect::longTapHasHappened(QPoint,QListWidgetItem*) {
    QMessageBox::critical(0,"Incomplete data", "You must specify place and timezone");
}

void MyListSelect::setFontSize(int size) {
    QFont font = ui->listWidget->font();
    font.setPointSize(size);
    ui->listWidget->setFont(font);
}

void MyListSelect::setHeaderText(const QString &text) {
    ui->headerLabel->setText(text);
    ui->headerLabel->update();
}
void MyListSelect::setActivateByPositiveSoftkey(bool doit) {
    activateByPositiveSoftkey = doit;
}

QListWidget* MyListSelect::getListWidget() {
    return ui->listWidget;
}

void MyListSelect::cancel() {
    emit selectCancelled();
}

void MyListSelect::selectPressed() {
    if (activateByPositiveSoftkey) {
        itemActivated(ui->listWidget->currentItem());
    } else {
        emit selectActionTriggered();
    }
}

void MyListSelect::itemActivated(QListWidgetItem* item) {
    emit itemSelected(item);
    if (item != 0) {
        emit itemSelected(item->text());
    }
}

void MyListSelect::focusInEvent ( QFocusEvent * event ) {
    ui->listWidget->setFocus(event->reason());
}

MyListSelect::~MyListSelect()
{
    delete ui;
    delete actionSelect;
}
