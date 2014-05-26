#ifndef COCKPIT_H
#define COCKPIT_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>

#include <QFile>
#include "settings.h"
#include "instrument_panel.h"
#include <iostream>
using namespace std;

class Cockpit: public QMainWindow
{
    Q_OBJECT

public:

    explicit Cockpit();




public slots:
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
        InstrumentPanel* ip= new InstrumentPanel(settings.object(), this);
        setCentralWidget(ip);
    }

private:
    QJsonDocument settings;
};

#endif // COCKPIT_H
