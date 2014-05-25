#include "instrument_panel.h"
#include "genericindicator.h"
#include <iostream>
using namespace std;


InstrumentPanel::InstrumentPanel(QJsonObject settings, QWidget *parent):actual(settings.find("url").value().toString())
{
    int dt = settings.find("dt").value().toDouble();
    connect(&actual, SIGNAL(parseFinished()), this, SLOT(update()));

    QJsonObject::iterator f = settings["instruments"].toObject().begin();
    QJsonObject::iterator l = settings["instruments"].toObject().end();
    QString instrument;
    for (;f!=l;++f)
    {
        //cout << "Creating! "<< f.key().toStdString()<<endl;
        instrument = f.key();
        if (instrument == QString("generic"))
        {
            cout << "Creating! "<< f.key().toStdString()<<endl;
            new GenericIndicator(f.value().toObject(), this);

        }

    }

    updater = new QTimer();
    connect(updater, SIGNAL(timeout()), &actual, SLOT(update()));
    updater->start(dt);
    cout << "Started updater"<<endl;


}

void InstrumentPanel::update()
{
    emit panel_update(&actual);


}

InstrumentPanel::~InstrumentPanel()
{
    delete updater;
}
