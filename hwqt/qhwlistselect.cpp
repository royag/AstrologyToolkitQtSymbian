#include "qhwlistselect.h"

#include "mylistselect.h"
#include "ui_mylistselect.h"
#include "hwqt/qhwlistwidget.h"
#include <QMessageBox>


QHWListSelect::QHWListSelect(const QString &selectText, QWidget *parent) :
    QFrame(parent),
    activateByPositiveSoftkey(true)
{
    /*this->resize(360, 600);
    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Raised);*/

    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    headerLabel = new QLabel(this);
    headerLabel->setObjectName(QString::fromUtf8("headerLabel"));
    verticalLayout->addWidget(headerLabel);

    listWidget = new QHWListWidget(this);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));

    QFont font;
    font.setPointSize(9);
    listWidget->setFont(font);

    verticalLayout->addWidget(listWidget);

    //retranslateUi(MyListSelect);

    //QMetaObject::connectSlotsByName(MyListSelect);

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
    connect(listWidget, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(itemActivated(QListWidgetItem*)));
    connect(listWidget, SIGNAL(longTapHasHappened(QPoint,QListWidgetItem*)), this, SLOT(longTapHasHappened(QPoint,QListWidgetItem*)));
    //ui->listWidget->setCurrentItem();
}

void QHWListSelect::addWidgetToLayout(QWidget* w) {
    verticalLayout->addWidget(w);
}

void QHWListSelect::setFontSize(int size) {
    QFont font = listWidget->font();
    font.setPointSize(size);
    listWidget->setFont(font);
}

void QHWListSelect::setHeaderText(const QString &text) {
    headerLabel->setText(text);
    headerLabel->update();
}
void QHWListSelect::setActivateByPositiveSoftkey(bool doit) {
    activateByPositiveSoftkey = doit;
}

QHWListWidget* QHWListSelect::getListWidget() {
    return listWidget;
}

void QHWListSelect::cancel() {
    listWidget->resetCache();
    emit selectCancelled();
}

void QHWListSelect::selectPressed() {
    listWidget->resetCache();
    if (activateByPositiveSoftkey) {
        itemActivated(listWidget->currentItem());
    } else {
        emit selectActionTriggered();
    }
}

void QHWListSelect::itemActivated(QListWidgetItem* item) {
    listWidget->resetCache();
    emit itemSelected(item);
    if (item != 0) {
        emit itemSelected(item->text());
    }
}

void QHWListSelect::longTapHasHappened(QPoint point,QListWidgetItem* item) {
    listWidget->resetCache();
    emit itemLongTapped(item);
    if (item != 0) {
        emit itemLongTapped(item->text());
    }
}

void QHWListSelect::focusInEvent ( QFocusEvent * event ) {
    listWidget->setFocus(event->reason());
}

QHWListSelect::~QHWListSelect()
{
    //delete ui;
    delete actionSelect;
}
