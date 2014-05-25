#include "cockpit.h"
#include<iostream>
#include <QCoreApplication>
//#define SETTINGSFILE "C:/Users/Marian/Documents/warthunder_cockpit/cockpit30Qt/build-cockpit3-Desktop_Qt_5_3_0_MinGW_32bit-Release/release/settings.json"
#define SETTINGSFILE "settings.json"

using namespace std;
Cockpit::Cockpit()


    {
        QFile sf(SETTINGSFILE);
        sf.open(QIODevice::ReadOnly | QIODevice::Text);
        QJsonParseError e;
        settings = QJsonDocument::fromJson(sf.readAll(), &e);
        cout << e.errorString().toStdString()<<endl;
        Settings* s = new Settings(settings.object(), this);
        this->setCentralWidget(s);
        sf.close();




    }
void Cockpit::savesettings()
{
     QFile saveFile(SETTINGSFILE);
     saveFile.open(QIODevice::WriteOnly);
     saveFile.write(settings.toJson());
     cout << "writing json!" <<endl;
     saveFile.close();
}

