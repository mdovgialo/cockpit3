#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>
#include <QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
class Gamestate : public QWidget
{
    Q_OBJECT
public:

    Gamestate(QUrl url);
    ~Gamestate();

    QJsonDocument indicators;
    QJsonDocument state;
    QJsonDocument mapInfo;
    QJsonDocument mapObj;
signals:
    void parseFinished();
    void mapParseFinished();
private:
    QUrl url;
    QNetworkAccessManager *manager;
public slots:
    void update();
    //void mapUpdate();

public slots:
    void parse(QNetworkReply*);
};

#endif // GAMESTATE_H
