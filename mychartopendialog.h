#ifndef MYCHARTOPENDIALOG_H
#define MYCHARTOPENDIALOG_H

#include <QDialog>
#include <hwqt/qhwlistwidget.h>
#include <QLabel>
#include <hwqt/qhwlistselect.h>
#include <QResizeEvent>

namespace Ui {
    class MyChartOpenDialog;
}

class MyChartOpenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyChartOpenDialog(QWidget *parent = 0, const QString & dir = QString(),
                               bool isDownloadable = false,
                               const QString & url = QString());
    ~MyChartOpenDialog();
    static QString getOpenFileName(
            QWidget * parent = 0,
            const QString & dir = QString(),
            bool isDownloadable = false,
            const QString & url = QString());
    QString selectedFileName;
    virtual void resizeEvent(QResizeEvent *);
protected slots:
    void cancel();
    void selectPressed();
    void selectedName(QString);
    void longTappedName(QString);
    void downloadMore();
private:
    bool downloadable;
    const QString & downloadUrl;
    bool inDialog;
    QLabel* headerLabel;
    QHWListSelect* listSelect;
    Ui::MyChartOpenDialog *ui;
    QAction* actionSelect;
    QAction* actionCancel;
    const QString & directory;
};

#endif // MYCHARTOPENDIALOG_H
