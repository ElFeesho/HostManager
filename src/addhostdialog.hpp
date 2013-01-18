#ifndef ADDHOSTDIALOG_HPP
#define ADDHOSTDIALOG_HPP

#include <QMainWindow>
#include <QAbstractButton>

namespace Ui {
    class AddHostDialog;
}

class AddHostDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddHostDialog(QWidget *parent = 0);
    ~AddHostDialog();
    void clear();
signals:
    void requestAdd(const QString &host, const QString &ip);
    void cancelAdd();
private slots:
    void buttonBoxSelect(QAbstractButton *button);



private:
    Ui::AddHostDialog *ui;
};

#endif // ADDHOSTDIALOG_HPP
