#ifndef HWCOMBOINPUT_H
#define HWCOMBOINPUT_H

#include <QFrame>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>

#include "hwqwertyinput.h"

namespace Ui {
    class HWComboInput;
}

/*class MyListener : public HWQwertyListener {

};*/
class HWComboPopulater{
public:
    virtual void populateComboList(QString entered, QStringList &list) {}
};

class HWComboInput : public QLabel, HWQwertyListener
{
    Q_OBJECT

public:
    explicit HWComboInput(QWidget * centralWidget, QWidget *parent = 0);
    ~HWComboInput();
    void setTextAndUpdateSelection(QString s);
    void setGeometry ( const QRect & rect );
    virtual void contentAdded(QString content);
    virtual void backspacePressed();
    virtual void enterPressed();
    void setPopulater(HWComboPopulater* populater);
signals:
    void selectedChoice(QString selection);
public slots:
    void charInput(QString c);
    void listItemSelected(QListWidgetItem* item);
protected:
    virtual void focusInEvent(QFocusEvent * event);

    virtual void focusOutEvent(QFocusEvent * event);
private:
    void createList();
    void destroyList();
    HWComboPopulater *m_populater;
    Ui::HWComboInput *ui;
    QWidget* m_centralWidget; // needed for qwerty-pad
    QListWidget* m_selectList;
    HWQwertyInput* m_qwerty;
    bool m_keyboardActive;
};

#endif // HWCOMBOINPUT_H
