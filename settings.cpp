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
    dt->setMaximum(99999);
    dt->setValue(settings.find("dt").value().toDouble());
    dt->setSuffix("ms");
    QPushButton* run = new QPushButton("Start");
    QPushButton* editor = new QPushButton("Editor");
    l->addWidget(new QLabel("Adress:", this));
    l->addWidget(url);
    l->addWidget(new QLabel("Update every:", this));
    l->addWidget(dt);

    l->addWidget(run);
    l->addWidget(editor);

    connect(url, SIGNAL(textChanged(QString)), parent, SLOT(set_url(QString)));
    connect(dt, SIGNAL(valueChanged(int)), parent, SLOT(set_dt(int)));
    connect(run, SIGNAL(clicked()), parent, SLOT(run_cockpit()));
    connect(editor, SIGNAL(clicked()), this, SLOT(show_editor()));






}
void Settings::show_editor()
{
    this->parentWidget()->hide();

}
Settings::~Settings()
{

}


