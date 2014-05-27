#include "flapsindicator.h"
#include <cmath>
#include <iostream>
FlapsIndicator::FlapsIndicator(QJsonObject params, int nr, InstrumentPanel *parent, bool edit) :
    GenericIndicator(params, nr, parent, edit)
{
    text.setText("");
    text.resize(params["w"].toDouble(), params["h"].toDouble());
    this->resize(text.size());
    pic = new QPixmap("./images/flaps.png");
    painter = new QPainter();
    text.setPixmap(pic->scaled(text.size(), Qt::KeepAspectRatio));


}

void FlapsIndicator::update_ind(Gamestate* actual)
{
    if(actual->state.object()["valid"].toBool())
    {
        text.setPixmap(pic->scaled(text.size(), Qt::KeepAspectRatio));
        this->show();

        QPixmap dev = *(text.pixmap());
        painter->begin(&dev);
        QPen pen(QColor(255,0,0));
        pen.setWidthF(0.3/4.8*text.size().height());
        painter->setPen(pen);

        int flaps = actual->state.object()["flaps, %"].toDouble();
        int airbrake = actual->state.object()["airbrake, %"].toDouble();
        int gear = actual->state.object()["gear, %"].toDouble();


        int x1, x2, y1, y2;

        if(flaps>0)
        {


            x1 = 3.0/6.4*text.size().width();
            y1 = 2.3/4.8*text.size().height();
            x2 = x1+cos(M_PI/2*flaps/100.0)*0.4*text.size().width();
            y2 = y1+sin(M_PI/2*flaps/100.0)*0.4*text.size().width();


            painter->drawLine(x1, y1, x2, y2);



        }
        if(airbrake>0)
        {
           x1 = .3/6.4*text.size().width();
            y1 = 2.18/4.8*text.size().height();
            x2 = x1+cos(M_PI/2*airbrake/100.0)*0.2*text.size().width();
            y2 = y1+sin(M_PI/2*airbrake/100.0)*0.2*text.size().width();
            painter->drawLine(x1, y1, x2, y2);
            x1 = .3/6.4*text.size().width();
             y1 = 2.18/4.8*text.size().height();
             x2 = x1+cos(-M_PI/2*airbrake/100.0)*0.2*text.size().width();
             y2 = y1+sin(-M_PI/2*airbrake/100.0)*0.2*text.size().width();
             painter->drawLine(x1, y1, x2, y2);
        }
        if(gear>0)
        {
            x1 = 1.4/6.4*text.size().width();
             y1 = 2.92/4.8*text.size().height();
             x2 = x1+cos(M_PI/2*gear/100.0)*0.2*text.size().width();
             y2 = y1+sin(M_PI/2*gear/100.0)*0.2*text.size().width();
             painter->drawLine(x1, y1, x2, y2);
             int eclsize = 0.1*text.size().width();
             painter->drawEllipse(x2-eclsize/2,y2-eclsize/2, eclsize , eclsize);
        }

        painter->end();
        text.setPixmap(dev);

    }
    else
        this->hide();
}

void FlapsIndicator::wheelEvent(QWheelEvent *e)
{
    if(editMode)
    {
        std::cout <<"Resizing " <<text.size().width()<<std::endl;
        float diff = e->angleDelta().y()/120;
        QSize d(diff, diff);
        std::cout << diff <<std::endl;
        QSize old = this->size();
        text.resize(old+=d);
        this->resize(text.size());
        text.setPixmap(pic->scaled(text.size(), Qt::KeepAspectRatio));


    }
}


