#ifndef INSTRUMENT_PANEL_H
#define INSTRUMENT_PANEL_H

#include "gamestate.h"
#include <QUrl>
#include <QString>
#include <QWidget>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTimer>
#include <QStringList>
#include <QLayout>

class InstrumentPanel : public QWidget
{
    Q_OBJECT
    public:
        InstrumentPanel(QJsonObject settings, QWidget *parent = 0);
        ~InstrumentPanel();
    private:
        Gamestate actual;
        QTimer* updater;
        int dt;
        //vector<QWidget*> instruments;
    signals:
        void panel_update(Gamestate*);
    public slots:
        void update();



};


#endif // INSTRUMENT_PANEL_H
