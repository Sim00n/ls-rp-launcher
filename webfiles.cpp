#include "webfiles.h"

WebFiles::WebFiles() {
    settings();
    checkStructure();
    loadConfig();
}

void WebFiles::settings() {
    homeDir = mDir.homePath() + "/AppData/Roaming";
    appDir = "/LS-RP";
    appFile = "/settings.txt";
}

void WebFiles::checkStructure() {

    if(!mDir.exists(homeDir + appDir)) {
        qDebug() << "There was an error with your home directory. Make sure that your %appdata% dirrectory is available.";
    }

    if(!mFile.exists(homeDir + appDir + appFile)) {
        qDebug() << "Creating " + homeDir + appDir + appFile;
        QFile textFile(homeDir + appDir + appFile);
        textFile.open(QIODevice::WriteOnly);

        QTextStream out(&textFile);
        out << "a=test";
        out << "b=124";
        out << "c=Sim00n";
        out << "d=52";

        textFile.close();
    }
}

void WebFiles::loadConfig() {

    qDebug("Opening config file ...\n");

    QFile textFile(homeDir + appDir + appFile);
    textFile.open(QIODevice::ReadOnly);
    QTextStream textStream(&textFile);

    qDebug() << "Key\tValue\n---\t-----";

    while (true)
    {
        QString line = textStream.readLine();
        if (line.isNull())
            break;
        else {
            QStringList sl = line.split("=");
            qDebug() << sl.at(0) + "\t" + sl.at(1);
        }
    }

    textFile.close();

    qDebug() << "\nDone.";
}
