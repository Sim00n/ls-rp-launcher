#ifndef LocalFiles_H
#define LocalFiles_H

#include <QDebug>
#include <QString>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStringRef>
#include <QTextStream>

class LocalFiles: public QObject {
    QDir mDir;
    QFile mFile;

    public:
        QString homeDir;
        QString appDir;
        QString configFile;

        QString c_gtaFolder;
        QString c_nickname;
        QString c_lastupdate;
        QString c_lastversion;

        LocalFiles();

        void settings();
        void checkStructure();
        void loadConfig();
        void loadDefaults();
        void fixConfigFile();
};

#endif // LocalFiles_H
