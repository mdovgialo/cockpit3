#include "variometer.h"


Variometer::Variometer(QJsonObject params, int nr, InstrumentPanel *parent, bool edit) :
    FlapsIndicator(params, nr, parent, edit)
{

    text.setText("");
    text.resize(params["w"].toDouble(), params["h"].toDouble());
    this->resize(text.size());

    pic = new QPixmap(params["back_im"].toString());

    needlePix = new QPixmap(params["needle_im"].toString());
    zeroangl=params["zeroangl"].toDouble();
    maxangl=params["maxangl"].toDouble();
    maxanglvalue=params["maxanglvalue"].toDouble();


    painter = new QPainter();
    text.setPixmap(pic->scaled(text.size(), Qt::KeepAspectRatio));
}
void Variometer::update_ind(Gamestate* actual)
{
    if(actual->state.object()["valid"].toBool())
    {
        float vy = actual->state.object()[params["ind_name"].toString()].toDouble();
        text.setPixmap(pic->scaled(text.size(), Qt::KeepAspectRatio));

        this->show();

        QPixmap dev = *(text.pixmap());
        QPixmap needlerot(needlePix->scaled(text.size(), Qt::KeepAspectRatio));
        painter->begin(&dev);

        painter->translate(text.size().height()/2, text.size().width()/2);
        painter->rotate(vy/maxanglvalue*maxangl+zeroangl);
        painter->translate(-text.size().height()/2,-text.size().height()/2);
        painter->drawPixmap(0, 0, needlerot);

        painter->end();
        text.setPixmap(dev);




    }
    if(!(actual->state.object()["valid"].toBool()) or actual->state.object()[params["ind_name"].toString()].isNull())
        this->hide();
}
