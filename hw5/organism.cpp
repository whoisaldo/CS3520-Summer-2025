#include "organism.hpp"

using namespace std;

Organism::Organism(World &world, int x, int y) : world(world), x(x), y(y)
{
}

void Organism::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}
