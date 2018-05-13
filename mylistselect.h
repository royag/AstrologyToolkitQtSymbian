#ifndef MYLISTSELECT_H
#define MYLISTSELECT_H

#include <QFrame>
#include <QAction>
#include <QListWidgetItem>
#include <QListWidget>
#include <QFocusEvent>
#include <QPushButton>

namespace Ui {
    class MyListSelect;
}

class MyListSelect : public QFrame
{
    Q_OBJECT

public:
    explicit MyListSelect(const QString &selectText = tr("Select"), QWidget *parent = 0);
    ~MyListSelect();
    QListWidget* getListWidget();
    void setHeaderText(const QString &text);
    void setActivateByPositiveSoftkey(bool);
public slots:
    void setFontSize(int);
protected:
    virtual void focusInEvent ( QFocusEvent * event );
signals:
    void selectActionTriggered();
    void itemSelected(QString item);
    void itemSelected(QListWidgetItem* item);
    void selectCancelled();

private:
    bool activateByPositiveSoftkey;
    Ui::MyListSelect *ui;
    QAction *actionSelect;
    QAction *actionCancel;
private slots:
    void longTapHasHappened(QPoint,QListWidgetItem*);
    void cancel();
    void selectPressed();
    void itemActivated(QListWidgetItem* item);
};

#endif // MYLISTSELECT_H
