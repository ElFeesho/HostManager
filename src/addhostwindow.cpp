#include "addhostwindow.hpp"
#include "ui_addhostwindow.h"

#include <QMessageBox>

AddHostWindow::AddHostWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddHostWindow)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(clicked(QAbstractButton*)),this,SLOT(buttonBoxSelect(QAbstractButton*)));
    setWindowFlags(windowFlags() ^ Qt::WindowMaximizeButtonHint ^ Qt::WindowMinimizeButtonHint);

}

void AddHostWindow::clear()
{
    ui->txtHost->clear();
    ui->txtIP->clear();
}

void AddHostWindow::setCompletionList(const QStringList &list)
{
    if(ui->txtIP->completer()!=NULL)
        delete ui->txtIP->completer();
    ui->txtIP->setCompleter(new QCompleter(list));
}

void AddHostWindow::buttonBoxSelect(QAbstractButton *button)
{
    if(button == ui->buttonBox->buttons().at(0))
    {
        if(ui->txtHost->text().length()<=0)
        {
            ui->txtHost->focusWidget();
            QMessageBox::critical(NULL,"Please Supply a Host Name","Please enter the host name you wish to add to the DNS redirection.");
            return;
        }
        else if(ui->txtIP->text().length()<=0)
        {
            ui->txtIP->focusWidget();
            QMessageBox::critical(this,"Please Supply an IP Address","Please enter an IP address that the host name will forward to.");
            return;
        }
        else
        {
            emit requestAdd(ui->txtHost->text(), ui->txtIP->text());
            hide();
        }
    }
    else
    {
        emit cancelAdd();
        hide();
    }
}

AddHostWindow::~AddHostWindow()
{
    delete ui;
}
