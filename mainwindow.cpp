#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Track1_clicked()
{
    Qt::KeyboardModifiers kn = QGuiApplication::keyboardModifiers();

    if (kn & Qt::KeyboardModifier::ShiftModifier)
    {
        std::cerr << "Shift clicked" << std::endl;
    }
    else if (kn & Qt::KeyboardModifier::ControlModifier)
    {
        std::cerr << "Contronl clicked" << std::endl;
    }
    else
    {
        std::cerr << "Clicked" << std::endl;
    }
}
