#ifndef EDITHOSTWINDOW_HPP
#define EDITHOSTWINDOW_HPP

#include <QMainWindow>
#include <QAbstractButton>
#include <QCompleter>
#include "hostrecord.hpp"

namespace Ui {
    class EditHostWindow;
}

class EditHostWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditHostWindow(QWidget *parent = 0);
    ~EditHostWindow();
    void setHost(HostRecord *record);
    void setCompletionList(const QStringList &list);
signals:
    void requestEdit(HostRecord *record);
    void cancelEdit();
public slots:
    void buttonBoxSelect(QAbstractButton *button);
private:
    Ui::EditHostWindow *ui;
    HostRecord *record;
};

#endif // EDITHOSTWINDOW_HPP

