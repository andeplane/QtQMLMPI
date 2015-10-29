#ifndef MYMPICONTROLLER_H
#define MYMPICONTROLLER_H
#include <QObject>
#include "mpicontroller.h"

class MyMPIController : public MPIController
{
    Q_OBJECT
private:

public:
    explicit MyMPIController(QObject *parent = 0);
    virtual void runSlaveLoop();
public slots:
    void sendMessageToAll(QString message);
    void sendMessageToEach(QString message);
    void quit();

};
// Q_DECLARE_METATYPE(MyMPIController)
#endif // MYMPICONTROLLER_H
