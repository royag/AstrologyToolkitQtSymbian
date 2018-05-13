#include "qhwsearchselector.h"
#include "ui_qhwsearchselector.h"
#include "qhwstackedframe.h"

QHWSearchSelector::QHWSearchSelector(QStackedWidget *sw, QWidget *parent) :
    QHWStackedFrame(sw, parent),
    ui(new Ui::QHWSearchSelector)
{
    ui->setupUi(this);
}

QHWSearchSelector::~QHWSearchSelector()
{
    delete ui;
}
