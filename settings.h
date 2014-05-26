#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QLabel>
#include <QGraphicsEffect>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QJsonObject>
#include <QLabel>


class Settings : public QWidget
{
    Q_OBJECT


public:
    Settings(QJsonObject settings, QWidget *parent = 0);
    ~Settings();


private:
    QLineEdit* url;
    QSpinBox* dt;
public slots:
    void show_editor();
};

#endif // SETTINGS_H
