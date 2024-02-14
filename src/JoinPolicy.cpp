#include "JoinPolicy.h"

#include <vector>

using std::vector;

Coalition& MandatesJoinPolicy::join(Simulation& sim, vector<int>& offers)
{
    Coalition* maxMandatesCoalition;
    int maxMandatesNum = 0;
    for(int coalition : offers)
    {
        Coalition& currCoalition=sim.getCoalition(coalition);
        int currMandates=currCoalition.getSize();
        if(currMandates>maxMandatesNum)
        {
            maxMandatesNum=currMandates;
            maxMandatesCoalition=&currCoalition;
        }
    }
    return *maxMandatesCoalition;
}

Coalition& LastOfferJoinPolicy::join(Simulation& sim, vector<int>& offers)
{
    return sim.getCoalition(offers.back());
}

JoinPolicy* MandatesJoinPolicy::clone()
{
    return new MandatesJoinPolicy();
}

JoinPolicy* LastOfferJoinPolicy::clone()
{
    return new LastOfferJoinPolicy();
}