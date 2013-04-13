#include "localfiles.h"

LocalFiles::LocalFiles() {
    settings();
    checkStructure();
    loadConfig();
}

void LocalFiles::settings() {
    homeDir = mDir.homePath() + "/AppData/Roaming";
    appDir = "/LS-RP";
    configFile = "/settings.txt";
}

void LocalFiles::checkStructure() {

    if(!mDir.exists(homeDir + appDir)) {
        qDebug() << "There was an error with your home directory. Make sure that your %appdata% dirrectory is available.";
    }

    if(!mFile.exists(homeDir + appDir + configFile)) {
        fixConfigFile();
    }
}

void LocalFiles::loadConfig() {

    qDebug("Opening config file ...\n");

    QFile textFile(homeDir + appDir + configFile);
    textFile.open(QIODevice::ReadOnly);
    QTextStream textStream(&textFile);

    while (true)
    {
        QString line = textStream.readLine();
        if (line.isNull())
            break;
        else {
            QStringList sl = line.split("=");
            QString name = sl.at(0);
            QString value = sl.at(1);

            // I know this is probably the ugliest thing you've ever seen but I'm working on it.
            // Yo no hablo c++.
            if(name == "gta")
                c_gtaFolder = value;
            else if(name == "nickname")
                c_nickname = value;
            else if(name == "lastupdate")
                c_lastupdate = value;
            else if(name == "lastversion")
                c_lastversion = value;
        }
    }

    bool flag = false;
    if(c_gtaFolder.length() == 0 || c_nickname.length() == 0 || c_lastupdate.length() == 0 || c_lastversion == 0) {
        flag = true;
    }

    QFile gtaFolder(c_gtaFolder);
    if(!gtaFolder.exists()) {
        flag = true;
    }

    if(flag) {
        qDebug() << "Something wrong with the config file. Le'me make a new one for you dude.";
        fixConfigFile();
        checkStructure();
        loadDefaults();
    }

    qDebug() << "Gta folder: " << c_gtaFolder;
    qDebug() << "Nickname: " << c_nickname;
    qDebug() << "Last update: " << c_lastupdate;
    qDebug() << "Last version: " << c_lastversion;

    textFile.close();

    qDebug() << "\nConfig file has been read.\n";
}

void LocalFiles::loadDefaults() {
    c_gtaFolder = "C:/Program Files/Rockstar Games/GTA San Andreas/";
    c_nickname = "Unknown";
    c_lastupdate = "1/1/1970 00:00:00";
    c_lastversion = "1.0";
}

void LocalFiles::fixConfigFile() {
    qDebug() << "Creating " + homeDir + appDir + configFile;
    QFile textFile(homeDir + appDir + configFile);
    textFile.open(QIODevice::WriteOnly);

    QTextStream out(&textFile);
    out << "gta=C:/Program Files/Rockstar Games/GTA San Andreas/\n";
    out << "nickname=Unknown\n";
    out << "lastupdate=1/1/1970 00:00:00\n";
    out << "lastversion=1.0\n";

    textFile.close();
}
