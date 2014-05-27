#include "variometer.h"
#include <cmath>

Variometer::Variometer(QJsonObject params, int nr, InstrumentPanel *parent, bool edit) :
    FlapsIndicator(params, nr, parent, edit)
{

    text.setText("");
    text.resize(params["w"].toDouble(), params["h"].toDouble());
    this->resize(text.size());
    pic = new QPixmap("./images/vario.png");
    painter = new QPainter();
    text.setPixmap(pic->scaled(text.size(), Qt::KeepAspectRatio));
}
void Variometer::update_ind(Gamestate* actual)
{
    if(actual->state.object()["valid"].toBool())
    {
        text.setPixmap(pic->scaled(text.size(), Qt::KeepAspectRatio));
        this->show();

        QPixmap dev = *(text.pixmap());
        painter->begin(&dev);
        QPen pen(QColor(255,0,0));
        pen.setStyle(Qt::DashDotDotLine);
        pen.setCapStyle(Qt::RoundCap);
        pen.setWidthF(0.01*text.size().height());
        painter->setPen(pen);

        float vy = actual->state.object()["Vy, m/s"].toDouble();

        int x1, x2, y1, y2;
        x1 = 0.5*(text.size().height());
        y1 = 0.5*(text.size().height());
        x2 = x1 + cos(M_PI*vy/100+M_PI)*0.4*text.size().height();
        y2 = y1 +sin(M_PI*vy/100+M_PI)*0.4*text.size().height();

        painter->drawLine(x1, y1, x2, y2);
        painter->end();
        text.setPixmap(dev);




    }
    if(!(actual->state.object()["valid"].toBool()) or actual->state.object()["Vy, m/s"].isNull())
        this->hide();
}
