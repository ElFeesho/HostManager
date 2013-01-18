#ifndef HOSTMANAGERAPPLICATION_HPP
#define HOSTMANAGERAPPLICATION_HPP

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QVector>
#include "hostmenu.hpp"
#include "hostfilemanager.hpp"
#include "addhostwindow.hpp"
#include "edithostwindow.hpp"
#include "aboutdialog.hpp"

class HostManagerApplication : public QObject
{
    Q_OBJECT
public:
    explicit HostManagerApplication(QObject *parent = 0);
    ~HostManagerApplication();
private:
    void populateSubHostsMenu();

signals:

public slots:
    bool addEntryTriggered();
    bool flushDNSTriggered();
    bool aboutTriggered();
    bool exitTriggered();

    void addNewEntry(const QString &host, const QString &ip);
    void editRecord(HostRecord *record);

    void toggleHostActive(HostRecord *host);
    void editHost(HostRecord *host);
    void removeHost(HostRecord *host);
private:
    QSystemTrayIcon *_icon;
    QMenu *_ctxMenu;

    QAction *_addEntry;

    AddHostWindow *addHostWND;
    EditHostWindow *editHostWND;
    AboutDialog *aboutDLG;

    HostFileManager *hostFileManager;

    QMenu *hostsMenu;
    QVector<HostMenu*> *hostSubMenus;
};

#endif // HOSTMANAGERAPPLICATION_HPP
