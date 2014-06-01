#include "editor.h"
#include "genericindicator.h"
#include <QDoubleValidator>
#include <cmath>
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
    QAction *addgenericgauge = new QAction("Generic gauge", addmenu);

    QAction *addflaps = new QAction("Flaps", addmenu);
    QAction *addvario = new QAction("Variometer", addmenu);
    QAction *addmap = new QAction("Map", addmenu);
    QAction *addtarget = new QAction("Target Distance", addmenu);




    addmenu->addAction(addgeneric);
    addmenu->addAction(addgenericgauge);

    addmenu->addAction(addflaps);
    addmenu->addAction(addvario);
    addmenu->addAction(addmap);
    addmenu->addAction(addtarget);



    connect(addgeneric, SIGNAL(triggered()), this, SLOT(add_generic()));
    connect(addgenericgauge, SIGNAL(triggered()), this, SLOT(add_generic_analogue()));

    connect(addflaps, SIGNAL(triggered()), this, SLOT(add_flaps()));
    connect(addvario, SIGNAL(triggered()), this, SLOT(add_vario()));
    connect(addmap, SIGNAL(triggered()), this, SLOT(add_map()));
    connect(addtarget, SIGNAL(triggered()), this, SLOT(add_target()));


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

void Editor::add_generic_analogue()
{
    ask = new QDialog;
    ask->setLayout(new QVBoxLayout);
    name = new QLineEdit("in game name");
    title = new QLineEdit("Title");

    back_picEdit= new QLineEdit("gauge image path");
    needle_picEdit = new QLineEdit("needle image path");
    zeroangleEdit = new QDoubleSpinBox;
    maxangleEdit =  new QDoubleSpinBox;
    maxvalueEdit =  new QDoubleSpinBox;
    zeroangleEdit->setMaximum(360);
    maxangleEdit->setMaximum(360);
    maxvalueEdit->setMaximum(9999999);
    QPushButton* ok = new QPushButton("ok");
    ask->layout()->addWidget(name);
    ask->layout()->addWidget(title);
    ask->layout()->addWidget(back_picEdit);
    ask->layout()->addWidget(needle_picEdit);
    ask->layout()->addWidget(new QLabel("zero angle (relative to 9 o'clock"));
    ask->layout()->addWidget(zeroangleEdit);
    ask->layout()->addWidget(new QLabel("maximum angle (relative to 9 o'clock)"));
    ask->layout()->addWidget(maxangleEdit);
    ask->layout()->addWidget(new QLabel("maximum angle value"));
    ask->layout()->addWidget(maxvalueEdit);

    ask->layout()->addWidget(ok);
    ask->show();
    connect(ok, SIGNAL(clicked()), this, SLOT(add_generic_analogue_params()));
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
void Editor::add_generic_analogue_params()
{
    QJsonArray instr = params["instruments"].toArray();
    QJsonObject i;
    i["x"] = 0;
    i["y"] = 0;
    i["h"] =300;
    i["w"] = 300;
    i["back_im"]  =back_picEdit->text();
    i["needle_im"] = needle_picEdit->text();
   i["zeroangl"] = zeroangleEdit->value();
    i[  "maxangl"] = maxangleEdit->value();
    i ["maxanglvalue"] =  maxvalueEdit->value();
    i["ind_name"] = name->text();
    i["type"] = "generic analogue";
    i["title"] = title->text();

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
    this->deleteLater();
    emit settings_updated(&params);
}

void Editor::add_map()
{
    QJsonArray instr = params["instruments"].toArray();
    QJsonObject i;
    i["x"] = 0;
    i["y"] = 0;
    i["h"] =300;
    i["w"] =300;
    i["ind_name"] = "Map";
    i["type"] = "map";


    instr.push_back(i);
    params["instruments"]=instr;
    this->deleteLater();
    emit settings_updated(&params);
}

void Editor::add_vario()
{
    QJsonArray instr = params["instruments"].toArray();
    QJsonObject i;
    i["x"] = 0;
    i["y"] = 0;
    i["h"] =200;
    i["w"] =200;
    i["ind_name"] = "Vy, m/s";
    i["type"] = "vario";
    i["back_im"] = "./images/vario.png";
    i["needle_im"] = "./images/vario_needle.png";
   i["zeroangl"] = 0.0;
    i[  "maxangl"] = 180.0;
    i ["maxanglvalue"] = 100.0;

    instr.push_back(i);
    params["instruments"]=instr;
    this->deleteLater();
    emit settings_updated(&params);
}

void Editor::add_target()
{
    QJsonArray instr = params["instruments"].toArray();
    QJsonObject i;
    i["x"] = 0;
    i["y"] = 0;
    i["h"] =30;
    i["w"] = 700;
    i["type"] = "target";
    cout<<"creating target"<<endl;

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
