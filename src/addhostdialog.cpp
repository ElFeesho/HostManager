#include <QMessageBox>

#include "addhostdialog.hpp"
#include "ui_addhostdialog.h"

AddHostDialog::AddHostDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddHostDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox,SIGNAL(clicked(QAbstractButton*)),this, SLOT(buttonBoxSelect(QAbstractButton*)));
}

void AddHostDialog::clear()
{
    ui->txtHost->clear();
    ui->txtIP->clear();
}

void AddHostDialog::buttonBoxSelect(QAbstractButton *button)
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

AddHostDialog::~AddHostDialog()
{
    delete ui;
}
