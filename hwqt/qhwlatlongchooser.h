#ifndef QHWLATLONGCHOOSER_H
#define QHWLATLONGCHOOSER_H

#include <QFrame>

namespace Ui {
    class QHWLatLongChooser;
}

class QHWLatLongChooser : public QFrame
{
    Q_OBJECT

public:
    explicit QHWLatLongChooser(QWidget *parent = 0);
    ~QHWLatLongChooser();

signals:
    void latLongSelected(int latitude, int longitude);
    void cancelled();

protected slots:
    void done();
    void cancel();

    void latDegDecMuch();
    void latDegDecStep();
    void latDegIncMuch();
    void latDegIncStep();

    void latMinDecMuch();
    void latMinDecStep();
    void latMinIncMuch();
    void latMinIncStep();

    void longDegDecMuch();
    void longDegDecStep();
    void longDegIncMuch();
    void longDegIncStep();

    void longMinDecMuch();
    void longMinDecStep();
    void longMinIncMuch();
    void longMinIncStep();

private:
    QString formatLatitude(int totalLatCents);
    QString formatLongitude(int totalLongCents);
    Ui::QHWLatLongChooser *ui;
    int curLat;
    int curLong;
    void updateLat(int);
    void updateLong(int);
};

#endif // QHWLATLONGCHOOSER_H
