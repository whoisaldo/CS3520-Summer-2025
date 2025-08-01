#include <array>
#include <memory>
#include <algorithm>
#include <iostream>

#include "doodlebug.hpp"

#include "world.hpp"

using namespace std;

DoodleBug::DoodleBug(World &world, int x, int y) : Organism(world, x, y)
{
    uniform_int_distribution<int> distribution(0, 7);
    direction = distribution(world.getGen());
    starvation = 15;
    // breedTime = 10;
    breedTime = 10 + 6; // +6 for initial breeding time to prevent breed bomb + offset for initial breeding time
}

OrganismType DoodleBug::getType()
{
    return OrganismType::DOODLEBUG;
}

char DoodleBug::charRepresentation()
{
    return 'X';
}

void DoodleBug::step()
{
    bool initial = true;
    unique_ptr<NewPosCandidate> foundAtDirection = nullptr;
    for (int i = direction; i != (direction + 8) % 8 || initial; i = (i + 1) % 8)
    {
        initial = false;
        NewPosCandidate newPosCandidate = getNewPositionCandidate(i);
        if (!world.isEmpty(newPosCandidate.getX(), newPosCandidate.getY()) && world.getEntity(newPosCandidate.getX(), newPosCandidate.getY())->getType() == OrganismType::ANT)
        {
            foundAtDirection = make_unique<NewPosCandidate>(newPosCandidate);
            break;
        }
    }

    if (foundAtDirection != nullptr)
    {
        // Replace the eaten ant with the doodlebug
        world.removeEntity(foundAtDirection->getX(), foundAtDirection->getY());
        world.moveEntity(x, y, foundAtDirection->getX(), foundAtDirection->getY());
        starvation = 15;
    }
    else
    {
        starvation--;

        uniform_int_distribution<int> distribution(0, 1);
        bool changeDirection = distribution(world.getGen());
        if (changeDirection)
        {
            direction = (direction + 1) % 8;
        }

        NewPosCandidate newPosCandidate = getNewPositionCandidate(direction);

        bool mayMove =
            world.isEmpty(newPosCandidate.getX(), newPosCandidate.getY()) ||
            (x == newPosCandidate.getX() && y == newPosCandidate.getY() && newPosCandidate.getBounced());
        if (mayMove)
        {
            world.moveEntity(x, y, newPosCandidate.getX(), newPosCandidate.getY());
        }
    }

    if (starvation == 0)
    {
        world.removeEntity(x, y);
    }

    breedTime--;
    if (breedTime == 0)
    {
        vector<pair<int, int>> relativeAdjacentPositions = {
            {{-2, -2}, {-2, -1}, {-2, 0}, {-2, 1}, {-2, 2}, {-1, -2}, {-1, 2}, {0, -2}, {0, 2}, {1, -2}, {1, 2}, {2, -2}, {2, -1}, {2, 0}, {2, 1}, {2, 2}}};
        shuffle(relativeAdjacentPositions.begin(), relativeAdjacentPositions.end(), world.getGen());

        int spawnCount = 2; // Spawn cap = 2
        vector<pair<int, int>> viablePositions;
        while (spawnCount > 0 && relativeAdjacentPositions.size() > 0)
        {
            pair<int, int> relativeAdjacentPosition = relativeAdjacentPositions.back();
            relativeAdjacentPositions.pop_back();

            int newX = x + relativeAdjacentPosition.first;
            int newY = y + relativeAdjacentPosition.second;
            if (newX >= 0 && newX < world.getWidth() && newY >= 0 && newY < world.getHeight() && world.isEmpty(newX, newY))
            {
                viablePositions.push_back(relativeAdjacentPosition);
                spawnCount--;
            }
        }

        for (pair<int, int> position : viablePositions)
        {
            world.spawnAt<DoodleBug>(position.first + x, position.second + y);
        }

        breedTime = 10;
    }
}

NewPosCandidate DoodleBug::getNewPositionCandidate(int direction)
{
    static const array<pair<int, int>, 8> relativeAdjacentPositions = {
        {{-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}}};
    int relX = relativeAdjacentPositions.at(direction).first;
    int relY = relativeAdjacentPositions.at(direction).second;

    // Bounce off until the doodlebug is in a valid position, each axis is doubled
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

int DoodleBug::getStarvation()
{
    return starvation;
}
