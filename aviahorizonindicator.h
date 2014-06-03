#ifndef AVIAHORIZONINDICATOR_H
#define AVIAHORIZONINDICATOR_H
#include "variometer.h"

class AviahorizonIndicator : public Variometer
{
    Q_OBJECT
public:
    explicit AviahorizonIndicator(QJsonObject params, int nr, InstrumentPanel *parent = 0, bool edit=1);

signals:

public slots:
    void update_ind(Gamestate* actual);

};

#endif // AVIAHORIZONINDICATOR_H
