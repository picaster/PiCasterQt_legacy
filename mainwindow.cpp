#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->trackButtons[0] = ui->Track1;
    this->trackButtons[1] = ui->Track2;
    this->trackButtons[2] = ui->Track3;
    this->trackButtons[3] = ui->Track4;
    this->trackButtons[4] = ui->Track5;
    this->trackButtons[5] = ui->Track6;
    this->trackButtons[6] = ui->Track7;
    this->trackButtons[7] = ui->Track8;
}

void MainWindow::init()
{
    forTrackButtons([&](QPushButton* button) {
        button->setText("Empty\n0:00.00");
        //QObject::connect(button, SIGNAL(clicked()), this, SLOT(on_TrackButton_clicked()));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_TrackButton_clicked()
{
    Qt::KeyboardModifiers kn = QGuiApplication::keyboardModifiers();
    QPushButton* button = dynamic_cast<QPushButton*>(sender());

    if (kn & Qt::KeyboardModifier::ShiftModifier)
    {
        std::cerr << "Shift clicked " << button->objectName().toUtf8().data() << std::endl;
    }
    else if (kn & Qt::KeyboardModifier::ControlModifier)
    {
        std::cerr << "Control clicked " << button->objectName().toUtf8().data() << std::endl;
    }
    else
    {
        std::cerr << "Clicked " << button->objectName().toUtf8().data() << std::endl;
    }
}
