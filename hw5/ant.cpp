#include <array>
#include <random>

#include "ant.hpp"

#include "world.hpp"
#include "newposcandidate.hpp"

using namespace std;

Ant::Ant(World &world, int x, int y) : Organism(world, x, y)
{
    starvation = -1;
}

OrganismType Ant::getType()
{
    return OrganismType::ANT;
}

NewPosCandidate Ant::getNewPositionCandidate()
{
    static const array<pair<int, int>, 8> relativeAdjacentPositions = {
        {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}};
    uniform_int_distribution<int> distribution(0, 7);
    int randomDirection = distribution(world.getGen());
    int relX = relativeAdjacentPositions.at(randomDirection).first;
    int relY = relativeAdjacentPositions.at(randomDirection).second;

    // Bounce off until the ant is in a valid position, each axis is doubled
    bool bounced = false;
    while (relX + x < 0 || relX + x >= world.getWidth() || relY + y < 0 || relY + y >= world.getHeight())
    {
        if (relX + x < 0 || relX + x >= world.getWidth())
        {
            relY *= 2;
            relX = 0;
            bounced = true;
        }
        if (relY + y < 0 || relY + y >= world.getHeight())
        {
            relX *= 2;
            relY = 0;
            bounced = true;
        }
    }

    return NewPosCandidate(relX + x, relY + y, bounced);
}

int Ant::getStarvation()
{
    return starvation;
}

