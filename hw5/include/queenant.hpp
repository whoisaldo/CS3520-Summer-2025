#ifndef QUEENANT_HPP
#define QUEENANT_HPP

#include "ant.hpp"

class QueenAnt : public Ant
{
private:
    bool cataglyphis;
    int matingCooldown;
    int bearTime;
    int notBredTime;

public:
    QueenAnt(World &world, int x, int y);

    virtual char charRepresentation() override;
    void step() override;
    virtual AntType getAntType() override;

    int getNotBredTime();
    bool isCataglyphis();
};

#endif
