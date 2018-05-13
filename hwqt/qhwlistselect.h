#ifndef QHWLISTSELECT_H
#define QHWLISTSELECT_H

#include <QFrame>
#include <hwqt/qhwlistwidget.h>
#include <QVBoxLayout>
#include <QLabel>

class QHWListSelect : public QFrame
{
    Q_OBJECT
public:
    explicit QHWListSelect(const QString &selectText = tr("Select"), QWidget *parent = 0);
    ~QHWListSelect();
    QHWListWidget* getListWidget();
    void setHeaderText(const QString &text);
    void setActivateByPositiveSoftkey(bool);
    void addWidgetToLayout(QWidget* w);
public slots:
    void setFontSize(int);
protected:
    virtual void focusInEvent ( QFocusEvent * event );
    QVBoxLayout *verticalLayout;
    QLabel *headerLabel;
    QHWListWidget *listWidget;
signals:
    void selectActionTriggered();
    void itemSelected(QString item);
    void itemSelected(QListWidgetItem* item);
    void itemLongTapped(QString item);
    void itemLongTapped(QListWidgetItem* item);
    void selectCancelled();

private:
    bool activateByPositiveSoftkey;
    QAction *actionSelect;
    QAction *actionCancel;
private slots:
    void longTapHasHappened(QPoint,QListWidgetItem*);
    void cancel();
    void selectPressed();
    void itemActivated(QListWidgetItem* item);
};

#endif // QHWLISTSELECT_H
