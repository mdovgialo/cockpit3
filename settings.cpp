#include "settings.h"
#include "instrument_panel.h"
#include <iostream>
Settings::Settings(QJsonObject settings, QWidget *parent, bool overlay)
    : QWidget(parent)
{
    QHBoxLayout* l = new QHBoxLayout;

    this->setLayout(l);
    url = new QLineEdit(settings.find("url").value().toString());
    dt = new QSpinBox();
    dt->setMaximum(99999);
    dt->setValue(settings.find("dt").value().toDouble());
    dt->setSuffix("ms");
    QPushButton* run = new QPushButton("Start");
    QPushButton* editor = new QPushButton("Editor");
    QCheckBox* asOverlay = new QCheckBox("As overlay");

    asOverlay->setChecked(overlay);

    l->addWidget(new QLabel("Adress:", this));
    l->addWidget(url);
    l->addWidget(new QLabel("Update every:", this));
    l->addWidget(dt);

    l->addWidget(run);
    l->addWidget(editor);
    l->addWidget(asOverlay);

    connect(url, SIGNAL(textChanged(QString)), parent, SLOT(set_url(QString)));
    connect(dt, SIGNAL(valueChanged(int)), parent, SLOT(set_dt(int)));
    connect(run, SIGNAL(clicked()), parent, SLOT(run_cockpit()));
   // connect(editor, SIGNAL(clicked()), this, SLOT(show_editor()));
    connect(editor, SIGNAL(clicked()), parent, SLOT(run_edit()));
    connect(asOverlay,SIGNAL(stateChanged(int)), parent, SLOT(set_overlay(int)));






}
void Settings::show_editor()
{
    this->parentWidget()->hide();


}
Settings::~Settings()
{

}


