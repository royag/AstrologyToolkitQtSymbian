#include "qhwlistwidget.h"

#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEngine>

QHWListWidget::QHWListWidget(QWidget *parent) :
        QListWidget(parent),
        mySelectedItemCache(0)
{
    myTrackingMouseFlag=false;
    loadWaitPixmaps();
}

void QHWListWidget::resetCache() {
    mySelectedItemCache = 0;
}


void QHWListWidget::paintEvent(QPaintEvent *pe)
{
    QListWidget::paintEvent(pe);
    //QRect rect = geometry();
    //setGeometry(0,0,500,500);
    QPainter newPainter(this->viewport());
    if(myTrackingMouseFlag==true)
    {
        QPoint point(myOriginalPoint.x()-100,myOriginalPoint.y()-60);
        if (m_waitPixmaps[myTimerTickCounter] != 0) {
            newPainter.drawPixmap(point, *m_waitPixmaps[myTimerTickCounter]);
        }

    }
}

void QHWListWidget::mouseReleaseEvent ( QMouseEvent * event )
{
    QListWidget::mouseReleaseEvent(event);
    killTimer(myTimerID);
    myTimerTickCounter=0;
    myTrackingMouseFlag=false;
    repaint();
}

void QHWListWidget::mouseMoveEvent ( QMouseEvent * event )
{
    QListWidget::mouseMoveEvent(event);
    if((myOriginalPoint-event->pos()).manhattanLength()>100)
    {
        killTimer(myTimerID);
        myTimerTickCounter=0;
        myTrackingMouseFlag=false;
        if(selectedItems().count()>0)
        {
            mySelectedItemCache=selectedItems()[0];
        }
        else
        {
        }
        repaint();
    }
}

void QHWListWidget::mousePressEvent ( QMouseEvent * event )
{
    QListWidget::mousePressEvent(event);
    myTimerID=startTimer(40);
    myTimerTickCounter=0;
    myTrackingMouseFlag=true;
    if(selectedItems().count()>0)
    {
        mySelectedItemCache=selectedItems()[0];
    }
    else
    {

    }
    myOriginalPoint=event->pos();
}

void QHWListWidget::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==myTimerID)
    {
        myTimerTickCounter++;
        if(myTimerTickCounter==11)
        {
            emit longTapHasHappened(myOriginalPoint,mySelectedItemCache);
            killTimer(myTimerID);
            myTrackingMouseFlag=false;
        }
        repaint();
    }
}

void QHWListWidget::loadWaitPixmaps() {
    for (int i = 0; i < 12; i++) {
        m_waitPixmaps[i] = new QPixmap(
                QString(":/gfx/wait")+
                QString::number(i+1)+
                QString(".png"));
    }
}

QHWListWidget::~QHWListWidget() {
    for (int i = 0; i < 12; i++) {
        if (m_waitPixmaps[i] != 0) {
            delete m_waitPixmaps[i];
            m_waitPixmaps[i] = 0;
        }
    }
}
