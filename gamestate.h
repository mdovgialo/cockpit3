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
signals:
    void parseFinished();
private:
    QUrl url;
    QNetworkAccessManager *manager;
public slots:
    void update();
public slots:
    void parse(QNetworkReply*);
};

#endif // GAMESTATE_H
