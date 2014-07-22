#ifndef ANGLETOTARGETINDICATOR_H
#define ANGLETOTARGETINDICATOR_H
#include "genericindicator.h"
#include <QObject>

class angletotargetindicator : public GenericIndicator
{
    Q_OBJECT
public:
    explicit angletotargetindicator(QJsonObject params, int nr, InstrumentPanel *parent = 0, bool edit=1, bool overlay=0);


signals:

public slots:
    void update_ind(Gamestate *);


};

#endif // ANGLETOTARGETINDICATOR_H


