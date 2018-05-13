#include <QtGui/QApplication>
#include "mainwindow.h"

#include <QMenuBar>
#include <QFile>
#include <QByteArray>
#include <QSplashScreen>



#include <fstream>

using namespace std;
ofstream logfile;
//#define MYDEBUG

#ifdef MYDEBUG
void SimpleLoggingHandler(QtMsgType type, const char *msg) {

    switch (type) {
        case QtDebugMsg:
            logfile << QTime::currentTime().toString().toAscii().data() << " Debug: " << msg << "\n";
            //logfile << "heapSize=" << User::Heap().Size();
            break;
        case QtCriticalMsg:
            logfile << QTime::currentTime().toString().toAscii().data() << " Critical: " << msg << "\n";
            break;
        case QtWarningMsg:
            logfile << QTime::currentTime().toString().toAscii().data() << " Warning: " << msg << "\n";
            break;
        case QtFatalMsg:
            logfile << QTime::currentTime().toString().toAscii().data() <<  " Fatal: " << msg << "\n";
            abort();
        }
    }
#endif
int main(int argc, char *argv[])
{
#ifdef MYDEBUG
    logfile.open("c:\\data\\astrologfile.txt", ios::app);
    qInstallMsgHandler(SimpleLoggingHandler);
#endif
    QApplication a(argc, argv);

    QPixmap splashPixmap(":/gfx/moonsplash10.png");
    QSplashScreen splash(splashPixmap);
    splash.setWindowFlags(splash.windowFlags() & Qt::WindowStaysOnTopHint);
    splash.showFullScreen();
    splash.showMessage("Wait...");
    qApp->processEvents();//This is used to accept a click on the screen so that user can cancel the screen

    QFile f(":/style/style.qss");
    bool ok = f.open(QIODevice::ReadOnly);
    QByteArray qssData = f.readAll();
    if (!qssData.isEmpty()) {
            a.setStyleSheet(qssData); //QString(qssData));
    }

    MainWindow w;
    //w.setWindowFlags(w.windowFlags() | Qt::WindowSoftkeysVisibleHint);

#if defined(Q_WS_S60)
    w.setWindowFlags(w.windowFlags() | Qt::WindowSoftkeysVisibleHint);
    w.showFullScreen(); //FullScreen();

#else
    w.showMaximized();

#endif
    splash.finish(&w);

    return a.exec();
}
