#include "workerant.hpp"

#include "world.hpp"

using namespace std;

WorkerAnt::WorkerAnt(World &world, int x, int y) : Ant(world, x, y)
{
}

char WorkerAnt::charRepresentation()
{
    return 'w';
}

void WorkerAnt::step()
{
    NewPosCandidate newPosition = getNewPositionCandidate();
    bool mayMove =
        world.isEmpty(newPosition.getX(), newPosition.getY()) ||
        (x == newPosition.getX() && y == newPosition.getY() && newPosition.getBounced());
    if (mayMove)
    {
        world.moveEntity(x, y, newPosition.getX(), newPosition.getY());
        starvation = 5;
    }
    else
    {
        starvation--;
    }

    if (starvation == 0)
    {
        world.removeEntity(x, y);
    }
}

AntType WorkerAnt::getAntType()
{
    return AntType::WORKER;
}
