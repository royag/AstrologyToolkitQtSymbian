#include "qhwtimechooser.h"
#include "ui_qhwtimechooser.h"

QHWTimeChooser::QHWTimeChooser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QHWTimeChooser)
{
    ui->setupUi(this);
}

QHWTimeChooser::~QHWTimeChooser()
{
    delete ui;
}
