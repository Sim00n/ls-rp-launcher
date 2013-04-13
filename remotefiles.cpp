#include "remotefiles.h"

RemoteFiles::RemoteFiles(QString gtaDir) {

    this->gtaDir = gtaDir + "/SAMP/";
    getRemoteChecksum();
}

void RemoteFiles::getRemoteChecksum() {
    QNetworkRequest request(QUrl("http://dev.ls-rp.net/checksum.php"));
    NetRepl = NetAccMan.get(request);
    connect(NetRepl, SIGNAL(finished()), this, SLOT(parseChecksum()));
}

void RemoteFiles::parseChecksum()
{
    QByteArray newData = NetRepl->readAll();

    QString temp = QString(newData);
    qDebug() << "Remote hash: " << temp << "\n";

    NetRepl->deleteLater();

    sums = temp.split(";");

    compareLocalChecksum();
}

void RemoteFiles::compareLocalChecksum() {

    QCryptographicHash hash(QCryptographicHash::Md5);

    QStringListIterator itter(sums);
    while (itter.hasNext()) {
        QStringList remoteFile = itter.next().split("|");
        QString remoteMD5 = remoteFile.at(0).toLocal8Bit().constData();

        bool flag = false;

        QDirIterator it(gtaDir, QDirIterator::Subdirectories | QDirIterator::FollowSymlinks);
        while (it.hasNext()) {
            QString filePath = it.next();

            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly)) {
                hash.addData(file.readAll());
                QString localMD5 = hash.result().toHex();
                hash.reset();

                if(localMD5 == remoteMD5) {
                    flag = true;
                }
            }
        }
        if(!flag) {
            downloadList.append(remoteFile.at(1).toLocal8Bit().constData());
        }
    }

    if(downloadList.length() > 0) {
        downloadFiles();
    } else {
        qDebug() << "All files are current.";
    }
}

void RemoteFiles::downloadFiles() {

    QStringListIterator dItter(downloadList);
    while(dItter.hasNext()) {
        QString filename = dItter.next();
        qDebug() << "Downloading " + filename;
        QFile *rFile = new QFile(filename);
        rFile->open(QIODevice::WriteOnly);
        NetRepl = NetAccMan.get(QNetworkRequest(QUrl("http://pliki.ls-rp.net/modpack/"+filename)));
        connect(NetRepl, SIGNAL(finished()), this, SLOT(saveRemoteFile()));
        //connect(NetRepl, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(test(qint64, qint64)));
        break;
    }
}

void RemoteFiles::saveRemoteFile() {
    QStringList filenameSplit = NetRepl->url().toString().split("/");
    QString filename = filenameSplit.at(filenameSplit.length() - 1).toLocal8Bit().constData();
    qDebug() << filename;

    QDir directory(gtaDir);
    directory.setCurrent(gtaDir);
    QFile *wFile = new QFile(filename);
    wFile->open(QIODevice::WriteOnly);
    wFile->write(NetRepl->readAll());
    wFile->close();
    qDebug() << "Saved file "+filename;
    NetRepl->close();

    downloadList.removeFirst();
    downloadFiles();
}
/*
void RemoteFiles::test(qint64 bytesReceived, qint64 bytesTotal) {
    qDebug() << bytesReceived;
}
*/

/*
 * The above is a test of the progress bar for the actuall, visual launcher.
 * Remember to uncomment    connect() in RemoteFIles::downloadFiles()
 *                          RemoteFiles::test()
 * and                      slot definition in remotefiles.h
 */
