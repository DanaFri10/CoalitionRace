#pragma once

#include <vector>
#include "Graph.h"

class SelectionPolicy;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy); //constructor
    Agent(int agentId, int partyId, int coalitionId, SelectionPolicy *selectionPolicy); //constructor
    virtual ~Agent(); //destructor
    Agent(const Agent& other); //copy constructor
    Agent(Agent&& other); //move constructor
    Agent& operator=(const Agent& other); //assignment operator
    Agent& operator=(Agent&& other); //move assignment operator

    int getId() const;
    int getPartyId() const;
    int getCoalitionId() const;
    SelectionPolicy* getSelectionPolicy() const;
    void step(Simulation &);

private:
    int mAgentId;
    int mPartyId;
    int mCoalitionId;
    SelectionPolicy *mSelectionPolicy;
    bool satisfiesConditions(Graph graph, int partyId);
};
