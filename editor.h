#ifndef EDITOR_H
#define EDITOR_H
#include "instrument_panel.h"
#include <QMenu>
#include <QAction>
#include <QDialog>
#include <QLineEdit>
#include <QList>
#include <QJsonValueRef>
 #include <QDoubleSpinBox>

class InstrumentPanel;

class Editor : public QWidget
{
    Q_OBJECT
    QComboBox* available;
    InstrumentPanel* editable;
    QJsonObject params;
    QLineEdit* name;
    QLineEdit* title;
    QLineEdit* suffix;
    QDoubleSpinBox* maxangleEdit;
    QDoubleSpinBox* maxvalueEdit;
    QLineEdit* back_picEdit;
    QLineEdit* needle_picEdit;
    QDoubleSpinBox* zeroangleEdit;
    QDialog* ask;

public:
    explicit Editor(QJsonObject params, InstrumentPanel* panel, QWidget *parent = 0);

signals:
    void settings_done(QJsonObject*);
    void settings_updated(QJsonObject*);

public slots:
    void rem_instrument();
    void done();
    void add_generic();
    void add_generic_params();
    void add_flaps();
    void add_vario();
    void add_target();
    void add_generic_analogue();
    void add_generic_analogue_params();

    void add_map();



};

#endif // EDITOR_H
