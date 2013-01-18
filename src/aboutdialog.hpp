#ifndef ABOUTDIALOG_HPP
#define ABOUTDIALOG_HPP

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
    class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();
public slots:
    void closeDialog(QAbstractButton *);
private:
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_HPP
