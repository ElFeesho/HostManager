#include "hostfilemanager.hpp"
#include <QApplication>
#include <QFile>
#include <QRegExp>
#include <QDebug>
#include <QStringList>
#include <QTextStream>

HostFileManager::HostFileManager(QObject *parent) :
    QObject(parent), records(new QVector<HostRecord*>())
{
    parseHosts();
}

bool HostFileManager::addNewHost(const QString &host, const QString &ip)
{
    records->append(new HostRecord(host, ip, true));
    if(!syncHosts())
    {
        return false;
    }
    return true;
}

bool HostFileManager::removeHost(HostRecord *host)
{
    for(int i = 0;i<records->count();i++)
    {
        if(records->at(i) == host)
        {
            records->remove(i);
            delete host;
            if(!syncHosts())
            {
                return false;
            }
            return true;
        }

    }
    return false;
}

QVector<HostRecord*> *HostFileManager::getHosts()
{
    return records;
}

bool HostFileManager::parseHosts()
{
    QFile::copy("C:\\Windows\\System32\\Drivers\\etc\\hosts","hosts.bak");
   QFile hosts("C:\\Windows\\System32\\Drivers\\etc\\hosts");

   hosts.open(QFile::ReadOnly);
   QString hostsText(hosts.readAll());
   QStringList lines = hostsText.split("\n");
   QRegExp hlineMatch("([0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3})\\s{1,}(\\S{1,}) #hm$");

   foreach(QString line, lines)
   {
       line.chop(1);
       int pos = 0;

       pos = hlineMatch.indexIn(line);
       if(pos!=-1)
           records->append(new HostRecord(hlineMatch.cap(2),hlineMatch.cap(1),line[0] != '#'));
       else
           originalFile<<line;
       qDebug() << line;
   }
    qDebug() << "Found hosts: " << records->count() << endl;
   hosts.close();

   qDebug() << "Original file: ";
   foreach(QString line, originalFile)
   {
       qDebug() << line;
   }

   return true;
}

bool HostFileManager::syncHosts()
{
    QFile hosts("C:\\Windows\\System32\\Drivers\\etc\\hosts");
    if(!hosts.open(QFile::WriteOnly))
    {
        return false;
    }

    QTextStream outstream(&hosts);


    // Write the original file in first.
    for(int i =0;i< originalFile.count();i++)
    {
        if(i < originalFile.count()-1)
        {
            outstream << originalFile.at(i) << "\r\n";
        }
    }

    foreach(HostRecord *host, *records)
    {
        if(host->isActive())
            outstream << host->ip() << " " << host->host() << " #hm\r\n";
        else
            outstream << "#" << host->ip() << " " << host->host() << " #hm\r\n";
    }

    hosts.close();
    return true;
}

HostFileManager::~HostFileManager()
{
    qDebug() << ":: HostFileManager dtor";
    qDeleteAll(*records);
    delete records;
}
