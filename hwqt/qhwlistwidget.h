#ifndef QHWLISTWIDGET_H
#define QHWLISTWIDGET_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QPoint>
#include <QPixmap>

class QHWListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit QHWListWidget(QWidget *parent = 0);
    ~QHWListWidget();

    virtual void paintEvent(QPaintEvent *pe);
    virtual void mouseMoveEvent ( QMouseEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event );
    virtual void mouseReleaseEvent ( QMouseEvent * event );
    virtual void timerEvent(QTimerEvent *event);
public slots:
    void resetCache();
 signals:
    void longTapHasHappened(QPoint where, QListWidgetItem* who);

 private:
    void loadWaitPixmaps();
    QPixmap* m_waitPixmaps[12];
    int myTimerTickCounter;;
    int myTimerID;
    bool myTrackingMouseFlag;

    //due to Qt 4.6.3 bug on Symbian where selectedItems() does not populate well
    QListWidgetItem* mySelectedItemCache;
    QPoint myOriginalPoint;
    QPoint myLastPoint;
};

#endif // QHWLISTWIDGET_H
