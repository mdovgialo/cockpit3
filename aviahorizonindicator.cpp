#include "aviahorizonindicator.h"
#include <cmath>
AviahorizonIndicator::AviahorizonIndicator(QJsonObject params, int nr, InstrumentPanel *parent, bool edit) :
    Variometer(params, nr, parent, edit)
{
}
void AviahorizonIndicator::update_ind(Gamestate* actual)
{
    if(actual->indicators.object()["valid"].toBool())
    {
        float w = actual->indicators.object()["aviahorizon_roll"].toDouble();
        float h = actual->indicators.object()["aviahorizon_pitch"].toDouble();
        text.setPixmap(pic->scaled(text.size(), Qt::KeepAspectRatio));

        this->show();

        QPixmap dev = *(text.pixmap());

        QPixmap needlerot(needlePix->scaled(text.size(), Qt::KeepAspectRatio));
        painter->begin(&dev);

        painter->translate(text.size().height()/2, text.size().width()/2);
        painter->rotate(-w);
        painter->translate(-text.size().height()/2,-text.size().height()/2);

        painter->translate(0, h/90*text.size().height()/2);

        painter->drawPixmap(0,0, needlerot);
        painter->end();
        text.setPixmap(dev);
        //text.move(0, h/90*text.size().height()/2);




    }
    if(!(actual->indicators.object()["valid"].toBool()) or actual->indicators.object()["aviahorizon_roll"].isNull())
        this->hide();
}
