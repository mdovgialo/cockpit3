#include "genericindicator.h"
#include <iostream>
using namespace std;



GenericIndicator::GenericIndicator(QJsonObject params, int nr, InstrumentPanel *parent, bool edit, bool overlay):
    QWidget(parent), editMode(edit), params(params), nr(nr), overlay(overlay)
{


    QFont fontstyle(params["font"].toString());

    text.setFont(fontstyle);

    this->fonts = params["fonts"].toDouble();

    text.setText(params["title"].toString() +QString("000000000")+ params["suffix"].toString());
    this->setLayout(new QVBoxLayout());
    this->layout()->addWidget(&text);
    QFont f = text.font();
    f.setPointSizeF(this->fonts);
    text.setFont(f);
    text.resize((text.fontMetrics().boundingRect(text.text()).size()*=1.1)+=QSize(20, 20));

    this->move(params["x"].toDouble(), params["y"].toDouble());
    this->resize(text.size());
    text.move(0,0);
    connect(parent, SIGNAL(panel_update(Gamestate*)), this, SLOT(update_ind(Gamestate*)));
}

void GenericIndicator::update_ind(Gamestate *upd)
{
    QString ind = params["ind_name"].toString();
    QString data = "%1";
    double value;

    if(upd->state.object()["valid"].toBool())
    {
        this->show();

        if(! upd->indicators.object()[ind].isNull())
        {
            cout << "reading as indicators"<<endl;
            value  =upd->state.object()[ind].toDouble();
            data = data.arg(value, params["field_size"].toInt(), 'f', params["precision"].toInt());

            //data = QString::number( upd->indicators.object()[ind].toDouble());

        }
        else if(! upd->state.object()[ind].isNull())
        {
            value = upd->state.object()[ind].toDouble();
            data = data.arg(value, params["field_size"].toInt(), 'f', params["precision"].toInt());
            //data = QString::number(upd->state.object()[ind].toDouble());
        }
        else
        {
            data = "N/A";
            this->hide();
        }
        if(params["hide_data"].toBool())
        {
            data = "";
        }
        QString textColor;
        if (value>params["critical_value"].toDouble())
        {
            textColor = params["critical_color"].toString();
        }
        else
        {
            textColor = params["color"].toString();

        }
        text.setStyleSheet(QString("color:")+textColor);

        text.setText(params["title"].toString() + data + params["suffix"].toString());
    }
    else
    {
        this->hide();
    }

}

 void GenericIndicator::mousePressEvent(QMouseEvent *e)
 {
     if (editMode)
     {
        this->moving=true;
         cout<< "MOVE!!!"<<endl;
     }
 }

void GenericIndicator::mouseMoveEvent(QMouseEvent *e)
{
    if(editMode and moving)
    {
        QPoint cur = this->parentWidget()->mapFromGlobal(QCursor::pos());
        this->move(cur.x(), cur.y());
    }

}

void GenericIndicator::mouseReleaseEvent(QMouseEvent *e)
{
    if(editMode and moving)
    {

        this->moving = false;

    }
}

void GenericIndicator::wheelEvent(QWheelEvent *e)
{
    if(editMode)
    {
        cout<<"Resizing generic";
        QFont f = text.font();
        f.setPointSizeF(f.pointSizeF()+e->angleDelta().y()/120);
        this->fonts= f.pointSizeF();
        text.setFont(f);
        text.resize((text.fontMetrics().boundingRect(text.text()).size()*=1.1)+=QSize(20,20));
        text.move(0,0);
        this->resize(text.size());
        e->accept();

    }
    else
        e->ignore();
}

