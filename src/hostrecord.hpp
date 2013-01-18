#ifndef HOSTRECORD_HPP
#define HOSTRECORD_HPP

#include <QString>

class HostRecord
{
public:
    HostRecord(const QString &host, const QString &ip, bool active);
    ~HostRecord();

    bool isActive();
    const QString host();
    const QString ip();
    void host(const QString &host);
    void ip(const QString &ip);
    void toggleActive();
private:
    QString *hostname;
    QString *ipAddress;
    bool active;
};

#endif // HOSTRECORD_HPP
