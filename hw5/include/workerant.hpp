#ifndef WORKERANT_HPP
#define WORKERANT_HPP

#include "ant.hpp"

class WorkerAnt : public Ant
{
public:
    WorkerAnt(World &world, int x, int y);

    virtual char charRepresentation() override;
    virtual void step() override;
    virtual AntType getAntType() override;
};

#endif
