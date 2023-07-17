#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MiniCAD.h"

class MiniCAD : public QMainWindow
{
    Q_OBJECT

public:
    MiniCAD(QWidget *parent = nullptr);
    ~MiniCAD();

private:
    Ui::MiniCADClass ui;
};
