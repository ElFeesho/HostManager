#include "edithostwindow.hpp"
#include "ui_edithostwindow.h"
#include <QMessageBox>

EditHostWindow::EditHostWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditHostWindow)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(clicked(QAbstractButton*)),this,SLOT(buttonBoxSelect(QAbstractButton*)));
    setWindowFlags(windowFlags() ^ Qt::WindowMaximizeButtonHint ^ Qt::WindowMinimizeButtonHint);
}

void EditHostWindow::setCompletionList(const QStringList &list)
{
    if(ui->txtIP->completer()!=NULL)
        delete ui->txtIP->completer();
    ui->txtIP->setCompleter(new QCompleter(list));
}

void EditHostWindow::setHost(HostRecord *record)
{
    this->record = record;
    ui->txtHost->setText(record->host());
    ui->txtIP->setText(record->ip());
}

void EditHostWindow::buttonBoxSelect(QAbstractButton *button)
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
                record->host(ui->txtHost->text());
                record->ip(ui->txtIP->text());
                emit requestEdit(record);
                hide();
            }
    }
    else
    {
        emit cancelEdit();
        hide();
    }
}

EditHostWindow::~EditHostWindow()
{
    delete ui;
}
