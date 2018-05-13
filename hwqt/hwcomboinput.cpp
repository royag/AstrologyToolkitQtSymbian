#include "hwcomboinput.h"
#include <QRect>
#include <QListWidget>
#include <QFocusEvent>
#include <QListWidgetItem>
#include <QStringList>

HWComboInput::HWComboInput(QWidget* centralWidget, QWidget *parent) :
    QLabel(parent)
{
    m_selectList = 0;
    m_centralWidget = centralWidget;
    /*m_selectList = new QListWidget(parent);
    m_selectList->setAutoFillBackground(true);
    m_selectList->setVisible(false);*/
    //connect(m_selectList, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(listItemSelected(QListWidgetItem*)));

    //connect(m_selectList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(listItemSelected(QListWidgetItem*)));
    setFocusPolicy(Qt::ClickFocus);

    m_qwerty = 0;
    m_populater = 0;
    m_keyboardActive = false;



    //connect(this, SIGNAL())
}
void HWComboInput::setPopulater(HWComboPopulater* populater) {
    m_populater = populater;
}

void HWComboInput::contentAdded(QString content) {
    charInput(content);

    if (m_populater != 0) {
        QStringList strList;
        QStringList &refStrList = strList;
        m_populater->populateComboList(text(), strList);
        m_selectList->clear();
        m_selectList->addItems(strList);

        m_selectList->update();
    }
    update();
    setFocus();
}

void HWComboInput::backspacePressed() {

    if (text().length() > 0) {
        QString t1 = text();
        t1.chop(1);
        setText(t1);
    }
    //text().truncate();
    //QString t = text();
    contentAdded("");
}

void HWComboInput::enterPressed() {
    //m_selectList->setVisible(false);
    destroyList();
    m_qwerty->setVisible(false);
    m_keyboardActive = false;
}

void HWComboInput::focusInEvent(QFocusEvent * event) {
    int a = 100;
    //m_selectList->setVisible(true);

    if (!m_keyboardActive) {
        /*if (m_qwerty != 0) {
            delete m_qwerty;
            m_qwerty = 0;
        }*/
        if (m_qwerty == 0) {
            m_qwerty = new HWQwertyInput(m_centralWidget);
            m_qwerty->setFocalWidget(this);
            m_qwerty->positionAtBottom();
            m_qwerty->setAutoFillBackground(true);
            m_qwerty->autoFillBackground();
            //connect(m_qwerty, SIGNAL(contentAdded(QString)), this, SLOT(charInput(QString)));
            m_qwerty->setVisible(true);
            m_qwerty->setAlphaCapsOff();
            m_qwerty->update();
            m_qwerty->setListener(this);
            m_keyboardActive = true;
        } else {
            m_qwerty->setVisible(true);
            m_qwerty->setAlphaCapsOff();
            m_qwerty->update();
            m_qwerty->setListener(this);
        }
    }


    //connect(m_selectList, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(listItemSelected(QListWidgetItem*)));

    //connect(m_selectList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(listItemSelected(QListWidgetItem*)));
    createList();
}

void HWComboInput::createList() {
    if (m_selectList != 0) {
        destroyList();
    }
    m_selectList = new QListWidget(m_centralWidget);
    m_selectList->setAutoFillBackground(true);
    m_selectList->setVisible(true);
    m_selectList->setGeometry(0,0,360,320);
    connect(m_selectList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(listItemSelected(QListWidgetItem*)));
}

void HWComboInput::destroyList() {
    delete m_selectList;
    m_selectList = 0;

}

void HWComboInput::focusOutEvent(QFocusEvent * event) {
    /*int a = 100;
    if (!hasFocus()) {
        m_selectList->setVisible(false);
        m_qwerty->setVisible(false);
        m_keyboardActive = false;
    }*/
}

void HWComboInput::setGeometry ( const QRect & rect )  {
    QLabel::setGeometry(rect);

            //rect.x(), rect.y()+rect.height(), rect.width(), 100);
}

void HWComboInput::setTextAndUpdateSelection(QString s) {
    setText(s);
}

void HWComboInput::charInput(QString c) {
    setText(text() + c);
    QString s = text();
    m_selectList->clear();
    /*if (s.length() > 2) {
        for (int i = 0; i < m_countryInfo->length(); i++) {
            if (m_countryInfo->at(i).countryName->startsWith(s, Qt::CaseInsensitive)) {
                m_selectList->addItem(*m_countryInfo->at(i).countryName);
            }
        }
    }*/
    m_selectList->addItem("1");
    //m_selectList->addItems();
}

void HWComboInput::listItemSelected(QListWidgetItem* item) {
    setText(item->text());
    m_selectList->setVisible(false);
    m_qwerty->setVisible(false);
    m_keyboardActive = false;
    selectedChoice(item->text());
    //destroyList();
    //delete m_qwerty;

}

HWComboInput::~HWComboInput()
{
    /*
    if (m_selectList != 0) {
        delete m_selectList;
    }

    if (m_qwerty != 0) {
        delete m_qwerty;
        m_qwerty = 0;
    }*/
}
