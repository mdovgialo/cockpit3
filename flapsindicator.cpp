#include "flapsindicator.h"


FlapsIndicator::FlapsIndicator(InstrumentPanel *parent) :
    QWidget(parent)
{
    connect(parent, SIGNAL(panel_update(Gamestate*)), this, SLOT( update(Gamestate*)));
}

void FlapsIndicator::update(Gamestate * actual)
{

}
