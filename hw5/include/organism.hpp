#ifndef ORGANISM_HPP
#define ORGANISM_HPP

#include <memory>

enum class OrganismType
{
    ANT,
    DOODLEBUG
};

class World;

class Organism
{
protected:
    World &world;
    int x;
    int y;

    void setPosition(int x, int y);

public:
    Organism(World &world, int x, int y);

    virtual char charRepresentation() = 0;
    virtual OrganismType getType() = 0;
    virtual void step() = 0;

    friend class World;
};

#endif
