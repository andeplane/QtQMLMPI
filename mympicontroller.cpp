#include "mympicontroller.h"
#include <QDebug>
#include <string>

MyMPIController::MyMPIController(QObject *parent) : MPIController(parent)
{

}

void MyMPIController::runSlaveLoop()
{
    int command;
    char *str = new char[8192];

    MPI_Status status;
    while(true) {
        MPI_Bcast(&command,1,MPI_INT,0,MPI_COMM_WORLD);
        if(command==0) {
            int messageLength;
            MPI_Recv(&messageLength,1,MPI_INT,0,0,MPI_COMM_WORLD, &status);
            MPI_Recv(str,messageLength,MPI_CHAR,0,0,MPI_COMM_WORLD, &status);
            qDebug() << worldRank() << " got message: " << str;
        } else if(command==1) {
            int messageLength;
            MPI_Bcast(&messageLength, 1, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Bcast(str, messageLength, MPI_CHAR, 0, MPI_COMM_WORLD);
            qDebug() << worldRank() << " got message: " << str;
        } else if(command==2) {
            qDebug() << worldRank() << " will exit.";
            break;
        }
    }
}

void MyMPIController::sendMessageToAll(QString message)
{
    int command = 1;
    MPI_Bcast(&command,1,MPI_INT,0,MPI_COMM_WORLD);

    const char *msg = message.toStdString().c_str();
    int messageLength = message.toStdString().size()+1;
    MPI_Bcast(&messageLength, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast((void*)msg, messageLength, MPI_CHAR, 0, MPI_COMM_WORLD);
}

void MyMPIController::sendMessageToEach(QString message)
{
    int command = 0;
    MPI_Bcast(&command,1,MPI_INT,0,MPI_COMM_WORLD);
    for(int i=1; i<worldSize(); i++) {
        QString newMessage = QString("Message to %1: %2").arg(i).arg(message);
        const char *msg = newMessage.toStdString().c_str();

        int messageLength = newMessage.toStdString().size()+1;
        MPI_Send(&messageLength, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        MPI_Send((void*)msg, messageLength, MPI_CHAR, i, 0, MPI_COMM_WORLD);
    }
}

void MyMPIController::quit()
{
    int command = 2;
    MPI_Bcast(&command,1,MPI_INT,0,MPI_COMM_WORLD);
}
