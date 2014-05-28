#ifndef TARGETDISTANCEINDICATOR_H
#define TARGETDISTANCEINDICATOR_H
#include "genericindicator.h"

class TargetDistanceIndicator : public GenericIndicator
{
    Q_OBJECT
public:
    explicit TargetDistanceIndicator(QJsonObject params, int nr, InstrumentPanel *parent = 0, bool edit=1, bool overlay=0);

signals:

public slots:
    void update_ind(Gamestate *);

};

#endif // TARGETDISTANCEINDICATOR_H
