#ifndef QHWSEARCHSELECTOR_H
#define QHWSEARCHSELECTOR_H

#include <QFrame>
#include "qhwstackedframe.h"

namespace Ui {
    class QHWSearchSelector;
}

class QHWSearchSelector : public QHWStackedFrame
{
    Q_OBJECT

public:
    explicit QHWSearchSelector(QStackedWidget *sw, QWidget *parent = 0);;
    ~QHWSearchSelector();

private:
    Ui::QHWSearchSelector *ui;
};

#endif // QHWSEARCHSELECTOR_H
