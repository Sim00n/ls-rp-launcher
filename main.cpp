#include <QCoreApplication>
#include <localfiles.h>
#include <remotefiles.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LocalFiles lf;
    RemoteFiles rf(lf.c_gtaFolder);
    return a.exec();
}
