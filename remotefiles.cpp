#include "remotefiles.h"

RemoteFiles::RemoteFiles() {
    getRemoteChecksum();
}

void RemoteFiles::getRemoteChecksum() {
    QNetworkRequest request(QUrl("http://dev.ls-rp.net/checksum.php"));
    NetRepl = NetAccMan.get(request);
    connect(NetRepl, SIGNAL(finished()), this, SLOT(parseChecksum()));
}


void RemoteFiles::parseChecksum()
{
    //qDebug() << (QString("isFinished:").append(QString::number(NetRepl->isFinished())));
    //qDebug() << (QString("error:").append(QString::number(NetRepl->error())));

    QByteArray newData = NetRepl->read(2048);
    qDebug() << (QString(newData));

    NetRepl->deleteLater();
}
