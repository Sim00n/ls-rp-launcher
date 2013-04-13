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

class RemoteFiles: public QObject {

    Q_OBJECT

    QNetworkAccessManager NetAccMan;
    QNetworkReply *NetRepl;

    public:
        RemoteFiles();
        void getRemoteChecksum();

    public slots:
        void parseChecksum();

};

#endif // REMOTEFILES_H
