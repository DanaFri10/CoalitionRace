#pragma once

#include <vector>
#include "Simulation.h"

using std::vector;

class JoinPolicy 
{
public:
    virtual Coalition& join(Simulation& sim, vector<int>& offers)=0;
    virtual JoinPolicy* clone()=0;
    virtual ~JoinPolicy()=default;
};

class MandatesJoinPolicy : public JoinPolicy 
{
    public:
        virtual Coalition& join(Simulation& sim, vector<int>& offers);
        virtual JoinPolicy* clone();
};

class LastOfferJoinPolicy : public JoinPolicy 
{
    public:
        virtual Coalition& join(Simulation& sim, vector<int>& offers);
        virtual JoinPolicy* clone();
};