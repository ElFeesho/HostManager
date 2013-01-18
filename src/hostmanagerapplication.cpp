#include "hostmanagerapplication.hpp"
#include <QString>
#include <QApplication>
#include <QDebug>
#include <QProcess>

HostManagerApplication::HostManagerApplication(QObject *parent) :
    QObject(parent), _icon(new QSystemTrayIcon(parent)),
    _ctxMenu(new QMenu()), _addEntry(new QAction(NULL)), addHostWND(new AddHostWindow()),
    editHostWND(new EditHostWindow()), aboutDLG(new AboutDialog()),
    hostFileManager(new HostFileManager()), hostSubMenus(new QVector<HostMenu*>)
{
    _icon->setIcon(QIcon(":/icons/res/icon.png"));
    _icon->setVisible(true);

    _addEntry->setText("Add New Entry");

    _ctxMenu->addAction(_addEntry);
    _ctxMenu->addAction("Flush DNS Cache",this, SLOT(flushDNSTriggered()));
    _ctxMenu->addSeparator();

    connect(_addEntry,SIGNAL(triggered()),this,SLOT(addEntryTriggered()));
    hostsMenu = _ctxMenu->addMenu("Hosts");

    _ctxMenu->addSeparator();

    _ctxMenu->addAction("About",this,SLOT(aboutTriggered()));
    _ctxMenu->addAction("Exit",this,SLOT(exitTriggered()));

    _icon->setContextMenu(_ctxMenu);
    populateSubHostsMenu();
    connect(addHostWND, SIGNAL(requestAdd(QString,QString)),this,SLOT(addNewEntry(QString,QString)));
    connect(editHostWND, SIGNAL(requestEdit(HostRecord*)),this,SLOT(editRecord(HostRecord*)));
}

HostManagerApplication::~HostManagerApplication()
{
    qDebug() << ":: HostManagerApplication dtor";
    delete _icon;
    delete _addEntry;
    delete _ctxMenu;
    delete addHostWND;
    delete editHostWND;
    delete aboutDLG;
    delete hostFileManager;
}

void HostManagerApplication::populateSubHostsMenu()
{
    if(hostSubMenus->count()>0)
    {
        hostsMenu->clear();
        hostSubMenus->clear();
    }
    foreach(HostRecord *host, *hostFileManager->getHosts())
    {
        HostMenu *nMenu = new HostMenu(host);
        hostsMenu->addMenu(nMenu);
        hostSubMenus->append(nMenu);
        connect(nMenu, SIGNAL(toggleHostActive(HostRecord*)),this, SLOT(toggleHostActive(HostRecord*)));
        connect(nMenu, SIGNAL(editHost(HostRecord*)),this, SLOT(editHost(HostRecord*)));
        connect(nMenu, SIGNAL(deleteHost(HostRecord*)),this, SLOT(removeHost(HostRecord*)));
    }
}

void HostManagerApplication::addNewEntry(const QString &host, const QString &ip)
{
    qDebug() << "Adding host "<< host <<" and IP " <<ip << endl;
    if(hostFileManager->addNewHost(host,ip))
    {
        populateSubHostsMenu();
    }
    else
    {
        _icon->showMessage("Failed to Add Host","It wasn't possible to add the new host.",QSystemTrayIcon::Critical);
    }
}

void HostManagerApplication::editRecord(HostRecord *record)
{
    if(hostFileManager->syncHosts())
    {
        populateSubHostsMenu();
        _icon->showMessage("Updated Host","The host was successfully updated. Flush the DNS cache to make the changes immediately.");
    }
    else
    {
        _icon->showMessage("Failed to Edit Host","It wasn't possible to edit the selected host.",QSystemTrayIcon::Critical);
    }
}

void HostManagerApplication::toggleHostActive(HostRecord *host)
{
    if(!hostFileManager->syncHosts())
    {
        _icon->showMessage("Failed to Toggle the Host","It wasn't possible to de/activate the selected host.",QSystemTrayIcon::Critical);
    }
    else
    {
        if(host->isActive())
        {
            _icon->showMessage(QString(host->host()).append(" is now active"),"The host is now active. Flush the DNS to make the changes immediately.");
        }
        else
        {
            _icon->showMessage(QString(host->host()).append(" is now deactivated"),"The host is now deactivated. Flush the DNS to make the changes immediately.");
        }
    }
}

void HostManagerApplication::removeHost(HostRecord *host)
{
    if(hostFileManager->removeHost(host))
    {
        _icon->showMessage("Host Removed","The host has been removed from your DNS list");
        populateSubHostsMenu();
    }
    else
    {
        _icon->showMessage("Failed to Remove Host","It wasn't possible to remove the selected host.",QSystemTrayIcon::Critical);
    }
}

void HostManagerApplication::editHost(HostRecord *host)
{
    QStringList ips;
    foreach(HostRecord *record, *hostFileManager->getHosts())
    {
        if(!ips.contains(record->ip()))
            ips << record->ip();
    }
    editHostWND->setCompletionList(ips);
    editHostWND->setHost(host);
    editHostWND->show();
}

bool HostManagerApplication::flushDNSTriggered()
{
    QProcess flushDNS;
    QStringList args;
    args << "/flushdns";
    flushDNS.start("ipconfig", args);
    flushDNS.waitForFinished();
    QString output(flushDNS.readAll());
    if(output.indexOf("Successfully flushed the DNS Resolver Cache.")!=-1)
        _icon->showMessage("Flushed DNS","The DNS cache has been flushed. Restart applications to ensure you see an effect.");
    else
        _icon->showMessage("DNS Cache Flush Unsuccessful", "It wasn't possible to flush the DNS cache.",QSystemTrayIcon::Critical);
    return true;
}

bool HostManagerApplication::aboutTriggered()
{
    aboutDLG->show();
    return true;
}

bool HostManagerApplication::exitTriggered()
{
    if(_icon!=NULL)
        _icon->setVisible(false);
    QApplication::exit();
    return true;
}

bool HostManagerApplication::addEntryTriggered()
{
    addHostWND->clear();
    QStringList ips;
    foreach(HostRecord *record, *hostFileManager->getHosts())
    {
        if(!ips.contains(record->ip()))
            ips << record->ip();
    }
    addHostWND->setCompletionList(ips);
    addHostWND->show();
    return true;
}
