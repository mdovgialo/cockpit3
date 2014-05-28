#ifndef MAPINDICATOR_H
#define MAPINDICATOR_H
#include "genericindicator.h"
#include <QPixmap>
#include <QPainter>
#include <QWidget>
#include <QNetworkAccessManager>
class MapIndicator : public GenericIndicator
{
    Q_OBJECT
public:
    explicit MapIndicator(QJsonObject params, int nr, InstrumentPanel *parent = 0, bool edit=1, bool overlay=0);
    void update_ind(Gamestate*);
    virtual void wheelEvent(QWheelEvent *);
signals:

public slots:
    void hide_later();
    void got_image(QNetworkReply*);
protected:
    QWidget* mapObjects;
    bool mapValid;
    QPixmap *mappix;
    QNetworkAccessManager *manager;

};

#endif // MAPINDICATOR_H
