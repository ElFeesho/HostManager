#include "hostrecord.hpp"
#include <QDebug>

HostRecord::HostRecord(const QString &host, const QString &ip, bool active)
    : hostname(new QString(host)), ipAddress(new QString(ip)), active(active)
{
}

HostRecord::~HostRecord()
{
    qDebug() << ":: HostRecord dtor " << *hostname << " " << *ipAddress;
    delete hostname;
    delete ipAddress;
}

void HostRecord::toggleActive()
{
    active = !active;
}

bool HostRecord::isActive()
{
    return active;
}

const QString HostRecord::host()
{
    return *hostname;
}

const QString HostRecord::ip()
{
    return *ipAddress;
}

void HostRecord::host(const QString &host)
{
    delete hostname;
    hostname = new QString(host);
}

void HostRecord::ip(const QString &ip)
{
    delete ipAddress;
    ipAddress = new QString(ip);
}
