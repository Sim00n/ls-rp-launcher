#include <QCoreApplication>
#include <webfiles.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    WebFiles wf;
    return a.exec();
}
