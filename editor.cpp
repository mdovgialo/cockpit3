#include "editor.h"
#include "genericindicator.h"
#include <iostream>
using namespace std;
Editor::Editor(QJsonObject params, InstrumentPanel *panel, QWidget *parent ) :
    QWidget(0), params(params)
{
    editable = panel;
    QVBoxLayout* mainl =  new QVBoxLayout ;
    QHBoxLayout* reml = new QHBoxLayout;
    QToolButton *add = new QToolButton();
    add->setText("Add");
    QMenu* addmenu = new QMenu;
    add->setMenu(addmenu);
    QAction *addgeneric = new QAction("Generic", addmenu);
    QAction *addflaps = new QAction("Flaps", addmenu);

    addmenu->addAction(addgeneric);
    addmenu->addAction(addflaps);
    connect(addgeneric, SIGNAL(triggered()), this, SLOT(add_generic()));
    connect(addflaps, SIGNAL(triggered()), this, SLOT(add_flaps()));

    QPushButton *done = new QPushButton("Done");
    QPushButton *rem = new QPushButton();
    rem->setText("Remove");
    available = new QComboBox;
    QJsonArray instruments = params["instruments"].toArray();
    for(int i = 0; i<instruments.size();++i)
    {
        QJsonObject instrument = instruments[i].toObject();
        available->addItem(
                instrument["type"].toString()+QString(" ")+instrument["title"].toString());
    }


    reml->addWidget(available);
    mainl->addWidget(add);
    reml->addWidget(rem);


    mainl->addLayout(reml);
    mainl->addWidget(done);

    connect(rem, SIGNAL(clicked()), this, SLOT(rem_instrument()));
    connect (done, SIGNAL(clicked()), this, SLOT(done()));
    connect( this, SIGNAL(settings_done(QJsonObject*)), parent, SLOT(run_settings(QJsonObject*)));
    connect(this, SIGNAL(settings_updated(QJsonObject*)), parent, SLOT(run_edit(QJsonObject*)));

    this->setLayout(mainl);
    this->show();
}
void Editor::done()
{
    QJsonArray jsoninstr = params["instruments"].toArray();
    QJsonObject jsonchild;
    QList<GenericIndicator*> children = editable->findChildren<GenericIndicator*>(QString(""), Qt::FindDirectChildrenOnly);
    for(int i = 0; i<children.size(); ++i)
    {
        GenericIndicator* child = children[i];
        int j = child->get_nr();
        jsonchild = jsoninstr[j].toObject();
        jsonchild["x"] = child->pos().x();
        jsonchild["y"] = child->pos().y();
        jsonchild["h"] = child->size().height();
        jsonchild["w"] = child->size().width();
        jsonchild["fonts"] = child->getFontSize();
        jsoninstr[j] = jsonchild;

    }
    params["instruments"] = jsoninstr;
    this->deleteLater();
    emit settings_done(&params);
}
void Editor::add_generic()
{
    ask = new QDialog;
    ask->setLayout(new QVBoxLayout);
    name = new QLineEdit("In game indicator name");
    title = new QLineEdit("Title");
    suffix = new QLineEdit("Suffix");
    QPushButton* ok = new QPushButton("ok");
    ask->layout()->addWidget(name);
    ask->layout()->addWidget(title);
    ask->layout()->addWidget(suffix);
    ask->layout()->addWidget(ok);
    ask->show();
    connect(ok, SIGNAL(clicked()), this, SLOT(add_generic_params()));
}
void Editor::add_generic_params()
{
    QJsonArray instr = params["instruments"].toArray();
    QJsonObject i;
    i["x"] = 0;
    i["y"] = 0;
    i["h"] =30;
    i["w"] = 700;
    i["ind_name"] = name->text();
    i["type"] = "generic";
    i["title"] = title->text();
    i["suffix"] = suffix->text();
    instr.push_back(i);
    params["instruments"]=instr;
    ask->deleteLater();
    this->deleteLater();
    emit settings_updated(&params);
}

void Editor::add_flaps()
{
    QJsonArray instr = params["instruments"].toArray();
    QJsonObject i;
    i["x"] = 0;
    i["y"] = 0;
    i["h"] =50;
    i["w"] =50;
    i["ind_name"] = "flaps, %";
    i["type"] = "flaps";


    instr.push_back(i);
    params["instruments"]=instr;
    ask->deleteLater();
    this->deleteLater();
    emit settings_updated(&params);
}
void Editor::rem_instrument()
{
    QJsonArray instr = params["instruments"].toArray();
    instr.removeAt(available->currentIndex());
    std::cout << "removing nr"<<available->currentIndex()<<endl;
    std::cout << instr[0].toObject()["title"].toString().toStdString()<<endl;
    params["instruments"]=instr;
    std::cout << params["instruments"].toArray()[0].toObject()["title"].toString().toStdString()<<endl;
    this->deleteLater();
    emit settings_updated(&params);



}
