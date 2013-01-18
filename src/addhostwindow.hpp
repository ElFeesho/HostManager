#ifndef ADDHOSTWINDOW_HPP
#define ADDHOSTWINDOW_HPP

#include <QMainWindow>

#include <QAbstractButton>

#include <QCompleter>

namespace Ui {
    class AddHostWindow;
}

class AddHostWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddHostWindow(QWidget *parent = 0);
    ~AddHostWindow();
    void clear();
    void setCompletionList(const QStringList &list);
signals:
    void requestAdd(const QString &host, const QString &ip);
    void cancelAdd();
private slots:
    void buttonBoxSelect(QAbstractButton *button);
private:
    Ui::AddHostWindow *ui;
};

#endif // ADDHOSTWINDOW_HPP
