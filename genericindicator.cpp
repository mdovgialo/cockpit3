#include "genericindicator.h"
#include <iostream>
using namespace std;



GenericIndicator::GenericIndicator(QJsonObject params, int nr, InstrumentPanel *parent, bool edit, bool overlay):
    QWidget(parent), editMode(edit), params(params), nr(nr), overlay(overlay)
{



    this->fonts = params["fonts"].toDouble();

    text.setText(params["title"].toString() +QString("0000")+ params["suffix"].toString());
    this->setLayout(new QVBoxLayout());
    this->layout()->addWidget(&text);
    QFont f = text.font();
    f.setPointSizeF(this->fonts);
    text.setFont(f);
    text.resize((text.fontMetrics().boundingRect(text.text()).size()*=1.1)+=QSize(20, 20));
    //setGeometry(this->x(), this->y(),text.size().width(), text.size().height());
    this->move(params["x"].toDouble(), params["y"].toDouble());
    this->resize(text.size());
    connect(parent, SIGNAL(panel_update(Gamestate*)), this, SLOT(update_ind(Gamestate*)));
}

void GenericIndicator::update_ind(Gamestate *upd)
{
    QString ind = params["ind_name"].toString();
    QString data;

    if(upd->state.object()["valid"].toBool())
    {
        this->show();

        if(! upd->indicators.object()[ind].isNull())
        {
            cout << "reading as indicators"<<endl;
            data = QString::number( upd->indicators.object()[ind].toDouble());

        }
        else if(! upd->state.object()[ind].isNull())
        {
            data = QString::number(upd->state.object()[ind].toDouble());
        }
        else
        {
            data = "N/A";
            this->hide();
        }
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

