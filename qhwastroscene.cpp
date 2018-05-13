#include "qhwastroscene.h"

QHWAstroScene::QHWAstroScene(QObject *parent) :
    QGraphicsScene(parent),
    lastActionItem(0),
    currentActionItem(0),
    myTimerTickCounter(0),
    myTimerID(0),
    myTrackingMouseFlag(false)
{

}

int QHWAstroScene::tickCounter() {
    return myTimerTickCounter;
}

bool QHWAstroScene::isTrackingMouse() {
    return myTrackingMouseFlag;
}

void QHWAstroScene::addLongTapItem(QGraphicsItem * item) {
    longTapItems.append(item);
}

bool QHWAstroScene::isLongTapItem(QGraphicsItem * item) {
    QListIterator<QGraphicsItem*> it(longTapItems);
    while (it.hasNext()) {
        if (it.next() == item) {
            return true;
        }
    }
    return false;
}

QPointF QHWAstroScene::trackingPoint() {
    return currentActionItem->pos();
}

QGraphicsItem* QHWAstroScene::currentItem() {
    return currentActionItem;
}

void QHWAstroScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug("PRESS");
    QPoint p = event->pos().toPoint();
    QGraphicsScene::mousePressEvent(event);
    QGraphicsItem *item = itemAt(event->scenePos().x(), event->scenePos().y());
    if (item != 0 && item != lastActionItem) {
        lastActionItem = item;



        if (isLongTapItem(item)) {
            currentActionItem = lastActionItem;
            myTimerTickCounter=0;
            myTrackingMouseFlag=true;
            myOriginalPoint = event->scenePos();
            currentPoint = myOriginalPoint;
               qDebug("starting timer");
            myTimerID=startTimer(100);
        } else {
            currentActionItem = 0;
        }
        emit pressedItem(item);

    }
}
void QHWAstroScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    qDebug("MOVE");
    QGraphicsScene::mouseMoveEvent(event);
    QGraphicsItem *item = itemAt(event->scenePos().x(), event->scenePos().y());

    if (item == currentActionItem) {
        return;
    }
    if (item != currentActionItem && isLongTapItem(currentActionItem) && !isLongTapItem(item)) {
        //currentActionItem->pos().x()
        //QRect bound(currentActionItem->boundingRect());

        QString pos = QString::number(event->scenePos().toPoint().x()) + "x" +
                     QString::number(event->scenePos().toPoint().y());

        QRect region = currentActionItem->boundingRect().toAlignedRect().adjusted(event->scenePos().toPoint().x(), event->scenePos().toPoint().y(),0,0);
        QString pos2 = QString::number(region.x()) + "x" +
                     QString::number(region.y()) + ",w=" +
                     QString::number(region.width()) + ",h=" +
                     QString::number(region.height());

        qDebug(pos.toLatin1());
        qDebug(pos2.toLatin1());
        if (region.contains(event->scenePos().toPoint())) {

            qDebug("Ignore move");
            return;
        } else {
            qDebug("Doesnt contain");
        }
    } else {
        qDebug("NOT from longTap to NONlongTap");
        /*if (isLongTapItem(item)) {
            qDebug("new IS longtap");
        }*/

    }

    if (item != 0 && item != lastActionItem) {

        /*if (currentActionItem != 0 && !isLongTapItem(item)) {
            if ()
        }*/
        killTimer(myTimerID);
        lastActionItem = item;

        if (isLongTapItem(item)) {
            currentActionItem = lastActionItem;
            myTimerTickCounter=0;
            myTrackingMouseFlag=true;
            myOriginalPoint = event->scenePos();
            currentPoint = myOriginalPoint;
            myTimerID=startTimer(50);
            qDebug("Started timer by move");
        } else {
            currentActionItem = 0;
        }
        emit movedToItem(item);
    } else if (item != lastActionItem ||
               ((myOriginalPoint-event->pos()).manhattanLength()>100)) {

        killTimer(myTimerID);
        myTimerTickCounter=0;
        myTrackingMouseFlag=false;
        qDebug("trackStopped");
        currentActionItem = 0;
        emit trackingStopped();

    } else {
        currentPoint = event->scenePos();
    }
}
void QHWAstroScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    qDebug("RELEASE");
    killTimer(myTimerID);
    myTimerTickCounter=0;
    myTrackingMouseFlag=false;
    emit trackingStopped();
    qDebug("trackStopped");
    QGraphicsScene::mouseReleaseEvent(event);
    QGraphicsItem *item = itemAt(event->scenePos().x(), event->scenePos().y());
    if (item != 0 && item != lastActionItem) {
        lastActionItem = 0;
        currentActionItem = lastActionItem;
        emit releaseOnItem(item);

    }
}

void QHWAstroScene::timerEvent(QTimerEvent *event) {
    if(event->timerId()==myTimerID) {
        myTimerTickCounter++;

        emit tickChanged();
        if(myTimerTickCounter>=12) {

            qDebug("LONG TAP HAS HAPPENED");
            emit longTapHasHappened(currentPoint,currentActionItem);
            killTimer(myTimerID);
            myTrackingMouseFlag=false;
        }
    }
}

