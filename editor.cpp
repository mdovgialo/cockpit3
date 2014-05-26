#include "editor.h"

editor::editor(QJsonObject params, QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* mainl =  new QVBoxLayout ;
    QHBoxLayout* ladd = new QHBoxLayout;
    QPushButton *add = new QPushButton("Add");

    available = new QComboBox;
    available->addItem("generic");
    ladd->addWidget(available);
    ladd->addWidget(add);
    mainl->addLayout(ladd);
    this->setLayout(mainl);
}
