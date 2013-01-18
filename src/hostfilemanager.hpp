#ifndef HOSTFILEMANAGER_HPP
#define HOSTFILEMANAGER_HPP

#include <QObject>
#include <QVector>
#include <QStringList>
#include "hostrecord.hpp"
class HostFileManager : public QObject
{
    Q_OBJECT
public:
    explicit HostFileManager(QObject *parent = 0);
    ~HostFileManager();

    bool addNewHost(const QString &host, const QString &ip);
    bool removeHost(HostRecord *host);
    QVector<HostRecord*> *getHosts();
    bool parseHosts();
    bool syncHosts();
signals:

public slots:


private:
    QVector<HostRecord*> *records;
    QStringList originalFile;
};

#endif // HOSTFILEMANAGER_HPP
