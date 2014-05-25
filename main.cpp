#include "settings.h"
#include <QApplication>
#include <QtGui>
#include <QMainWindow>
#include "instrument_panel.h"
#include "cockpit.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QString>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Cockpit *window = new Cockpit;
    //window->setWindowFlags(window->windowFlags() |  Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    //window->setAttribute(Qt::WA_TranslucentBackground);
    //window->setStyleSheet("background-color: rgba(0, 0, 0, 100%);");

    //InstrumentPanel* panel = new InstrumentPanel(QUrl("http://localhost:8111") , 10);

    QObject::connect(&a, SIGNAL(aboutToQuit()), window, SLOT(savesettings()));
    window->show();

    return a.exec();
}
