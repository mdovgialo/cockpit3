#include "mapindicator.h"
#include <iostream>
#include <QTimer>
#include <cmath>
#include <QFont>
#include "instrument_panel.h"
using namespace std;

MapIndicator::MapIndicator(QJsonObject params, int nr, InstrumentPanel *parent, bool edit, bool overlay) :
    GenericIndicator(params, nr, parent, edit, overlay)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(got_image(QNetworkReply*)));


    disconnect(parent, SIGNAL(panel_update(Gamestate*)), this, SLOT(update_ind(Gamestate*)));
    connect(parent, SIGNAL(map_update(Gamestate*)), this, SLOT(update_ind(Gamestate*)));
    text.setText("");
    text.resize(params["w"].toDouble(), params["h"].toDouble());
    mapObjects = new QWidget(this);
    mapObjects->resize(text.size());
    mapObjects->move(0,0);
    this->resize(text.size());
    QPixmap p(size());
    p.fill(QColor(100, 100,100, 100));
    text.setPixmap(p);
    this->mapValid = false;
}

void MapIndicator::update_ind(Gamestate* actual)
{

    QJsonArray mapObj = actual->mapObj.array();
    int player = -1;
    bool playerTank = 0;

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



    if(mapObj.isEmpty() or player==-1 or (!playerTank and overlay))
    {
        mapValid = false;
        this->hide();

    }
    else if ((!overlay) or playerTank)
    {
        if(mapValid==false)
        {
            if(this->overlay)
            {
                QPixmap n(text.size());
                n.fill(QColor(0,0,0,0));
                text.setPixmap(n);
                cout << "Setting empty pixmap"<<endl;
            }
            else
            {

                QUrl url(dynamic_cast<InstrumentPanel*>(this->parent())->settings["url"].toString()+QString("/map.img"));
                QNetworkRequest request(url);
                cout << "Downloading image " << request.url().toString().toStdString()<<endl;
                manager->get(request);
            }


        }
        //cout << "Painting map Object!"<<endl;
        double playerX = mapObj[player].toObject()["x"].toDouble();
        double playerY = mapObj[player].toObject()["y"].toDouble();

        qDeleteAll(mapObjects->findChildren<QLabel*>());

        for (int i =0; i<mapObj.size(); ++i)
        {

           QLabel* obj; ;

           double x = mapObj[i].toObject()["x"].toDouble();
           double y = mapObj[i].toObject()["y"].toDouble();
           int mapX = x*this->size().width();
           int mapY =  y*this->size().height();
           int dist = sqrt((x-playerX)*mapW*(x-playerX)*mapW+(y-playerY)*mapH*(y-playerY)*mapW);
           //cout << dist<<endl;
            QWidget* obscure =  mapObjects->childAt(mapX, mapY);
           int obscureX = text.fontMetrics().size(Qt::TextSingleLine, "00").width();
           int obscureY = text.fontMetrics().size(Qt::TextSingleLine, "00").height();
           QWidget* obscure2 =  mapObjects->childAt(mapX+obscureX, mapY+obscureY);
           QWidget* obscure3 =  mapObjects->childAt(mapX-obscureX, mapY-obscureY);
           QWidget* obscure4 =  mapObjects->childAt(mapX-obscureX, mapY+obscureY);
           QWidget* obscure5 =  mapObjects->childAt(mapX+obscureX, mapY-obscureY);

           if(!(obscure or obscure2 or obscure3 or obscure4 or obscure5))
           {
               obj = new QLabel(mapObjects);
               obj->setText( QString::number(dist));
               //

               obj->move(mapX, mapY);
               obj->show();


           }

           if(!overlay)
           {
               obj = new QLabel(mapObjects);
               if( mapObj[i].toObject()["icon_bg"].toString().indexOf("Target")>-1)
               {
                   obj->setStyleSheet(QString("QLabel { color: gold}"));
               }
               else
               {
                obj->setStyleSheet(QString("QLabel { color: ") + mapObj[i].toObject()["color"].toString()+QString("}"));
               }

               if(mapObj[i].toObject()["type"].toString() == QString("aircraft"))
               {
                    obj->setText("^");
               }
               else if(mapObj[i].toObject()["type"].toString() == QString("ground_model"))
               {
                    obj->setText("=");
               }

               if(mapObj[i].toObject()["icon"].toString() == QString("Player"))
               {
                     obj->setText("o");
                     obj->setStyleSheet(QString("QLabel { font: bold; color: green}"));
               }



               //obj->setStyleSheet(QString("QLabel { color: ") + mapObj[i].toObject()["color"].toString()+QString("}"));
               obj->move(mapX-5, mapY-5);
               obj->show();
           }

           if( mapObj[i].toObject()["icon_bg"].toString().indexOf("Target")>-1)
           {
               obj = new QLabel(mapObjects);
               obj->setText( QString("Target distance: ")+QString::number(dist));
              // obj->setStyleSheet(QString("QLabel { color: ") + mapObj[i].toObject()["color"].toString()+QString("}"));

               obj->move(0,0);
               obj->show();

               obj->setStyleSheet(QString("QLabel { font: bold 15px; color: red}"));
               obj->resize(obj->sizeHint());
           }

        }
        mapObjects->raise();
        this->show();
        mapValid = true;

    }
}
void MapIndicator::hide_later()
{
    if(!mapValid)
    {
        this->hide();
    }
}

void MapIndicator::wheelEvent(QWheelEvent* e)
{
    if(editMode)
    {
        //std::cout <<"Resizing " <<text.size().width()<<std::endl;
        float diff = e->angleDelta().y()/120;
        QSize d(diff, diff);
        std::cout << diff <<std::endl;
        QSize old = this->size();
        text.resize(old+=d);
        QPixmap p(size());
        p.fill(QColor(100, 100,100, 100));
        text.setPixmap(p);
        mapObjects->resize(text.size());

        this->resize(text.size());



    }
}
void MapIndicator::got_image(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {

        cout << "getting IMAGE"<<endl;

        QByteArray Data = reply->readAll();
        cout <<Data.size()<<"size"<<endl;
        QPixmap pixmap;

        cout << "Succes? " << pixmap.loadFromData(Data,0,Qt::ColorOnly	)<< endl;

        text.setPixmap(pixmap.scaled(text.size(), Qt::KeepAspectRatio));
        text.repaint();
        cout <<text.size().width()<<endl;
    }
    else
        this->mapValid = false;
}
