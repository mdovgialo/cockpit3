#ifndef INSTRUMENT_PANEL_H
#define INSTRUMENT_PANEL_H


#include <QUrl>
#include <QString>
#include <QWidget>
#include <QJsonObject>
#include <QJsonArray>


#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QToolButton>


#include <QJsonDocument>
#include <QTimer>
#include <QStringList>
#include <QLayout>
#include "gamestate.h"
#include "editor.h"
#include <QApplication>
#include <QGraphicsDropShadowEffect>



class InstrumentPanel : public QWidget
{
    Q_OBJECT
    public:
        InstrumentPanel(QJsonObject settings, QWidget *parent = 0, bool editMode=0, bool overlay=0);
        ~InstrumentPanel();
        bool getOverlay();
    private:
        Gamestate actual;
        bool overlay;
        QTimer* updater;
        bool editMode;
        int dt;
        //vector<QWidget*> instruments;
    signals:
        void panel_update(Gamestate*);
    public slots:
        void update();



};






#endif // INSTRUMENT_PANEL_H
