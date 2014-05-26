#ifndef FLAPSINDICATOR_H
#define FLAPSINDICATOR_H
#include "genericindicator.h"
class FlapsIndicator : public GenericIndicator
{
    Q_OBJECT
public:
    explicit FlapsIndicator(QJsonObject params, int nr, InstrumentPanel *parent = 0, bool edit=1);

signals:

public slots:


};

#endif // FLAPSINDICATOR_H
