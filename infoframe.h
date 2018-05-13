#ifndef INFOFRAME_H
#define INFOFRAME_H

#include <QFrame>
#include "cpp_core/astrodefs.h"

namespace Ui {
    class InfoFrame;
}

class InfoFrame : public QFrame
{
    Q_OBJECT

public:
    explicit InfoFrame(QWidget *parent = 0);
    ~InfoFrame();
signals:
    void wantSearchForPlacement(int planet, int sign, int house, int aspect, int planet2);
public slots:
    void setBodyText(QString txt);
    void setEscapable(bool);
    void setLabelName(const QString &name);
protected slots:
    void setDialogMode(bool b);
    void okPressed();
    void openLink(QString);
    void searchGo();
    void searchCancel();
    void searchCharts();

private:
    Ui::InfoFrame *ui;
    QString searchQuery;
    bool m_escapable;
    QString searchForChartData;
};

#endif // INFOFRAME_H
