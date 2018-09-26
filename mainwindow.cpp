#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mediafile.h"

#include <QFileDialog>
#include <taglib.h>
#include <taglib/fileref.h>

#include <iostream>
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    trackButtons[0] = ui->trackButton1;
    trackButtons[1] = ui->trackButton2;
    trackButtons[2] = ui->trackButton3;
    trackButtons[3] = ui->trackButton4;
    trackButtons[4] = ui->trackButton5;
    trackButtons[5] = ui->trackButton6;
    trackButtons[6] = ui->trackButton7;
    trackButtons[7] = ui->trackButton8;

    jingleButtons[0] = ui->jingleButton1;
    jingleButtons[1] = ui->jingleButton2;
    jingleButtons[2] = ui->jingleButton3;
    jingleButtons[3] = ui->jingleButton4;
    jingleButtons[4] = ui->jingleButton5;
    jingleButtons[5] = ui->jingleButton6;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    forTrackButtons([&](QPushButton* button) {
        button->setText("Empty\n0:00");
        QObject::connect(button, SIGNAL(clicked()), this, SLOT(trackButtonClicked()));
    });

    forJingleButtons([&](QPushButton* button) {
        button->setText("Empty\n0:00");
        QObject::connect(button, SIGNAL(clicked()), this, SLOT(jingleButtonClicked()));
    });

    ui->micButton->setEnabled(false);
    QObject::connect(ui->micButton, SIGNAL(clicked()), this, SLOT(micButtonClicked()));

    ui->jackButton->setEnabled(true);
    QObject::connect(ui->jackButton, SIGNAL(clicked()), this, SLOT(jackButtonClicked()));

    ui->recordButton->setEnabled(false);
    QObject::connect(ui->recordButton, SIGNAL(clicked()), this, SLOT(recordButtonClicked()));

    ui->streamButton->setEnabled(false);
    QObject::connect(ui->streamButton, SIGNAL(clicked()), this, SLOT(streamButtonClicked()));

    QObject::connect(ui->micLevelSlider, SIGNAL(valueChanged(int)), this, SLOT(micLevelChanged(int)));
}

void MainWindow::setButtonText(QPushButton* button, MediaFile* mediaFile)
{
    QString label = mediaFile->artist() + " - " + mediaFile->title();
    int seconds = mediaFile->duration() % 60;
    int minutes = (mediaFile->duration() - seconds) / 60;
    button->setText(QString("%1\n%2:%3").arg(label).arg(QString::number(minutes)).arg(seconds, 2, 10, QLatin1Char('0')));
}

void MainWindow::trackButtonShiftClicked(QPushButton* button)
{
    if (button->isChecked()) button->toggle();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open media file"), QString(), tr("Audio files (*.flac *.mp3)"));
    if (!fileName.isEmpty())
    {
        TagLib::FileRef f(fileName.toUtf8().data());
        TagLib::String artist = f.tag()->artist();
        TagLib::String title = f.tag()->title();
        int duration = f.audioProperties()->lengthInSeconds();
        MediaFile* mediaFile = new MediaFile(fileName, artist.toCString(), title.toCString(), duration);
        button->setUserData(0, mediaFile);
        setButtonText(button, mediaFile);
    }
}

void MainWindow::trackButtonClicked()
{
    QPushButton* button = dynamic_cast<QPushButton*>(sender());
    Qt::KeyboardModifiers kn = QGuiApplication::keyboardModifiers();

    if (kn & Qt::KeyboardModifier::ShiftModifier)
    {
        if (button->isChecked()) trackButtonShiftClicked(button);
        else button->toggle();
    }
    else
    {
        MediaFile* mediaFile = dynamic_cast<MediaFile*>(button->userData(0));
        if (mediaFile == nullptr) trackButtonShiftClicked(button);
        else
        {
            if (button->isChecked())
            {
                if (tracksPlaying == 2) button->toggle();
                else
                {
                    std::cerr << "Playing track " << mediaFile->filePath().toUtf8().data() << " for " << button->objectName().toUtf8().data() << std::endl;
                    mediaFile->setPlaying(true);
                    tracksPlaying += 1;
                    if (tracksPlaying == 2)
                    {
                        forTrackButtons([&](QPushButton* button) {
                            MediaFile* mediaFile = dynamic_cast<MediaFile*>(button->userData(0));
                            if ((mediaFile == nullptr) || (!mediaFile->playing())) button->setDisabled(true);
                        });
                    }
                }
            }
            else
            {
                std::cerr << "Stopping track " << mediaFile->filePath().toUtf8().data() << " for " << button->objectName().toUtf8().data() << std::endl;
                tracksPlaying -= 1;
                mediaFile->setPlaying(false);
                setButtonText(button, mediaFile);
                if (tracksPlaying == 1)
                {
                    forTrackButtons([&](QPushButton* button) {
                        button->setDisabled(false);
                    });
                }
            }
        }
    }

    /*
    if (kn & Qt::KeyboardModifier::ControlModifier)
    {
        std::cerr << "Control clicked " << button->objectName().toUtf8().data() << std::endl;
    }
    else
    {
        std::cerr << "Clicked " << button->objectName().toUtf8().data() << std::endl;
    }
    */
}

void MainWindow::micLevelChanged(int value)
{
    long double fvalue = value / 100.0l;
    long double dbValue = 65 * log10(fvalue);
}

void MainWindow::jingleButtonClicked()
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

void MainWindow::micButtonClicked()
{

}

void MainWindow::jackButtonClicked()
{

}

void MainWindow::recordButtonClicked()
{

}

void MainWindow::streamButtonClicked()
{

}
