#ifndef COCKPIT_H
#define COCKPIT_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>
#include <QScrollArea>

#include <QFile>
#include "settings.h"
#include "instrument_panel.h"
#include <iostream>


using namespace std;

class Cockpit: public QMainWindow
{
    Q_OBJECT
    bool overlay;
public:

    explicit Cockpit(bool overlay=0);




public slots:
    void set_overlay(int);
    void savesettings();
    void set_dt(int dt)
    {
        QJsonObject t = settings.object();

        t["dt"] = dt;
        settings.setObject(t);

    }
    void set_url(QString url)
    {
        QJsonObject t = settings.object();
        t["url"] = url;
        settings.setObject(t);
    }

    void run_cockpit()
    {

        this->centralWidget()->deleteLater();
        InstrumentPanel* ip= new InstrumentPanel(settings.object(), this, 0, overlay);
        setCentralWidget(ip);

    }

    void run_edit(QJsonObject* newsettings=0)
    {

        if (newsettings)
        {
            settings.setObject(*newsettings);
        }

        this->centralWidget()->deleteLater();
        InstrumentPanel* ip= new InstrumentPanel(settings.object(), this, true, overlay);
        setCentralWidget(ip);

    }
    void run_settings(QJsonObject* newsettings=0)
    {

        if (newsettings)
        {
            settings.setObject(*newsettings);
        }
        this->centralWidget()->deleteLater();
        Settings* s = new Settings(settings.object(), this, overlay);
        this->setCentralWidget(s);

    }

protected:
    QJsonDocument settings;
};

#endif // COCKPIT_H
