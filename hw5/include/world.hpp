#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <memory>
#include <random>

#include "organism.hpp"
#include "worldstatus.hpp"

class World
{
private:
    std::mt19937 &gen;

    int width;
    int height;
    std::vector<std::shared_ptr<Organism>> entities;

    std::shared_ptr<Organism> &at(int x, int y);

public:
    World(int width, int height, std::mt19937 &gen);

    int getWidth();
    int getHeight();
    std::mt19937 &getGen();

    void addEntity(int x, int y, std::shared_ptr<Organism> organism);
    void moveEntity(int x, int y, int newX, int newY);
    void removeEntity(int x, int y);
    std::shared_ptr<Organism> getEntity(int x, int y);
    bool isEmpty(int x, int y);
    WorldStatus getStatus();
    void printWorld();
    void step();

    // Templated functions cannot be put in the cpp file.

    template <typename T = Organism>
    void spawnAtRandomPosition()
    {
        static_assert(std::is_base_of<Organism, T>::value, "T must be a subclass of Organism");
        while (true)
        {
            std::uniform_int_distribution<int> distributionX(0, getWidth() - 1);
            std::uniform_int_distribution<int> distributionY(0, getHeight() - 1);
            int randomX = distributionX(gen);
            int randomY = distributionY(gen);
            if (isEmpty(randomX, randomY))
            {
                addEntity(randomX, randomY, std::make_shared<T>(*this, randomX, randomY));
                break;
            }
        }
    }

    template <typename T = Organism>
    void spawnAt(int x, int y)
    {
        static_assert(std::is_base_of<Organism, T>::value, "T must be a subclass of Organism");
        if (isEmpty(x, y))
        {
            addEntity(x, y, std::make_shared<T>(*this, x, y));
        }
    }
};

#endif
