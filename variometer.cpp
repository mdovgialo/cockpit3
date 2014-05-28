#include "variometer.h"


Variometer::Variometer(QJsonObject params, int nr, InstrumentPanel *parent, bool edit) :
    FlapsIndicator(params, nr, parent, edit)
{

    text.setText("");
    text.resize(params["w"].toDouble(), params["h"].toDouble());
    this->resize(text.size());
    pic = new QPixmap("./images/vario.png");
    needlePix = new QPixmap("./images/vario_needle.png");


    painter = new QPainter();
    text.setPixmap(pic->scaled(text.size(), Qt::KeepAspectRatio));
}
void Variometer::update_ind(Gamestate* actual)
{
    if(actual->state.object()["valid"].toBool())
    {
        float vy = actual->state.object()["Vy, m/s"].toDouble();
        text.setPixmap(pic->scaled(text.size(), Qt::KeepAspectRatio));

        this->show();

        QPixmap dev = *(text.pixmap());
        QPixmap needlerot(needlePix->scaled(text.size(), Qt::KeepAspectRatio));
        painter->begin(&dev);

        painter->translate(text.size().height()/2, text.size().width()/2);
        painter->rotate(vy/100*180);
        painter->translate(-text.size().height()/2,-text.size().height()/2);
        painter->drawPixmap(0, 0, needlerot);
        /*
        QPen pen(QColor(255,0,0));
        //pen.setStyle(Qt::DashDotDotLine);
        pen.setCapStyle(Qt::RoundCap);
        pen.setWidthF(0.01*text.size().height());
        painter->setPen(pen);

        float vy = actual->state.object()["Vy, m/s"].toDouble();

        int x1, x2, y1, y2;
        int xc = 0.5*(text.size().height());
        int yc = 0.5*(text.size().height());
        x1 = xc +cos(M_PI*vy/100+M_PI-M_PI/2)*0.02*text.size().height();
        y1 = yc +sin(M_PI*vy/100+M_PI-M_PI/2)*0.02*text.size().height();
        x2 = xc + cos(M_PI*vy/100+M_PI)*0.4*text.size().height();
        y2 = yc +sin(M_PI*vy/100+M_PI)*0.4*text.size().height();

        painter->drawLine(x1, y1, x2, y2);

        x1 = xc +cos(M_PI*vy/100+M_PI+M_PI/2)*0.02*text.size().height();
        y1 = yc +sin(M_PI*vy/100+M_PI+M_PI/2)*0.02*text.size().height();
        x2 = xc + cos(M_PI*vy/100+M_PI)*0.4*text.size().height();
        y2 = yc +sin(M_PI*vy/100+M_PI)*0.4*text.size().height();
         painter->drawLine(x1, y1, x2, y2);
         */
        painter->end();
        text.setPixmap(dev);




    }
    if(!(actual->state.object()["valid"].toBool()) or actual->state.object()["Vy, m/s"].isNull())
        this->hide();
}
