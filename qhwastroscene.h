#ifndef QHWASTROSCENE_H
#define QHWASTROSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

class QHWAstroScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit QHWAstroScene(QObject *parent);
    bool isTrackingMouse();
    QPointF trackingPoint();
    int tickCounter();
    void addLongTapItem(QGraphicsItem*);
    QGraphicsItem* currentItem();
signals:
    void pressedItem(QGraphicsItem *);
    void movedToItem(QGraphicsItem *);
    void releaseOnItem(QGraphicsItem *);
    void longTapHasHappened(QPointF where, QGraphicsItem* who);
    void tickChanged();
    void trackingStopped();
private:
    QGraphicsItem *currentActionItem;
    QGraphicsItem *lastActionItem;
    int myTimerTickCounter;
    int myTimerID;
    bool myTrackingMouseFlag;
    QPointF myOriginalPoint;
    QPointF currentPoint;
    QList<QGraphicsItem*> longTapItems;
    bool isLongTapItem(QGraphicsItem*);
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void timerEvent(QTimerEvent *);
    //virtual void pa
};

#endif // QHWASTROSCENE_H
