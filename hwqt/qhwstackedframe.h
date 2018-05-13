#ifndef QHWSTACKEDFRAME_H
#define QHWSTACKEDFRAME_H

#include <QFrame>
#include <QStackedWidget>

class QHWStackedFrame : public QFrame
{
    Q_OBJECT
public:
    explicit QHWStackedFrame(QStackedWidget *stackedWidget, QWidget *parent = 0);
    virtual ~QHWStackedFrame();
    void setFrameId(QString str);

signals:

public slots:

protected:
    QStackedWidget *stackedWidget;

    QHWStackedFrame* getFrameByClassName(QString className);
    void setActiveWidgetByClassName(QString className);
    QHWStackedFrame* getFrameByFrameId(QString frameId);
    void setActiveWidgetByFrameId(QString frameId);
private:
    QString frameId;


};

#endif // QHWSTACKEDFRAME_H
