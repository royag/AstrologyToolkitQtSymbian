#include "hwqwertyinput.h"
#include "ui_hwqwertyinput.h"

#define UP_DOWN_NUM(u,d,n) (m_isNumeric ? n : (m_isCapsOn ? u : d))

HWQwertyInput::HWQwertyInput(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::HWQwertyInput)
{
    ui->setupUi(this);
    setAlphaCapsOff();
    update();

    m_focalWidget = 0;
    m_listener = 0;

    connect(ui->bQ, SIGNAL(clicked()), this, SLOT(pressedQ()));
    connect(ui->bW, SIGNAL(clicked()), this, SLOT(pressedW()));
    connect(ui->bE, SIGNAL(clicked()), this, SLOT(pressedE()));
    connect(ui->bR, SIGNAL(clicked()), this, SLOT(pressedR()));
    connect(ui->bT, SIGNAL(clicked()), this, SLOT(pressedT()));
    connect(ui->bY, SIGNAL(clicked()), this, SLOT(pressedY()));
    connect(ui->bU, SIGNAL(clicked()), this, SLOT(pressedU()));
    connect(ui->bI, SIGNAL(clicked()), this, SLOT(pressedI()));
    connect(ui->bO, SIGNAL(clicked()), this, SLOT(pressedO()));
    connect(ui->bP, SIGNAL(clicked()), this, SLOT(pressedP()));

    connect(ui->bA, SIGNAL(clicked()), this, SLOT(pressedA()));
    connect(ui->bS, SIGNAL(clicked()), this, SLOT(pressedS()));
    connect(ui->bD, SIGNAL(clicked()), this, SLOT(pressedD()));
    connect(ui->bF, SIGNAL(clicked()), this, SLOT(pressedF()));
    connect(ui->bG, SIGNAL(clicked()), this, SLOT(pressedG()));
    connect(ui->bH, SIGNAL(clicked()), this, SLOT(pressedH()));
    connect(ui->bJ, SIGNAL(clicked()), this, SLOT(pressedJ()));
    connect(ui->bK, SIGNAL(clicked()), this, SLOT(pressedK()));
    connect(ui->bL, SIGNAL(clicked()), this, SLOT(pressedL()));

    connect(ui->bZ, SIGNAL(clicked()), this, SLOT(pressedZ()));
    connect(ui->bX, SIGNAL(clicked()), this, SLOT(pressedX()));
    connect(ui->bC, SIGNAL(clicked()), this, SLOT(pressedC()));
    connect(ui->bV, SIGNAL(clicked()), this, SLOT(pressedV()));
    connect(ui->bB, SIGNAL(clicked()), this, SLOT(pressedB()));
    connect(ui->bN, SIGNAL(clicked()), this, SLOT(pressedN()));
    connect(ui->bM, SIGNAL(clicked()), this, SLOT(pressedM()));

    connect(ui->bSpace, SIGNAL(clicked()), this, SLOT(pressedSpace()));
    connect(ui->bSlash, SIGNAL(clicked()), this, SLOT(pressedSlash()));
    connect(ui->bDot, SIGNAL(clicked()), this, SLOT(pressedDot()));

    connect(ui->bBackspace, SIGNAL(clicked()), this, SLOT(pressedBackspace()));
    connect(ui->bEnter, SIGNAL(clicked()), this, SLOT(pressedEnter()));

    connect(ui->b123, SIGNAL(clicked()), this, SLOT(pressed123()));
    connect(ui->bShift, SIGNAL(clicked()), this, SLOT(pressedShift()));
}

void HWQwertyInput::pressedQ() { _contentAdded(UP_DOWN_NUM("Q","q","1")); }
void HWQwertyInput::pressedW() { _contentAdded(UP_DOWN_NUM("W","w","2")); }
void HWQwertyInput::pressedE() { _contentAdded(UP_DOWN_NUM("E","e","3")); }
void HWQwertyInput::pressedR() { _contentAdded(UP_DOWN_NUM("R","r","4")); }
void HWQwertyInput::pressedT() { _contentAdded(UP_DOWN_NUM("T","t","5")); }
void HWQwertyInput::pressedY() { _contentAdded(UP_DOWN_NUM("Y","y","6")); }
void HWQwertyInput::pressedU() { _contentAdded(UP_DOWN_NUM("U","u","7")); }
void HWQwertyInput::pressedI() { _contentAdded(UP_DOWN_NUM("I","i","8")); }
void HWQwertyInput::pressedO() { _contentAdded(UP_DOWN_NUM("O","o","9")); }
void HWQwertyInput::pressedP() { _contentAdded(UP_DOWN_NUM("P","p","0")); }

