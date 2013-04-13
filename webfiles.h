#ifndef WEBFILES_H
#define WEBFILES_H

#include <QDebug>
#include <QString>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStringRef>
#include <QTextStream>

class WebFiles: public QObject {
    QDir mDir;
    QFile mFile;
    QString homeDir;
    QString appDir;
    QString appFile;

    public:
        WebFiles();
        void settings();
        void checkStructure();
        void loadConfig();
};

#endif // WEBFILES_H
