#include "genericindicator.h"

GenericIndicator::GenericIndicator(QJsonObject params, InstrumentPanel *parent, bool edit): params(params),
    QWidget(parent), editMode(edit)
{
    this->move(params["x"].toDouble(), params["y"].toDouble());
    //this->resize(params["w"].toDouble(), params["h"].toDouble());

    text.setText(params["title"].toString() +QString("000000")+ params["suffix"].toString());
    QFont f = text.font();
    f.setPointSize(params["h"].toDouble());
    text.setFont(f);
    this->resize(text.size());
    connect(parent, SIGNAL(panel_update(Gamestate*)), this, SLOT(update_ind(Gamestate*)));
}

void GenericIndicator::update_ind(Gamestate *upd)
{
    QString ind(params["ind_name"].toString());
    QString data;
    if(upd->state.object()["valid"].toBool())
    {
        if(! (upd->indicators.object()[ind]==QJsonValue::Undefined))
        {
            data = upd->indicators.object()[ind].toDouble();

        }
        else if(!( upd->state.object()[ind]==QJsonValue::Undefined))
        {
            data = upd->state.object()[ind].toDouble();
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
