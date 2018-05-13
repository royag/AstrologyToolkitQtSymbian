#ifndef DOWNLOADDIALOG_H
#define DOWNLOADDIALOG_H

#include <QDialog>
 #include <QNetworkAccessManager>
 #include <QUrl>
#include <QStringList>

 class QDialogButtonBox;
 class QFile;
 class QLabel;
 class QLineEdit;
 class QProgressDialog;
 class QPushButton;
 class QSslError;
 class QAuthenticator;
 class QNetworkReply;


 class DownloadDialog : public QDialog
 {
     Q_OBJECT

 public:
     DownloadDialog(const QString & storageDir,
                    const QString & rootUrl,
                    QWidget *parent = 0);

     void startRequest(QUrl url);
 signals:
     void downloadNext(QString fullUrl);
 private slots:
     void go();
     void downloadFile(QString fullUrl);
     void cancelDownload();
     void httpFinished();
     void httpReadyRead();
     void updateDataReadProgress(qint64 bytesRead, qint64 totalBytes);
 #ifndef QT_NO_OPENSSL
     void sslErrors(QNetworkReply*,const QList<QSslError> &errors);
 #endif

 private:
     bool downloadingIndex;
     const QString & storageDir;
     const QString & rootUrl;
     QLabel *statusLabel;
     QProgressDialog *progressDialog;
     QPushButton *downloadButton;
     QPushButton *quitButton;
     QDialogButtonBox *buttonBox;

     QStringList *toGetList;
     int getCounter;

     QUrl url;
     QNetworkAccessManager qnam;
     QNetworkReply *reply;
     QFile *file;
     int httpGetId;
     bool httpRequestAborted;
 };

#endif // DOWNLOADDIALOG_H
