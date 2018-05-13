#include "qhwstackedframe.h"

QHWStackedFrame::QHWStackedFrame(QStackedWidget *stackedWidget, QWidget *parent) :
    QFrame(parent)
{
    this->stackedWidget = stackedWidget;
    frameId = "noid";
}

void QHWStackedFrame::setFrameId(QString frameId) {
    this->frameId = frameId;
}

void QHWStackedFrame::setActiveWidgetByClassName(QString className) {
    QHWStackedFrame* frame = getFrameByClassName(className);
    if (frame != 0) {
        stackedWidget->setCurrentWidget(frame);
    }
}

void QHWStackedFrame::setActiveWidgetByFrameId(QString frameId) {
    QHWStackedFrame* frame = getFrameByFrameId(frameId);
    if (frame != 0) {
        stackedWidget->setCurrentWidget(frame);
    }
}

QHWStackedFrame* QHWStackedFrame::getFrameByFrameId(QString frameId) {
    if (stackedWidget == 0) {
        return 0;
    }
    QHWStackedFrame* ret = 0;
    QHWStackedFrame* tmp = 0;
    for (int i = 0; i < stackedWidget->count(); i++) {
        tmp = static_cast<QHWStackedFrame*>(stackedWidget->widget(i));
        if (tmp->frameId == frameId) {
            ret = tmp;
            break;
        }
    }
    return ret;
}

QHWStackedFrame* QHWStackedFrame::getFrameByClassName(QString className) {
    if (stackedWidget == 0) {
        return 0;
    }
    QHWStackedFrame* ret = 0;
    for (int i = 0; i < stackedWidget->count(); i++) {
        if (stackedWidget->widget(i)->metaObject()->className() == className) {
            ret = static_cast<QHWStackedFrame*>(stackedWidget->widget(i));
            break;
        }
    }
    return ret;
}

QHWStackedFrame::~QHWStackedFrame() {

}
