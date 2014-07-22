#include "angletotargetindicator.h"


#include <cmath>
angletotargetindicator::angletotargetindicator(QJsonObject params, int nr, InstrumentPanel *parent, bool edit, bool overlay) :
    GenericIndicator(params, nr, parent, edit, overlay)
{
    this->fonts = params["fonts"].toDouble();

    if(params["text"].toString().size())
    {
        text.setText( params["text"].toString()+QString("0000"));
    }
    else
    {
     text.setText("Angle: 000000");
     }

    QFont f = text.font();
    f.setPointSizeF(this->fonts);
    text.setFont(f);
    text.resize((text.fontMetrics().boundingRect(text.text()).size()*=1.1)+=QSize(20, 20));
    //setGeometry(this->x(), this->y(),text.size().width(), text.size().height());
    this->move(params["x"].toDouble(), params["y"].toDouble());
    this->resize(text.size());
    text.move(0,0);
    connect(parent, SIGNAL(panel_update(Gamestate*)), this, SLOT(update_ind(Gamestate*)));



    disconnect(parent, SIGNAL(panel_update(Gamestate*)), this, SLOT(update_ind(Gamestate*)));
    connect(parent, SIGNAL(map_update(Gamestate*)), this, SLOT(update_ind(Gamestate*)));
}

void angletotargetindicator::update_ind(Gamestate *actual)
{
    QJsonArray mapObj = actual->mapObj.array();

    int player = -1;
    bool playerTank = 0;
    bool validTarget=false;

    float mapW = actual->mapInfo.object()["map_max"].toArray()[0].toDouble() - actual->mapInfo.object()["map_min"].toArray()[0].toDouble();
    float mapH = actual->mapInfo.object()["map_max"].toArray()[1].toDouble() - actual->mapInfo.object()["map_min"].toArray()[1].toDouble();


    for (int i =0; i<mapObj.size(); ++i)
    {
        if(mapObj[i].toObject()["icon"].toString() == QString("Player"))
        {
            player = i;
            if(mapObj[i].toObject()["type"].toString()==QString("ground_model"))
            {
                playerTank = 1;
            }
            break;
        }

    }
    if(mapObj.isEmpty() or player==-1 or (!playerTank))
    {
        this->hide();

    }
    else
    {
        double playerX = mapObj[player].toObject()["x"].toDouble();
        double playerY = mapObj[player].toObject()["y"].toDouble();
        double playerAngle = (atan2(mapObj[player].toObject()["dy"].toDouble(), mapObj[player].toObject()["dx"].toDouble())*180)/M_PI;



        for (int i =0; i<mapObj.size(); ++i)
        {


           double x = mapObj[i].toObject()["x"].toDouble();
           double y = mapObj[i].toObject()["y"].toDouble();
           double enemyAngle = (atan2((y-playerY), (x-playerX))*180)/M_PI;
           int relAngle =playerAngle - enemyAngle;
           //int dist = sqrt((x-playerX)*mapW*(x-playerX)*mapW+(y-playerY)*mapH*(y-playerY)*mapW);

           if( mapObj[i].toObject()["icon_bg"].toString().indexOf("Target")>-1)
           {
                if(params["text"].toString().size())
                {
                    text.setText( params["text"].toString()+QString::number(relAngle));
                }
                else
                {
               text.setText( QString("Angle: ")+QString::number(relAngle));
              }
               // obj->setStyleSheet(QString("QLabel { color: ") + mapObj[i].toObject()["color"].toString()+QString("}"));


               //obj->setStyleSheet(QString("QLabel { font: bold 15px; color: red}"));
              // obj->resize(obj->sizeHint());
               validTarget = true;
               this->show();
               break;
           }
        }
        if(!validTarget)
        {
            this->hide();
        }

    }

}


