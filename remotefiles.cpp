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
    QByteArray newData = NetRepl->read(2048);

    QString temp = QString(newData);
    qDebug() << temp;

    NetRepl->deleteLater();

    sums = temp.split(";");

    compareLocalChecksum();
}

void RemoteFiles::compareLocalChecksum() {

    QCryptographicHash hash(QCryptographicHash::Md5);

    QStringListIterator itter(sums);
    while (itter.hasNext()) {
        QStringList remoteFile = itter.next().split("|");

        bool flag = false;

        QDirIterator it(homeDir + appDir, QDirIterator::Subdirectories | QDirIterator::FollowSymlinks);
        while (it.hasNext()) {
            QString filePath = it.next();

            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly)) {
                hash.addData(file.readAll());
                QString md5 = QString(hash.result().toHex());

                qDebug() << md5;

                if(md5 == remoteFile.at(0).toLocal8Bit().constData()) {
                    flag = true;
                    qDebug() << "match";
                }
            }
        }
        if(!flag) {
            downloadList.append(remoteFile.at(1).toLocal8Bit().constData());
        }
    }

    downloadFiles();
}

void RemoteFiles::downloadFiles() {

    QStringListIterator dItter(downloadList);
    while(dItter.hasNext()) {
        QString filename = dItter.next();
        qDebug() << "Downloading " + filename;
        QDir directory(homeDir + appDir);
        QFile *rFile = new QFile(filename);
        rFile->open(QIODevice::WriteOnly);
        NetRepl = NetAccMan.get(QNetworkRequest(QUrl("http://pliki.ls-rp.net/modpack/"+filename)));
        connect(NetRepl, SIGNAL(finished()), this, SLOT(saveRemoteFile()));
        break;
    }
}

void RemoteFiles::saveRemoteFile() {
    QStringList filenameSplit = NetRepl->url().toString().split("/");
    QString filename = filenameSplit.at(filenameSplit.length() - 1).toLocal8Bit().constData();
    qDebug() << filename;

    QDir directory(homeDir + appDir);
    directory.setCurrent(homeDir + appDir);
    QFile *wFile = new QFile(filename);
    wFile->open(QIODevice::WriteOnly);
    wFile->write(NetRepl->readAll());
    wFile->close();
    qDebug() << "Saved file "+filename;
    NetRepl->close();

    downloadList.removeFirst();
    downloadFiles();
}