/*
    ui->bA->setText("(");
    ui->bS->setText(")");
    ui->bD->setText("+");
    ui->bF->setText("*");
    ui->bG->setText("=");
    ui->bH->setText("&");
    ui->bJ->setText("_");
    ui->bK->setText("-");
    ui->bL->setText("'");

    ui->bZ->setText("\"");
    ui->bX->setText("@");
    ui->bC->setText("?");
    ui->bV->setText("!");
    ui->bB->setText(";");
    ui->bN->setText(":");
    ui->bM->setText(",");
 */

void HWQwertyInput::pressedA() { _contentAdded(UP_DOWN_NUM("A","a","(")); }
void HWQwertyInput::pressedS() { _contentAdded(UP_DOWN_NUM("S","s",")")); }
void HWQwertyInput::pressedD() { _contentAdded(UP_DOWN_NUM("D","d","+")); }
void HWQwertyInput::pressedF() { _contentAdded(UP_DOWN_NUM("F","f","*")); }
void HWQwertyInput::pressedG() { _contentAdded(UP_DOWN_NUM("G","g","=")); }
void HWQwertyInput::pressedH() { _contentAdded(UP_DOWN_NUM("H","h","&")); }
void HWQwertyInput::pressedJ() { _contentAdded(UP_DOWN_NUM("J","j","_")); }
void HWQwertyInput::pressedK() { _contentAdded(UP_DOWN_NUM("K","k","-")); }
void HWQwertyInput::pressedL() { _contentAdded(UP_DOWN_NUM("L","l","'")); }

void HWQwertyInput::pressedZ() { _contentAdded(UP_DOWN_NUM("Z","z","\"")); }
void HWQwertyInput::pressedX() { _contentAdded(UP_DOWN_NUM("X","x","@")); }
void HWQwertyInput::pressedC() { _contentAdded(UP_DOWN_NUM("C","c","?")); }
void HWQwertyInput::pressedV() { _contentAdded(UP_DOWN_NUM("V","v","!")); }
void HWQwertyInput::pressedB() { _contentAdded(UP_DOWN_NUM("B","b",";")); }
void HWQwertyInput::pressedN() { _contentAdded(UP_DOWN_NUM("N","n",":")); }
void HWQwertyInput::pressedM() { _contentAdded(UP_DOWN_NUM("M","m",",")); }

void HWQwertyInput::pressedSpace() { _contentAdded(" "); }
void HWQwertyInput::pressedDot() { _contentAdded(UP_DOWN_NUM(".",".","#")); }
void HWQwertyInput::pressedSlash() { _contentAdded(UP_DOWN_NUM("/","/","%")); }

void HWQwertyInput::pressedShift() {
    if (isNumeric()) {
        // TODO: more chars
    } else {
        if (isAlphaCapsOff()) {
            setAlphaCapsOn();
        } else {
            setAlphaCapsOff();
        }
    }
}

void HWQwertyInput::pressed123() {
    if (isNumeric()) {
        setAlphaCapsOff();
    } else {
        setNumeric();
    }
}

void HWQwertyInput::pressedBackspace() {
    if (m_listener != 0) {
        m_listener->backspacePressed();
    }
}

void HWQwertyInput::pressedEnter() {
    if (m_listener != 0) {
        m_listener->enterPressed();
    }
}

void HWQwertyInput::_contentAdded(QString content) {
    //contentAdded(content);
    if (m_listener != 0) {
        m_listener->contentAdded(content);
    }
}

void HWQwertyInput::setListener(HWQwertyListener *listener) {
    m_listener = listener;
}

void HWQwertyInput::positionAtBottom() {
    setGeometry(0,640-320,360,320);
}

void HWQwertyInput::setFocalWidget(QWidget* focalWidget) {
    m_focalWidget = focalWidget;
    //m_focalWidget->focusWidget();
}

