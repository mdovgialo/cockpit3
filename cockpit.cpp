#include "cockpit.h"
#include<iostream>
#include <QCoreApplication>
//#define SETTINGSFILE "C:/Users/Marian/Documents/warthunder_cockpit/cockpit30Qt/build-cockpit3-Desktop_Qt_5_3_0_MinGW_32bit-Release/release/settings.json"
#define SETTINGSFILE "settings.json"
#ifdef __ANDROID_API__
#define SETTINGSFILE "/mnt/sdcard/warthunder_cockpit.json"
#endif

using namespace std;
Cockpit::Cockpit(bool overlay):overlay(overlay)


    {


        QFile sf(SETTINGSFILE);
        sf.open(QIODevice::ReadOnly | QIODevice::Text);
        QJsonParseError e;
        settings = QJsonDocument::fromJson(sf.readAll(), &e);
        cout << e.errorString().toStdString()<<endl;

        Settings* s = new Settings(settings.object(), this,overlay);
        this->setCentralWidget(s);

        sf.close();



        QObject::connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(savesettings()));





    }
void Cockpit::savesettings()
{
     QFile saveFile(SETTINGSFILE);
     if(not overlay)
     {
         QJsonObject ss(settings.object());
         QJsonArray geo;
         geo.push_back(QJsonValue( this->pos().x()));
         geo.push_back(QJsonValue( this->pos().y()));
         geo.push_back(QJsonValue( this->width()));
         geo.push_back(QJsonValue( this->height()));
         geo.push_back(QJsonValue(double(this->isMaximized())));
         ss["window_geometry"] = geo;
         settings.setObject(ss);
     }
     saveFile.open(QIODevice::WriteOnly);
     saveFile.write(settings.toJson());
     cout << "writing json!" <<endl;
     saveFile.close();
}

void Cockpit::set_overlay(int check)
{


    if(check)
    {
        savesettings();

        Cockpit* nc = new Cockpit(1);
        nc->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

        nc->setAttribute(Qt::WA_TranslucentBackground, true);
        //nc->setAttribute(Qt::WA_TransparentForMouseEvents, true);

        //this->setStyleSheet("background-color: rgba(0, 0, 0, 100%);");
        nc->showFullScreen();
        this->deleteLater();


    }
    else
    {
        Cockpit* nc = new Cockpit();


        nc->show();
        this->deleteLater();
    }

}
