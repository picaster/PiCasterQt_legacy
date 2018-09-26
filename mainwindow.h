#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QPushButton* trackButtons[8];

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init();

private slots:
    void on_TrackButton_clicked();

private:
    Ui::MainWindow *ui;

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

};

#endif // MAINWINDOW_H
