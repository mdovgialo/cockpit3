#include "instrument_panel.h"
#include "genericindicator.h"
#include <iostream>
using namespace std;


InstrumentPanel::InstrumentPanel(QJsonObject settings, QWidget *parent, bool editMode):actual(settings.find("url").value().toString())
{
    this->editMode = editMode;
    int dt = settings.find("dt").value().toDouble();
    connect(&actual, SIGNAL(parseFinished()), this, SLOT(update()));

    QJsonObject instruments = settings["instruments"].toObject();
    QStringList l = instruments.keys();

    for(int i = 0;i<l.size();++i)
    {

        if(l.at(i)==QString("generic"))
        {
            cout << "Creating: " << l.at(i).toStdString()<<endl;
            GenericIndicator* ind = new GenericIndicator(instruments[l.at(i)].toObject(), this, editMode);

        }
    }

    updater = new QTimer();
    if(editMode)
    {
        editor* ed = new editor(settings, 0);
        ed->show();
    }
    else
    {
    connect(updater, SIGNAL(timeout()), &actual, SLOT(update()));
    updater->start(dt);
    cout << "Started updater"<<endl;
    }


}

void InstrumentPanel::update()
{
    emit panel_update(&actual);


}

InstrumentPanel::~InstrumentPanel()
{
    delete updater;
}
