#ifndef FLAPSINDICATOR_H
#define FLAPSINDICATOR_H
#include "genericindicator.h"
class FlapsIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit FlapsIndicator(InstrumentPanel *parent = 0);

signals:

public slots:
    void update(Gamestate*);

};

#endif // FLAPSINDICATOR_H
