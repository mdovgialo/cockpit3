#ifndef AIRBRAKEINDICATOR_H
#define AIRBRAKEINDICATOR_H
#include "flapsindicator.h"
class AirbrakeIndicator : public FlapsIndicator
{
    Q_OBJECT
public:
    explicit AirbrakeIndicator(QJsonObject params, int nr, InstrumentPanel *parent = 0, bool edit=1);
};

#endif // AIRBRAKEINDICATOR_H
