#include "worldstatus.hpp"

WorldStatus::WorldStatus(
    int doodlebugCount,
    int queenAntCount,
    int queenAntCataglyphisCount,
    int maleAntCount,
    int workerAntCount,
    double doddlebugStarvationAverage,
    double antStarvationAverage,
    double queenAntNotBredTimeAverage) : doodlebugCount(doodlebugCount),
                                      queenAntCount(queenAntCount),
                                      queenAntCataglyphisCount(queenAntCataglyphisCount),
                                      maleAntCount(maleAntCount),
                                      workerAntCount(workerAntCount),
                                      doddlebugStarvationAverage(doddlebugStarvationAverage),
                                      antStarvationAverage(antStarvationAverage),
                                      queenAntNotBredTimeAverage(queenAntNotBredTimeAverage) {}

int WorldStatus::getDoodlebugCount()
{
    return doodlebugCount;
}

int WorldStatus::getQueenAntCount()
{
    return queenAntCount;
}

int WorldStatus::getMaleAntCount()
{
    return maleAntCount;
}

int WorldStatus::getWorkerAntCount()
{
    return workerAntCount;
}

int WorldStatus::getQueenAntCataglyphisCount()
{
    return queenAntCataglyphisCount;
}

double WorldStatus::getDoddlebugStarvationAverage()
{
    return doddlebugStarvationAverage;
}

double WorldStatus::getAntStarvationAverage()
{
    return antStarvationAverage;
}

double WorldStatus::getQueenAntNotBredTimeAverage()
{
    return queenAntNotBredTimeAverage;
}
