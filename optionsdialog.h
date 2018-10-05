#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = nullptr);
    ~OptionsDialog();

private:
    Ui::OptionsDialog *ui;
    void addCard(const QString& sName, const QString& sDescription);
};

#endif // OPTIONSDIALOG_H
