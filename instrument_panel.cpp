#include "instrument_panel.h"
#include "genericindicator.h"
#include "flapsindicator.h"
#include "variometer.h"
#include <iostream>

using namespace std;


InstrumentPanel::InstrumentPanel(QJsonObject settings, QWidget *parent, bool editMode, bool overlay):
    actual(settings.find("url").value().toString()), overlay(overlay)
{
    this->editMode = editMode;
    int dt = settings.find("dt").value().toDouble();
    connect(&actual, SIGNAL(parseFinished()), this, SLOT(update()));

    QJsonArray instruments = settings["instruments"].toArray();
    if(!overlay and !editMode)
    {
        qApp->setStyleSheet("QWidget {color:white; background-color: black} ");
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
            cout << "Creating: " << instrument["type"].toString().toStdString()<<endl;
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
        if(overlay)
        {
            QGraphicsDropShadowEffect* ef = new QGraphicsDropShadowEffect(inst);
            ef->setBlurRadius(5);
            ef->setColor(QColor(0,0,0));
            ef->setXOffset(0.0);
            ef->setYOffset(0.0);
            inst->setGraphicsEffect(ef);
        }

    }









}

void InstrumentPanel::update()
{
    emit panel_update(&actual);


}

bool InstrumentPanel::getOverlay()
{
    return overlay;


}

InstrumentPanel::~InstrumentPanel()
{
    delete updater;
}
