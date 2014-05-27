#ifndef FLAPSINDICATOR_H
#define FLAPSINDICATOR_H

#include "genericindicator.h"
#include <QPixmap>
#include <QPainter>
class FlapsIndicator : public GenericIndicator
{
    Q_OBJECT
protected:
    QPixmap* pic;
    QPainter* painter;
public:
    explicit FlapsIndicator(QJsonObject params, int nr, InstrumentPanel *parent = 0, bool edit=1);
    void update_ind(Gamestate*);
    virtual void wheelEvent(QWheelEvent *);
signals:

public slots:


};

#endif // FLAPSINDICATOR_H
