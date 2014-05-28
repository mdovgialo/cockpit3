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
#include <QFontMetrics>
class GenericIndicator : public QWidget
{
    Q_OBJECT

public:
    explicit GenericIndicator(QJsonObject params, int nr, InstrumentPanel *parent = 0, bool edit=1, bool overlay=0);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void wheelEvent(QWheelEvent *);
    virtual int get_nr()
    {
        return nr;
    }
    virtual float getFontSize()
    { return fonts;}

signals:

public slots:
    virtual void update_ind(Gamestate*);
protected:
    bool editMode;
    bool moving;
    float fonts;
    QJsonObject params;
    QLabel text;
    int nr;
    bool overlay;

};

#endif // GENERICINDICATOR_H
