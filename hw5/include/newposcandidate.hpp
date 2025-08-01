#ifndef NEWPOSCANDIDATE_HPP
#define NEWPOSCANDIDATE_HPP

#include <utility>

class NewPosCandidate
{
private:
    int x;
    int y;
    bool bounced;

public:
    NewPosCandidate(int x, int y, bool bounced);

    int getX();
    int getY();
    bool getBounced();
};

#endif