#include "remotefiles.h"

RemoteFiles::RemoteFiles(QString homeDir, QString appDir, QString appFile) {

    this->homeDir = homeDir;
    this->appDir = appDir;
    this->appFile = appFile;
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

    QString temp = QString(newData);
    qDebug() << temp;

    NetRepl->deleteLater();

    sums = temp.split(";");

    compareLocalChecksum(temp);
}

void RemoteFiles::compareLocalChecksum(QString checksum) {

    QCryptographicHash hash(QCryptographicHash::Md5);
    QStringList downloadList;

    QStringListIterator itter(sums);
    while (itter.hasNext()) {
        QStringList remoteFile = itter.next().split("|");

        bool flag = false;

        QDirIterator it(homeDir + appDir, QDirIterator::Subdirectories | QDirIterator::FollowSymlinks);
        while (it.hasNext()) {
            QString filePath = it.next();
            if(!filePath.contains(".txt")) continue;

            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly)) {
                hash.addData(file.readAll());
                QString md5 = QString(hash.result().toHex());

                if(md5 == remoteFile.at(0).toLocal8Bit().constData()) {
                    flag = true;
                }
            }
        }
        if(!flag) {
            downloadList.append(remoteFile.at(1).toLocal8Bit().constData());
        }
    }

    /*
    QStringListIterator dItter(downloadList);
    while(dItter.hasNext()) {
        qDebug() << QString(dItter.next());
    }
    */

    downloadFiles(downloadList);
}

void RemoteFiles::downloadFiles(QStringList downloadList) {

    QStringListIterator dItter(downloadList);
    while(dItter.hasNext()) {
        QString filename = dItter.next();
        qDebug() << "Downloading " + filename;
    }

}
