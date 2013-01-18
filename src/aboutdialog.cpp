#include "aboutdialog.hpp"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox,SIGNAL(clicked(QAbstractButton*)),this,SLOT(closeDialog(QAbstractButton*)));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::closeDialog(QAbstractButton *)
{
    this->hide();
}
