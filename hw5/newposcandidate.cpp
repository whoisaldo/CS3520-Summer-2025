#include "newposcandidate.hpp"

using namespace std;

NewPosCandidate::NewPosCandidate(int x, int y, bool bounced) : x(x), y(y), bounced(bounced)
{
}

int NewPosCandidate::getX()
{
    return x;
}

int NewPosCandidate::getY()
{
    return y;
}

bool NewPosCandidate::getBounced()
{
    return bounced;
}