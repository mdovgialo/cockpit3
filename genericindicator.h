#ifndef GENERICINDICATOR_H
#define GENERICINDICATOR_H

#include <QWidget>
#include "gamestate.h"
#include "instrument_panel.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QPoint>
#include <QSize>
#include <QLabel>
#include <QString>
#include <QFont>
#include <QMouseEvent>
#include <QWheelEvent>

class GenericIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit GenericIndicator(QJsonObject params, InstrumentPanel *parent = 0, bool edit=1);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);

signals:

public slots:
    virtual void update_ind(Gamestate*);
protected:
    bool editMode;
    bool moving;
    QJsonObject params;
    QLabel text;

};

#endif // GENERICINDICATOR_H
