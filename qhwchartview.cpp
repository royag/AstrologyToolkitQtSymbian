#include "qhwchartview.h"
#include "ui_qhwchartview.h"
#include "hwqt/qhwstackedframe.h"
#include <QStackedWidget>

QHWChartView::QHWChartView(QStackedWidget* sw, QWidget *parent) :
    QHWStackedFrame(sw, parent),
    ui(new Ui::QHWChartView)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene(ui->canvas);
    ui->canvas->setScene(scene);
    populateGraphics();
}

void QHWChartView::populateGraphics() {
/*
    m_chart = new AstroChart(ui->canvas->scene(), this);

    planet_positions pp = ephem_calculateRecForGmt(1978, 4, 12 + this->currentDay, 18, 20, 0 ,&(this->ephemYear));
    calcAscAndMc(&pp, 59.44, 10.15);

    m_chart->updatePositions(pp);
    */
}

QHWChartView::~QHWChartView()
{
    delete ui;
}
