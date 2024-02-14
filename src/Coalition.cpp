#include "Coalition.h"
#include "Party.h"

#include <vector>
#include <iostream>
using std::vector;

Coalition::Coalition(int coalitionId, vector<Party> parties) : mId(coalitionId), mParties(parties), mSize()
{
    for(Party p:mParties)
    {
        mSize+=p.getMandates();
    }
}

const int Coalition::getId() const
{
    return mId;
}

const vector<Party>& Coalition::getParties() const
{
    return mParties;
}

const int Coalition::getSize() const
{
    return mSize;
}

void Coalition::joinCoalition(Party& p)
{
    mParties.push_back(p);
    mSize+=p.getMandates();
}

void Coalition::print()
{
    std::cout<<"<";
    for(Party p:mParties)
    {
        std::cout << std::to_string(p.getId());
    }
    std::cout<<">";
}