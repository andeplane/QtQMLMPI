#include "mpicontroller.h"

MPIController::MPIController(QObject *parent) : QObject(parent)
{

}

void MPIController::initialize(int worldRank, int worldSize)
{
    m_worldRank = worldRank;
    m_worldSize = worldSize;
    // Split the communicator based on the color and use the
    // original rank for ordering
    if(worldRank==0) {
        MPI_Comm_split(MPI_COMM_WORLD, MPI_UNDEFINED, worldRank, &slave_comm);
    } else {
        MPI_Comm_split(MPI_COMM_WORLD, 1, worldRank, &slave_comm);
    }

    m_isInitialized = true;
}

void MPIController::setHost()
{
    m_isHost = true;
}

void MPIController::setSlave()
{
    m_isHost = false;
}

int MPIController::numberOfProcessors() const
{
    return m_worldSize;
}

int MPIController::worldSize() const
{
    return m_worldSize;
}

int MPIController::worldRank() const
{
    return m_worldRank;
}

void MPIController::setNumberOfProcessors(int numberOfProcessors)
{
    if (m_worldSize == numberOfProcessors)
        return;

    m_worldSize = numberOfProcessors;
    emit numberOfProcessorsChanged(numberOfProcessors);
}