void HWQwertyInput::setAlphaCapsOff() {
    m_isNumeric = false;
    m_isCapsOn = false;

    ui->bQ->setText("q");
    ui->bW->setText("w");
    ui->bE->setText("e");
    ui->bR->setText("r");
    ui->bT->setText("t");
    ui->bY->setText("y");
    ui->bU->setText("u");
    ui->bI->setText("i");
    ui->bO->setText("o");
    ui->bP->setText("p");

    ui->bA->setText("a");
    ui->bS->setText("s");
    ui->bD->setText("d");
    ui->bF->setText("f");
    ui->bG->setText("g");
    ui->bH->setText("h");
    ui->bJ->setText("j");
    ui->bK->setText("k");
    ui->bL->setText("l");

    ui->bZ->setText("z");
    ui->bX->setText("x");
    ui->bC->setText("c");
    ui->bV->setText("v");
    ui->bB->setText("b");
    ui->bN->setText("n");
    ui->bM->setText("m");

    ui->bSpace->setText("space");
    ui->bSlash->setText("/");
    ui->bDot->setText(".");

    ui->bBackspace->setText("<-");
    ui->bEnter->setText("enter");

    ui->b123->setText("123");
    ui->bShift->setText("^");

    update();
}

void HWQwertyInput::setAlphaCapsOn() {
    m_isNumeric = false;
    m_isCapsOn = true;

    ui->bQ->setText("Q");
    ui->bW->setText("W");
    ui->bE->setText("E");
    ui->bR->setText("R");
    ui->bT->setText("T");
    ui->bY->setText("Y");
    ui->bU->setText("U");
    ui->bI->setText("I");
    ui->bO->setText("O");
    ui->bP->setText("P");

    ui->bA->setText("A");
    ui->bS->setText("S");
    ui->bD->setText("D");
    ui->bF->setText("F");
    ui->bG->setText("G");
    ui->bH->setText("H");
    ui->bJ->setText("J");
    ui->bK->setText("K");
    ui->bL->setText("L");

    ui->bZ->setText("Z");
    ui->bX->setText("X");
    ui->bC->setText("C");
    ui->bV->setText("V");
    ui->bB->setText("B");
    ui->bN->setText("N");
    ui->bM->setText("M");

    ui->bSpace->setText("SPACE");
    ui->bSlash->setText("/");
    ui->bDot->setText(".");

    ui->bBackspace->setText("<-");
    ui->bEnter->setText("ENTER");

    ui->b123->setText("123");
    ui->bShift->setText("^");

    update();
}

void HWQwertyInput::setNumeric() {
    m_isNumeric = true;
    m_isCapsOn = false;

    ui->bQ->setText("1");
    ui->bW->setText("2");
    ui->bE->setText("3");
    ui->bR->setText("4");
    ui->bT->setText("5");
    ui->bY->setText("6");
    ui->bU->setText("7");
    ui->bI->setText("8");
    ui->bO->setText("9");
    ui->bP->setText("0");

    ui->bA->setText("(");
    ui->bS->setText(")");
    ui->bD->setText("+");
    ui->bF->setText("*");
    ui->bG->setText("=");
    ui->bH->setText("&");
    ui->bJ->setText("_");
    ui->bK->setText("-");
    ui->bL->setText("'");

    ui->bZ->setText("\"");
    ui->bX->setText("@");
    ui->bC->setText("?");
    ui->bV->setText("!");
    ui->bB->setText(";");
    ui->bN->setText(":");
    ui->bM->setText(",");

    ui->bSpace->setText("space");
    ui->bSlash->setText("%");
    ui->bDot->setText("#");

    ui->bBackspace->setText("<-");
    ui->bEnter->setText("enter");

    ui->b123->setText("123");
    ui->bShift->setText("+");

    update();
}
bool HWQwertyInput::isAlphaCapsOff() {
    return (!isAlphaCapsOn()) && (!isNumeric());
            //(!m_isNumeric) && (!m_isCapsOn);
}
bool HWQwertyInput::isAlphaCapsOn() {
    return (!m_isNumeric) && m_isCapsOn;
}
bool HWQwertyInput::isNumeric() {
    return m_isNumeric;
}

HWQwertyInput::~HWQwertyInput()
{
    delete ui;
}
