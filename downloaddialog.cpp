#include <QtGui>
 #include <QtNetwork>
#include <QTextStream>

 #include "downloaddialog.h"

 DownloadDialog::DownloadDialog(const QString & storageDir,
                                const QString & rootUrl,
                                QWidget *parent)
     : QDialog(parent),
     storageDir(storageDir),
     rootUrl(rootUrl),
     downloadingIndex(true)
 {
     statusLabel = new QLabel(tr("Press Update to connect to\n internet and download charts."));

     downloadButton = new QPushButton(tr("Update"));
     downloadButton->setDefault(true);
     quitButton = new QPushButton(tr("Done"));
     quitButton->setAutoDefault(false);

     buttonBox = new QDialogButtonBox;
     buttonBox->addButton(downloadButton, QDialogButtonBox::ActionRole);
     buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

     progressDialog = new QProgressDialog(this);

 #ifndef QT_NO_OPENSSL
     connect(&qnam, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
             this, SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));
 #endif
     connect(progressDialog, SIGNAL(canceled()), this, SLOT(cancelDownload()));
     connect(downloadButton, SIGNAL(clicked()), this, SLOT(go()));
     connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

     connect(this, SIGNAL(downloadNext(QString)), this, SLOT(downloadFile(QString)));
     //connect(this, SIGNAL(execCalled()), this, SLOT(go()));

     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addWidget(statusLabel);
     mainLayout->addWidget(buttonBox);
     setLayout(mainLayout);

     setWindowTitle(tr("Download Charts"));
 }

 void DownloadDialog::go() {
    statusLabel->setText(tr("Looking for new charts..."));
    downloadingIndex = true;
    downloadFile(rootUrl + "/index.txt");
 }


 void DownloadDialog::startRequest(QUrl url)
 {
     reply = qnam.get(QNetworkRequest(url));
     connect(reply, SIGNAL(finished()),
             this, SLOT(httpFinished()));
     connect(reply, SIGNAL(readyRead()),
             this, SLOT(httpReadyRead()));
     connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
             this, SLOT(updateDataReadProgress(qint64,qint64)));
 }

 void DownloadDialog::downloadFile(QString fullUrl)
 {
     url = fullUrl;

     QFileInfo fileInfo(url.path());
     QString fileName = fileInfo.fileName();
     if (fileName.isEmpty())
         fileName = "index.html";

     if (QFile::exists(storageDir + "/" + fileName)) {
         if (!downloadingIndex) {
             if (QMessageBox::question(this, tr("HTTP"),
                                       tr("There already exists a file called %1 in "
                                          "the current directory. Overwrite?").arg(fileName),
                                       QMessageBox::Yes|QMessageBox::No, QMessageBox::No)
                 == QMessageBox::No)
                 return;
         }
         QFile::remove(storageDir + "/" + fileName);
     }

     file = new QFile(storageDir + "/" + fileName);
     if (!file->open(QIODevice::WriteOnly)) {
         QMessageBox::information(this, tr("HTTP"),
                                  tr("Unable to save the file %1: %2.")
                                  .arg(fileName).arg(file->errorString()));
         //delete file;
         file = 0;
         return;
     }

     progressDialog->setWindowTitle(tr("HTTP"));
     progressDialog->setLabelText(tr("Downloading %1.").arg(fileName));
     downloadButton->setEnabled(false);

     // schedule the request
     httpRequestAborted = false;
     startRequest(url);
 }

 void DownloadDialog::cancelDownload()
 {
     statusLabel->setText(tr("Download canceled."));
     httpRequestAborted = true;
     reply->abort();
     downloadButton->setEnabled(true);
 }

 void DownloadDialog::httpFinished()
 {
     if (httpRequestAborted) {
         if (file) {
             file->close();
             file->remove();
             //delete file;
             file = 0;
         }
         //reply->deleteLater();
         progressDialog->hide();
         return;
     }

     progressDialog->hide();
     file->flush();
     file->close();

     QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
     if (reply->error()) {
         file->remove();
         QMessageBox::information(this, tr("HTTP"),
                                  tr("Download failed: %1.")
                                  .arg(reply->errorString()));
         downloadButton->setEnabled(true);
     } else if (!redirectionTarget.isNull()) {
         QUrl newUrl = url.resolved(redirectionTarget.toUrl());
         if (QMessageBox::question(this, tr("HTTP"),
                                   tr("Redirect to %1 ?").arg(newUrl.toString()),
                                   QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
             url = newUrl;
             //reply->deleteLater();
             file->open(QIODevice::WriteOnly);
             file->resize(0);
             startRequest(url);
             return;
         }
     } else {
         //QString fileName = QFileInfo(QUrl(urlLineEdit->text()).path()).fileName();
         //statusLabel->setText(tr("Downloaded %1.").arg(fileName));
         downloadButton->setEnabled(true);
     }

     if (downloadingIndex) {
        file->open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(file);
        QString s = in.readAll();
        file->close();
        QStringList chartList = s.split('\n');
        toGetList = new QStringList();
        QDir dir(storageDir);
        for (int i = 0; i < chartList.size(); i++) {
            if ((chartList.at(i).trimmed().length() > 4) && !dir.exists(chartList.at(i))) {
                toGetList->append(chartList.at(i));
            }
        }
        getCounter = 0;
        downloadingIndex = false;
    } else {
        getCounter++;
    }

     //reply->deleteLater();
     reply = 0;
     //delete file;
     file = 0;

     if (getCounter < toGetList->size()) {

         statusLabel->setText(tr("Downloading %1 (%2/%3).")
                              .arg(toGetList->at(getCounter))
                              .arg(getCounter+1).arg(toGetList->size()));
         emit downloadNext(rootUrl + "/" + toGetList->at(getCounter));
     } else {
         if (getCounter == 0) {
            statusLabel->setText(tr("There were no new charts to download"));
         } else {
             statusLabel->setText(tr("Downloaded %1 new charts.").arg(toGetList->size()));
         }
    }
 }

 void DownloadDialog::httpReadyRead()
 {
     // this slot gets called every time the QNetworkReply has new data.
     // We read all of its new data and write it into the file.
     // That way we use less RAM than when reading it at the finished()
     // signal of the QNetworkReply
     if (file)
         file->write(reply->readAll());
 }

 void DownloadDialog::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
 {
     if (httpRequestAborted)
         return;

     progressDialog->setMaximum(totalBytes);
     progressDialog->setValue(bytesRead);
 }

 #ifndef QT_NO_OPENSSL
 void DownloadDialog::sslErrors(QNetworkReply*,const QList<QSslError> &errors)
 {
     QString errorString;
     foreach (const QSslError &error, errors) {
         if (!errorString.isEmpty())
             errorString += ", ";
         errorString += error.errorString();
     }

     if (QMessageBox::warning(this, tr("HTTP"),
                              tr("One or more SSL errors has occurred: %1").arg(errorString),
                              QMessageBox::Ignore | QMessageBox::Abort) == QMessageBox::Ignore) {
         reply->ignoreSslErrors();
     }
 }
 #endif
