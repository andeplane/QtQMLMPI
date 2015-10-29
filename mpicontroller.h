#ifndef MPICONTROLLER_H
#define MPICONTROLLER_H
#include <mpi.h>
#include <QObject>
// Inspired by http://mpitutorial.com/tutorials/introduction-to-groups-and-communicators/
class MPIController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int numberOfProcessors READ numberOfProcessors WRITE setNumberOfProcessors NOTIFY numberOfProcessorsChanged)
    Q_PROPERTY(int worldSize READ worldSize NOTIFY worldSizeChanged)
    Q_PROPERTY(int worldRank READ worldRank NOTIFY worldRankChanged)
private:
    int m_worldRank = -1;
    int m_worldSize = -1;
    bool m_isInitialized = false;
    bool m_isHost = false;
    MPI_Comm slave_comm;

public:
    explicit MPIController(QObject *parent = 0);
    void initialize(int worldRank, int worldSize);
    ~MPIController() { }
    void setHost();
    void setSlave();
    int numberOfProcessors() const;
    virtual void runSlaveLoop() = 0;
    int worldSize() const;
    int worldRank() const;

public slots:
    void setNumberOfProcessors(int numberOfProcessors);
signals:
    void numberOfProcessorsChanged(int numberOfProcessors);
    void worldSizeChanged(int worldSize);
    void worldRankChanged(int worldRank);
};

#endif // MPICONTROLLER_H
