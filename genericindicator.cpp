#include "genericindicator.h"
#include <iostream>
using namespace std;
GenericIndicator::GenericIndicator(QJsonObject params, InstrumentPanel *parent, bool edit): params(params),
    QWidget(parent), editMode(edit)
{


   // this->resize(params["w"].toDouble(), params["h"].toDouble());

    text.setText(params["title"].toString() +QString("000000")+ params["suffix"].toString());
    this->setLayout(new QVBoxLayout());
    this->layout()->addWidget(&text);
    QFont f = text.font();
    f.setPixelSize(params["h"].toDouble());
    text.setFont(f);
    QFontMetrics mm(text.font());
    QSize size = mm.size(Qt::TextSingleLine, text.text());
    this->resize(size.width()+15, size.height()+15);
    //setGeometry(this->x(), this->y(),text.size().width(), text.size().height());
    this->move(params["x"].toDouble(), params["y"].toDouble());
    connect(parent, SIGNAL(panel_update(Gamestate*)), this, SLOT(update_ind(Gamestate*)));
}

void GenericIndicator::update_ind(Gamestate *upd)
{
    QString ind = params["ind_name"].toString();
    QString data;

    if(upd->state.object()["valid"].toBool())
    {

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
            data = "N/A";
        text.setText(params["title"].toString() + data + params["suffix"].toString());
    }
    else
    {
        text.setText("");
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
    if(editMode and moving)
    {
        QFont f = text.font();
        f.setPixelSize(f.pixelSize()+e->angleDelta().y()/120);

        text.setFont(f);
        //this->resize(text.size());
        QFontMetrics mm(text.font());
        QSize size = mm.size(Qt::TextSingleLine, text.text());
        this->resize(size.width()+15, size.height()+15);
        e->accept();

    }
    else
        e->ignore();
}
