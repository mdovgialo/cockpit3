#include "gamestate.h"

#include <iostream>
using namespace std;

Gamestate::Gamestate(QUrl url) : url(url)
{
    manager = new  QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(parse(QNetworkReply*)));
}

Gamestate::~Gamestate()
{
    delete manager;
}
void Gamestate::parse(QNetworkReply* reply)
{
    QString p = reply->url().path();
    if(p == QString("/state"))
    {
        state = QJsonDocument::fromJson(reply->readAll().data());
        //for debuging purposes
       /* QString bbbb = "{\"valid\": true,\
                \"aileron, %\": 0,\
                \"elevator, %\": -4,\
                \"rudder, %\": 1,\
                \"TAS, km/h\": 327,\
                \"IAS, km/h\": 281,\
                \"M\": 0.27,\
                \"flaps, %\":33,\
                \"gear, %\":44,\
                \"AoA, deg\": -0.7,\
                \"AoS, deg\": 0.1,\
                \"Ny\": 0.99,\
                \"Vy, m/s\": 5.8,\
                \"Wx, deg/s\": 0,\
                \"throttle 1, %\": 110,\
                \"RPM throttle 1, %\": 100,\
                \"radiator 1, %\": 81,\
                \"power 1, hp\": 2593.5,\
                \"RPM 1\": 2699,\
                \"manifold pressure 1, atm\": 1.37,\
                \"water temp 1, C\": 89,\
                \"oil temp 1, C\": 98,\
                \"pitch 1, deg\": 28.4,\
                \"thrust 1, kgs\": 1175,\
                \"efficiency 1, %\": 54,\
                \"throttle 2, %\": 110,\
                \"RPM throttle 2, %\": 100,\
                \"radiator 2, %\": 81,\
                \"power 2, hp\": 2592.7,\
                \"RPM 2\": 2699,\
                \"manifold pressure 2, atm\": 1.37,\
                \"water temp 2, C\": 89,\
                \"oil temp 2, C\": 98,\
                \"pitch 2, deg\": 28.4,\
                \"thrust 2, kgs\": 1175,\
                \"efficiency 2, %\": 54}\
                ";
        state = QJsonDocument::fromJson(QByteArray(bbbb.toStdString().c_str()));*/
    }
    else if(p == QString("/indicators"))
            {
                indicators = QJsonDocument::fromJson(reply->readAll().data());
            }
   emit parseFinished();
}

void Gamestate::update()
{
 url.setPath(QString("/state"));
 manager->get(QNetworkRequest(url));
 url.setPath(QString("/indicators"));
 manager->get(QNetworkRequest(url));
}
