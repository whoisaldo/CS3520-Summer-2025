#include <iostream>
#include <string>

#include "world.hpp"
#include "worldstatus.hpp"
#include "ant.hpp"
#include "queenant.hpp"
#include "doodlebug.hpp"

using namespace std;

shared_ptr<Organism> &World::at(int x, int y)
{
    return entities.at(y * width + x);
}

World::World(int width, int height, mt19937 &gen) : width(width), height(height), gen(gen)
{
    entities.resize(width * height, nullptr);
}

int World::getWidth()
{
    return width;
}

int World::getHeight()
{
    return height;
}

mt19937 &World::getGen()
{
    return gen;
}

void World::addEntity(int x, int y, shared_ptr<Organism> organism)
{
    this->at(x, y) = organism;
    organism->setPosition(x, y);
}

void World::moveEntity(int x, int y, int newX, int newY)
{
    // The organism may bounce to the same position
    if (this->at(newX, newY) == this->at(x, y))
    {
        return;
    }

    shared_ptr<Organism> organism = this->at(x, y);
    this->at(newX, newY) = organism;
    organism->setPosition(newX, newY);
    this->at(x, y) = nullptr;
}

void World::removeEntity(int x, int y)
{
    this->at(x, y) = nullptr;
}

shared_ptr<Organism> World::getEntity(int x, int y)
{
    return this->at(x, y);
}

bool World::isEmpty(int x, int y)
{
    return this->at(x, y) == nullptr;
}

WorldStatus World::getStatus()
{
    int doodlebugCount = 0;
    int queenAntCount = 0;
    int maleAntCount = 0;
    int workerAntCount = 0;
    int queenAntCataglyphisCount = 0;
    double doddlebugStarvationAverage = 0;
    double antStarvationAverage = 0;
    double queenAntNotBredTimeAverage = 0;
    for (shared_ptr<Organism> entity : entities)
    {
        if (entity && entity->getType() == OrganismType::DOODLEBUG)
        {
            doodlebugCount++;
            doddlebugStarvationAverage += dynamic_cast<DoodleBug *>(entity.get())->getStarvation();
        }
        else if (entity && entity->getType() == OrganismType::ANT)
        {
            AntType antType = dynamic_cast<Ant *>(entity.get())->getAntType();
            if (antType == AntType::QUEEN)
            {
                queenAntCount++;
                QueenAnt *queenAnt = dynamic_cast<QueenAnt *>(entity.get());
                if (queenAnt->isCataglyphis())
                {
                    queenAntCataglyphisCount++;
                }
                else
                {
                    queenAntNotBredTimeAverage += queenAnt->getNotBredTime();
                }
            }
            else if (antType == AntType::MALE)
            {
                maleAntCount++;
                antStarvationAverage += dynamic_cast<Ant *>(entity.get())->getStarvation();
            }
            else if (antType == AntType::WORKER)
            {
                workerAntCount++;
                antStarvationAverage += dynamic_cast<Ant *>(entity.get())->getStarvation();
            }
        }
    }
    if (doodlebugCount > 0)
    {
        doddlebugStarvationAverage /= doodlebugCount;
    }
    if (queenAntCount > 0)
    {
        queenAntNotBredTimeAverage /= queenAntCount - queenAntCataglyphisCount;
    }
    if (maleAntCount + workerAntCount > 0)
    {
        antStarvationAverage /= (maleAntCount + workerAntCount);
    }
    return WorldStatus(
        doodlebugCount,
        queenAntCount,
        queenAntCataglyphisCount,
        maleAntCount,
        workerAntCount,
        doddlebugStarvationAverage,
        antStarvationAverage,
        queenAntNotBredTimeAverage);
}

void World::printWorld()
{
    string worldBuffer;
    worldBuffer += "/";
    for (int i = 0; i < width; i++)
    {
        worldBuffer += "-";
    }
    worldBuffer += "\\";
    worldBuffer += '\n';
    for (int i = 0; i < height; i++)
    {
        worldBuffer += "|";
        for (int j = 0; j < width; j++)
        {
            shared_ptr<Organism> entity = this->at(j, i);
            worldBuffer += entity ? entity->charRepresentation() : '.';
        }
        worldBuffer += "|";
        worldBuffer += '\n';
    }
    worldBuffer += "\\";
    for (int i = 0; i < width; i++)
    {
        worldBuffer += "-";
    }
    worldBuffer += "/";
    worldBuffer += '\n';
    cout << worldBuffer << endl;
}

void World::step()
{
    vector<shared_ptr<Organism>> doodlebugs;
    vector<shared_ptr<Organism>> ants;
    for (shared_ptr<Organism> entity : entities)
    {
        if (entity)
        {
            if (entity->getType() == OrganismType::DOODLEBUG)
            {
                doodlebugs.push_back(entity);
            }
            else if (entity->getType() == OrganismType::ANT)
            {
                ants.push_back(entity);
            }
        }
    }
    for (shared_ptr<Organism> entity : doodlebugs)
    {
        entity->step();
    }
    for (shared_ptr<Organism> entity : ants)
    {
        entity->step();
    }
}
