#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QObject>
#include <QQuickWindow>
#include <QString>

#include "mympicontroller.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<MyMPIController>("QMPI", 1, 0, "MyMPIController");

    MPI_Init(&argc, &argv);
    int worldRank;
    int worldSize;
    // Get the rank and size in the original communicator
    MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
    MyMPIController mpiController;
    mpiController.initialize(worldRank, worldSize);

    if(worldRank==0) {
        QGuiApplication app(argc, argv);
        QQmlApplicationEngine engine;

        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
        engine.rootContext()->setContextProperty("mpi", &mpiController);

        mpiController.setHost();
        app.exec();

    } else {
        mpiController.setSlave();
        mpiController.runSlaveLoop();
    }

    MPI_Finalize();
    return 0;
}

