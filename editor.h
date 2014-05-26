#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QJsonObject>
#include <QJsonDocument>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
 #include <QComboBox>
class editor : public QWidget
{
    Q_OBJECT
    QComboBox* available;
public:
    explicit editor(QJsonObject params, QWidget *parent = 0);

signals:

public slots:



};

#endif // EDITOR_H
