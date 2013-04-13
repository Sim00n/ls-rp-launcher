#ifndef REMOTEFILES_H
#define REMOTEFILES_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <QByteArray>
#include <QCryptographicHash>
#include <QFile>
#include <QDirIterator>
#include <QStringListIterator>
#include <QStringList>

class RemoteFiles: public QObject {

    Q_OBJECT

    QNetworkAccessManager NetAccMan;
    QNetworkReply *NetRepl;
    QStringList downloadList;

    QString gtaDir;
    QStringList sums;

    public:
        RemoteFiles(QString gtaDir);
        void getRemoteChecksum();
        void compareLocalChecksum();
        void downloadFiles();

    public slots:
        void parseChecksum();
        void saveRemoteFile();
        //void test(qint64 bytesReceived, qint64 bytesTotal);

};

#endif // REMOTEFILES_H
