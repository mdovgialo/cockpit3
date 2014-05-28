#ifndef VARIOMETER_H
#define VARIOMETER_H
#include "flapsindicator.h"
class Variometer : public FlapsIndicator
{
    Q_OBJECT
protected:
    QPixmap* needlePix;
    QLabel needle;
public:
    explicit Variometer(QJsonObject params, int nr, InstrumentPanel *parent = 0, bool edit=1);

signals:

public slots:
    void update_ind(Gamestate*);
};

#endif // VARIOMETER_H
