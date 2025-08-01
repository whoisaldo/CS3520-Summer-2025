#include <array>
#include <algorithm>
#include <vector>

#include "queenant.hpp"

#include "world.hpp"
#include "workerant.hpp"
#include "queenant.hpp"
#include "maleant.hpp"

using namespace std;

QueenAnt::QueenAnt(World &world, int x, int y) : Ant(world, x, y)
{
    uniform_real_distribution<double> cataglyphisDist(0.0, 1.0);
    cataglyphis = cataglyphisDist(world.getGen()) < 0.1;

    if (cataglyphis)
    {
        matingCooldown = -1;
        bearTime = 25;
        notBredTime = -1;
        return;
    }

    matingCooldown = 25;
    bearTime = -1;
    notBredTime = 60;
}

char QueenAnt::charRepresentation()
{
    return 'Q';
}

void QueenAnt::step()
{
    if (bearTime > 0)
    {
        bearTime--;
        return;
    }

    if (bearTime == 0)
    {
        if (cataglyphis)
        {
            bearTime = 25;
        }
        else
        {
            bearTime = -1;
            matingCooldown = 25;
        }

        vector<pair<int, int>> newInnerPositions = {
            {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}};
        vector<pair<int, int>> newOuterPositions = {
            {{-2, -2}, {-2, -1}, {-2, 0}, {-2, 1}, {-2, 2}, {-1, -2}, {-1, 2}, {0, -2}, {0, 2}, {1, -2}, {1, 2}, {2, -2}, {2, -1}, {2, 0}, {2, 1}, {2, 2}}};

        shuffle(newInnerPositions.begin(), newInnerPositions.end(), world.getGen());
        shuffle(newOuterPositions.begin(), newOuterPositions.end(), world.getGen());

        // The inner positions have higher priority than the outer positions
        vector<pair<int, int>> newPositionsWithPriority = {};
        newPositionsWithPriority.insert(newPositionsWithPriority.end(), newInnerPositions.begin(), newInnerPositions.end());
        newPositionsWithPriority.insert(newPositionsWithPriority.end(), newOuterPositions.begin(), newOuterPositions.end());

        int spawnCount = 10; // Spawn cap = 10
        vector<pair<int, int>> viablePositions;
        while (spawnCount > 0 && newPositionsWithPriority.size() > 0)
        {
            pair<int, int> position = newPositionsWithPriority.back();
            newPositionsWithPriority.pop_back();

            int newX = x + position.first;
            int newY = y + position.second;
            if (newX >= 0 && newX < world.getWidth() && newY >= 0 && newY < world.getHeight() && world.isEmpty(newX, newY))
            {
                viablePositions.push_back(position);
                spawnCount--;
            }
        }

        uniform_real_distribution<double> femaleDist(0.6, 0.8);
        uniform_real_distribution<double> queenDist(0.00, 0.05);
        double femaleRatio = femaleDist(world.getGen());
        double queenChance = queenDist(world.getGen());

        for (pair<int, int> position : viablePositions)
        {
            uniform_real_distribution<double> typeDist(0.0, 1.0);
            double random = typeDist(world.getGen());

            if (random < queenChance)
            {
                world.spawnAt<QueenAnt>(position.first + x, position.second + y);
            }
            else if (random < femaleRatio)
            {
                world.spawnAt<WorkerAnt>(position.first + x, position.second + y);
            }
            else
            {
                world.spawnAt<MaleAnt>(position.first + x, position.second + y);
            }
        }

        return;
    }

    if (matingCooldown > 0)
    {
        matingCooldown--;
    }

    if (notBredTime > 0)
    {
        notBredTime--;
    }

    if (notBredTime == 0)
    {
        world.removeEntity(x, y);
    }

    static const array<pair<int, int>, 8> surroundings = {
        {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}};
    bool hasMaleAround = false;
    for (pair<int, int> surrounding : surroundings)
    {
        int newX = x + surrounding.first;
        int newY = y + surrounding.second;
        if (newX < 0 || newX >= world.getWidth() || newY < 0 || newY >= world.getHeight())
        {
            continue;
        }

        shared_ptr<Organism> organism = world.getEntity(newX, newY);
        if (organism && organism->charRepresentation() == 'o')
        {
            hasMaleAround = true;
            break;
        }
    }

    if (matingCooldown == 0 && bearTime == -1 && hasMaleAround)
    {
        matingCooldown = 50;
        bearTime = 25;
        notBredTime = 60 + 25;
        return;
    }

    NewPosCandidate newPosition = getNewPositionCandidate();
    bool mayMove =
        world.isEmpty(newPosition.getX(), newPosition.getY()) ||
        (x == newPosition.getX() && y == newPosition.getY() && newPosition.getBounced());
    if (mayMove)
    {
        world.moveEntity(x, y, newPosition.getX(), newPosition.getY());
    }
}

AntType QueenAnt::getAntType()
{
    return AntType::QUEEN;
}

int QueenAnt::getNotBredTime()
{
    return notBredTime;
}

bool QueenAnt::isCataglyphis()
{
    return cataglyphis;
}
