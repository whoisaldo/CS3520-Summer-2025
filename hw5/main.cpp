#include <iostream>
#include <optional>
#include <vector>
#include <memory>
#include <random>
#include <array>
#include <thread>
#include <chrono>
#include <climits>
#include <iomanip>

#include "world.hpp"
#include "organism.hpp"
#include "ant.hpp"
#include "queenant.hpp"
#include "maleant.hpp"
#include "workerant.hpp"
#include "doodlebug.hpp"

using namespace std;

int readInt(string prompt, int defaultValue)
{
    while (true)
    {
        cout << prompt;
        string line;
        getline(cin, line);

        if (line.empty())
        {
            return defaultValue;
        }

        try
        {
            int num = stoi(line);

            if (num > 0)
            {
                return num;
            }

            cout << "Please enter a number greater than 0." << endl;
        }
        catch (const invalid_argument &e)
        {
            cout << "Please enter a valid number." << endl;
        }
        catch (const out_of_range &e)
        {
            cout << "Please enter a number between " << INT_MIN << " and " << INT_MAX << "." << endl;
        }
    }
}

int main()
{
    random_device rd;
    mt19937 gen(rd());
    World world(100, 100, gen);

    int doodlebugCount = readInt("Enter the number of doodlebugs [default: 10]: ", 10);
    int antCount = readInt("Enter the number of ants [default: 50]: ", 50);
    int queenAntCount = readInt("Enter the number of queen ants [default: 3]: ", 3);

    for (int i = 0; i < doodlebugCount; i++)
    {
        world.spawnAtRandomPosition<DoodleBug>();
    }
    for (int i = 0; i < antCount; i++)
    {
        int isMale = rand() % 2;
        if (isMale)
        {
            world.spawnAtRandomPosition<MaleAnt>();
        }
        else
        {
            world.spawnAtRandomPosition<WorkerAnt>();
        }
    }
    for (int i = 0; i < queenAntCount; i++)
    {
        world.spawnAtRandomPosition<QueenAnt>();
    }

    while (true)
    {
        world.printWorld();

        WorldStatus status = world.getStatus();
        int antCount = status.getQueenAntCount() + status.getMaleAntCount() + status.getWorkerAntCount();
        if (status.getDoodlebugCount() == 0)
        {
            cout << "Doodlebugs are extinct!" << endl;
            break;
        }
        else if (antCount == 0)
        {
            cout << "Ants are extinct!" << endl;
            break;
        }

        cout
            << "Doodlebugs: " << setw(3) << status.getDoodlebugCount()
            << ", All queen ants: " << setw(3) << status.getQueenAntCount()
            << ", Male ants: " << setw(3) << status.getMaleAntCount()
            << ", Worker ants: " << setw(3) << status.getWorkerAntCount()
            << ", Cataglyphis queen ants: " << setw(3) << status.getQueenAntCataglyphisCount()
            << endl;
        cout
            << "Doodlebugs starvation average: " << setw(5) << setprecision(2) << fixed << status.getDoddlebugStarvationAverage()
            << ", Ant starvation average: " << setw(5) << setprecision(2) << fixed << status.getAntStarvationAverage()
            << ", Queen ant not bred time average: " << setw(5) << setprecision(2) << fixed << status.getQueenAntNotBredTimeAverage()
            << endl;

        int fps = 10;
        this_thread::sleep_for(chrono::milliseconds(1000 / fps));
        world.step();
    }

    return 0;
}
