#ifndef QHWCHARTVIEW_H
#define QHWCHARTVIEW_H

#include <QFrame>
#include "hwqt/qhwstackedframe.h"
#include <QStackedWidget>

#include <QMainWindow>
#include <QGraphicsScene>
#include <QFrame>
#include "astrochart.h"

#include "cpp_core/astrodefs.h"
#include <QListWidget>
#include "hwqt/hwqwertyinput.h"
#include "cpp_core/geodata.h"
#include "hwqt/hwcomboinput.h"

namespace Ui {
    class QHWChartView;
}

class QHWChartView : public QHWStackedFrame
{
    Q_OBJECT

public:
    explicit QHWChartView(QStackedWidget* stackedWidget, QWidget *parent = 0);
    ~QHWChartView();

private:
    AstroChart *m_chart;
    Ui::QHWChartView *ui;
    void populateGraphics();
};

#endif // QHWCHARTVIEW_H
