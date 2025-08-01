#include "maleant.hpp"
#include "world.hpp"
#include "newposcandidate.hpp"

using namespace std;

MaleAnt::MaleAnt(World &world, int x, int y) : Ant(world, x, y)
{
}

char MaleAnt::charRepresentation()
{
    return 'o';
}

void MaleAnt::step()
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

AntType MaleAnt::getAntType()
{
    return AntType::MALE;
}
