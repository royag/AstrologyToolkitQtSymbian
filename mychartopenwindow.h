#ifndef MYCHARTOPENWINDOW_H
#define MYCHARTOPENWINDOW_H

#include <QWidget>

#include <QDialog>
#include <hwqt/qhwlistwidget.h>
#include <QLabel>
#include <hwqt/qhwlistselect.h>
#include <QResizeEvent>

class MyChartOpenWindow : public QFrame
{
    Q_OBJECT
public:
    explicit MyChartOpenWindow(QWidget *parent = 0, QString dir = QString(),
                               bool isDownloadable = false,
                               QString url = QString());
    ~MyChartOpenWindow();
    static QString getOpenFileName(
            QWidget * parent = 0,
            const QString & dir = QString(),
            bool isDownloadable = false,
            const QString & url = QString());
    QString selectedFileName;
    void reloadDir();
    void setFilenames(QStringList list);
    void setHeaderText(QString txt);
signals:
    void cancelled();
    void selectedFile(QString);
protected slots:
    void cancel();
    void selectPressed();
    void selectedName(QString);
    void longTappedName(QString);
    void downloadMore();
protected:
    virtual void focusInEvent ( QFocusEvent * event );
    virtual void resizeEvent ( QResizeEvent * event );
private:
    bool downloadable;
    QString downloadUrl;
    bool inDialog;
    QLabel* headerLabel;
    QHWListSelect* listSelect;
    //Ui::MyChartOpenDialog *ui;
    QAction* actionSelect;
    QAction* actionCancel;
    QString directory;
};

#endif // MYCHARTOPENWINDOW_H
