#ifndef DOODLEBUG_HPP
#define DOODLEBUG_HPP

#include "organism.hpp"
#include "newposcandidate.hpp"

class DoodleBug : public Organism
{
private:
    int direction;
    int starvation;
    int breedTime;

public:
    DoodleBug(World &world, int x, int y);

    virtual char charRepresentation() override;
    virtual OrganismType getType() override;
    virtual void step() override;

    NewPosCandidate getNewPositionCandidate(int direction);

    int getStarvation();
};

#endif
