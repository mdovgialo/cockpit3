#include "instrument_panel.h"
#include "genericindicator.h"
#include "flapsindicator.h"
#include "variometer.h"
#include "aviahorizonindicator.h"
#include "mapindicator.h"
#include <iostream>
#include "targetdistanceindicator.h"
#include <QByteArray>

using namespace std;


InstrumentPanel::InstrumentPanel(QJsonObject settings, QWidget *parent, bool editMode, bool overlay):
    actual(settings.find("url").value().toString()), overlay(overlay), settings(settings)
{
    this->editMode = editMode;
    int dt = settings.find("dt").value().toDouble();
    connect(&actual, SIGNAL(parseFinished()), this, SLOT(update_stuff()));
    connect(&actual, SIGNAL(mapParseFinished()), this, SLOT(map_updated()));
    QJsonArray instruments = settings["instruments"].toArray();
    if(!overlay and !editMode)
    {
        qApp->setStyleSheet("QWidget {color:white; }");
        parent->setStyleSheet("QMainWindow {background-color: black} ");
    }
    else if(overlay and !editMode)
    {
         qApp->setStyleSheet("QWidget {color:white}");
    }


    updater = new QTimer();
    if(editMode)
    {
        Editor* ed = new Editor(settings,this, parent);

        ed->show();
    }
    else
    {
    connect(updater, SIGNAL(timeout()), &actual, SLOT(update()));
    updater->start(dt);
    cout << "Started updater"<<endl;
    }


    for(int i = 0;i<instruments.size();++i)
    {
        GenericIndicator* inst=0;

        QJsonObject instrument = instruments[i].toObject();
        if(instrument["type"].toString()==QString("generic"))
        {
             inst = new GenericIndicator(instrument, i, this, editMode);

        }
        else if(instrument["type"].toString()==QString("flaps"))
        {
            inst = new FlapsIndicator(instrument, i, this, editMode);
        }
        else if(instrument["type"].toString()==QString("vario"))
        {
            inst = new Variometer(instrument, i, this, editMode);
        }
        else if(instrument["type"].toString()==QString("aviahorizon"))
        {
            inst = new AviahorizonIndicator(instrument, i, this, editMode);
        }
        else if(instrument["type"].toString()==QString("generic analogue"))
        {
            inst = new Variometer(instrument, i, this, editMode);
        }
        else if(instrument["type"].toString()==QString("map"))
        {
            inst = new MapIndicator(instrument, i, this, editMode, overlay);
        }
        else if(instrument["type"].toString()==QString("target"))
        {
            inst = new TargetDistanceIndicator(instrument, i, this, editMode, overlay);
        }
        if(overlay)
        {
            QGraphicsDropShadowEffect* ef = new QGraphicsDropShadowEffect(inst);
            ef->setBlurRadius(5);
            ef->setColor(QColor(0,0,0));
            ef->setXOffset(0.0);
            ef->setYOffset(0.0);
            inst->setGraphicsEffect(ef);
           // inst->setAttribute(Qt::WA_TransparentForMouseEvents);
        }

    }
    if(not editMode)
    {
        map_updated();
        update_stuff();
    }
    if(not overlay)
    {
        cout <<"setting geometry "<<endl;
        QJsonArray geo(settings["window_geometry"].toArray());

        if(geo[4].toBool())
        {
            parent->showMaximized();
        }
        else
        {
        parent->move(geo[0].toDouble(), geo[1].toDouble());
        parent->resize(geo[2].toDouble(), geo[3].toDouble());
        }
    }

}

void InstrumentPanel::update_stuff()
{
    emit panel_update(&actual);


}

void InstrumentPanel::map_updated()
{
    emit map_update(&actual);


}

bool InstrumentPanel::getOverlay()
{
    return overlay;


}

InstrumentPanel::~InstrumentPanel()
{
    delete updater;
}
