#include <QCoreApplication>
#include <webfiles.h>
#include <remotefiles.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    WebFiles wf;
    RemoteFiles rf;
    return a.exec();
}
