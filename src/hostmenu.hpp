#ifndef HOSTMENU_HPP
#define HOSTMENU_HPP

#include <QMenu>
#include <QAction>
#include "hostrecord.hpp"

class HostMenu : public QMenu
{
    Q_OBJECT
public:
    explicit HostMenu(QObject *parent = 0);
    HostMenu(HostRecord *host);

signals:
    void toggleHostActive(HostRecord *);
    void editHost(HostRecord *);
    void deleteHost(HostRecord *);
public slots:
    bool toggleTriggered();
    bool editTriggered();
    bool deleteTriggered();
private:
    HostRecord *_host;
    QAction *toggleActive;
    QAction *edit;
    QAction *del;
};

#endif // HOSTMENU_HPP
