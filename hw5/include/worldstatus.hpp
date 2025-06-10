#ifndef WORLDSTATUS_HPP
#define WORLDSTATUS_HPP

#include <vector>
#include <memory>

class WorldStatus
{
private:
    int doodlebugCount;
    int queenAntCount;
    int queenAntCataglyphisCount;
    int maleAntCount;
    int workerAntCount;
    double doddlebugStarvationAverage;
    double antStarvationAverage;
    double queenAntNotBredTimeAverage;

public:
    WorldStatus(
        int doodlebugCount,
        int queenAntCount,
        int queenAntCataglyphisCount,
        int maleAntCount,
        int workerAntCount,
        double doddlebugStarvationAverage,
        double antStarvationAverage,
        double queenAntNotBredTimeAverage);

    int getDoodlebugCount();
    int getQueenAntCount();
    int getQueenAntCataglyphisCount();
    int getMaleAntCount();
    int getWorkerAntCount();
    double getDoddlebugStarvationAverage();
    double getAntStarvationAverage();
    double getQueenAntNotBredTimeAverage();
};

#endif

