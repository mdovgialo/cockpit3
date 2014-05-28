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
    //cout << reply->error()<<endl;
    if((not reply->error()))
    {
        QString p = reply->url().path();
        if(p == QString("/state"))
        {
            state = QJsonDocument::fromJson(reply->readAll().data());
            emit parseFinished();
        }
        else if(p == QString("/indicators"))
                {
                    indicators = QJsonDocument::fromJson(reply->readAll().data());
                    emit parseFinished();
                }
        else if(p == QString("/map_obj.json"))
                {
                    mapObj = QJsonDocument::fromJson(reply->readAll().data());
                    emit mapParseFinished();
                }
        else if(p == QString("/map_info.json"))
                {
                    mapInfo = QJsonDocument::fromJson(reply->readAll().data());
                    //emit mapParseFinished();
                }
    }

    reply->deleteLater();

}

void Gamestate::update()
{
 url.setPath(QString("/state"));
 manager->get(QNetworkRequest(url));
 url.setPath(QString("/indicators"));
 manager->get(QNetworkRequest(url));

 url.setPath(QString("/map_obj.json"));
 manager->get(QNetworkRequest(url));
 url.setPath(QString("/map_info.json"));
 manager->get(QNetworkRequest(url));
}
