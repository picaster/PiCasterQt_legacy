#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QPushButton>

#include <mediafile.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QPushButton* trackButtons[8];
    QPushButton* jingleButtons[6];
    int tracksPlaying = 0;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init();

private:
    void trackButtonShiftClicked(QPushButton* button);
    void setButtonText(QPushButton* button, MediaFile* mediaFile);

private slots:
    void trackButtonClicked();
    void jingleButtonClicked();
    void micButtonClicked();
    void jackButtonClicked();
    void recordButtonClicked();
    void streamButtonClicked();

// Private utility methods    
private:
    template <typename Func>
    void forTrackButtons(Func func)
    {
        for (int i = 0; i < 8; i++)
        {
            func(this->trackButtons[i]);
        }
    }

    template <typename Func>
    void forJingleButtons(Func func)
    {
        for (int i = 0; i < 6; i++)
        {
            func(this->jingleButtons[i]);
        }
    }
};

#endif // MAINWINDOW_H
