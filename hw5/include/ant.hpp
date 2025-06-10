#ifndef ANT_HPP
#define ANT_HPP

#include "organism.hpp"
#include "newposcandidate.hpp"

enum class AntType
{
    QUEEN,
    MALE,
    WORKER
};

class Ant : public Organism
{
protected:
    int starvation;

public:
    Ant(World &world, int x, int y);

    virtual OrganismType getType() override;

    NewPosCandidate getNewPositionCandidate();

    virtual AntType getAntType() = 0;

    int getStarvation();
};

#endif
