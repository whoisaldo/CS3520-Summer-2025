#ifndef MALEANT_HPP
#define MALEANT_HPP

#include "ant.hpp"

class MaleAnt : public Ant
{
public:
    MaleAnt(World &world, int x, int y);

    virtual char charRepresentation() override;
    virtual void step() override;
    virtual AntType getAntType() override;
};

#endif
