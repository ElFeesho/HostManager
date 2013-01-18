#include "hostmenu.hpp"
#include <QString>
HostMenu::HostMenu(QObject *parent) :
    QMenu()
{
}

HostMenu::HostMenu(HostRecord *host) :
    QMenu(), _host(host)
{
    setTitle(host->host());
    toggleActive = addAction((_host->isActive())?("Deactivate"):("Activate"),this,SLOT(toggleTriggered()));
    edit = addAction("Edit",this,SLOT(editTriggered()));
    del = addAction("Delete", this, SLOT(deleteTriggered()));
}

bool HostMenu::toggleTriggered()
{
    toggleActive->setText((_host->isActive())?("Activate"):("Deactivate"));
    _host->toggleActive();
    emit toggleHostActive(_host);
    return true;
}

bool HostMenu::editTriggered()
{
    emit editHost(_host);
    return true;
}

bool HostMenu::deleteTriggered()
{
    emit deleteHost(_host);
    return true;
}
