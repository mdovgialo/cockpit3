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
