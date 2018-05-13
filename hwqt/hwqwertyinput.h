#ifndef HWQWERTYINPUT_H
#define HWQWERTYINPUT_H

#include <QFrame>

namespace Ui {
    class HWQwertyInput;
}

class HWQwertyListener {
public:
    virtual void contentAdded(QString content) {};
    virtual void backspacePressed() {};
    virtual void enterPressed() {};
};

class HWQwertyInput : public QFrame, HWQwertyListener
{
    Q_OBJECT

public:
    explicit HWQwertyInput(QWidget *parent = 0);
    ~HWQwertyInput();
    void positionAtBottom();
    void setFocalWidget(QWidget* focalWidget);
    void setListener(HWQwertyListener* listener);
/*signals:
    void contentAdded(QString content);
    void backspacePressed();
    void enterPressed();*/

    bool isAlphaCapsOn();
    bool isAlphaCapsOff();
    bool isNumeric();
    void setAlphaCapsOn();
    void setAlphaCapsOff();
    void setNumeric();
private:
    Ui::HWQwertyInput *ui;
    QWidget *m_focalWidget;
    void _contentAdded(QString content);
    HWQwertyListener* m_listener;
    bool m_isCapsOn;
    bool m_isNumeric;


private slots:
    void pressedQ();
    void pressedW();
    void pressedE();
    void pressedR();
    void pressedT();
    void pressedY();
    void pressedU();
    void pressedI();
    void pressedO();
    void pressedP();

    void pressedA();
    void pressedS();
    void pressedD();
    void pressedF();
    void pressedG();
    void pressedH();
    void pressedJ();
    void pressedK();
    void pressedL();

    void pressedZ();
    void pressedX();
    void pressedC();
    void pressedV();
    void pressedB();
    void pressedN();
    void pressedM();

    void pressedEnter();
    void pressedBackspace();
    void pressedShift();
    void pressed123();
    void pressedSpace();
    void pressedDot();
    void pressedSlash();

};

#endif // HWQWERTYINPUT_H
