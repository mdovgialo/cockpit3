#include "settings.h"
#include "instrument_panel.h"
#include <iostream>
Settings::Settings(QJsonObject settings, QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout* l = new QHBoxLayout;

    this->setLayout(l);
    url = new QLineEdit(settings.find("url").value().toString());
    dt = new QSpinBox();
    dt->setValue(settings.find("dt").value().toDouble());
    QPushButton* run = new QPushButton("Start");
    l->addWidget(url);
    l->addWidget(dt);

    l->addWidget(run);
    connect(url, SIGNAL(textChanged(QString)), parent, SLOT(set_url(QString)));
    connect(dt, SIGNAL(valueChanged(int)), parent, SLOT(set_dt(int)));
    connect(run, SIGNAL(clicked()), parent, SLOT(run_cockpit()));




}

Settings::~Settings()
{

}


