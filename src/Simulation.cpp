#include <iostream>
#include "Simulation.h"
#include "Coalition.h"
#include "SelectionPolicy.h"

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), mCoalitions(createCoalitions())
{}

vector<Coalition> Simulation::createCoalitions()
{
    vector<Coalition> coalitions;
    for(Agent agent:mAgents)
    {
        vector<Party> coalParties;
        coalParties.push_back(getParty(agent.getPartyId()));
        Coalition coalition(agent.getId(), coalParties);
        mCoalitions.push_back(coalition);
    }
    return coalitions;
}

void Simulation::step()
{
    for(int i=0;i<mGraph.getNumVertices();i++)
    {
        mGraph.getParty(i).step(*this);
    }
    for(Agent a:mAgents)
    {
        a.step(*this);
    }
}

bool Simulation::shouldTerminate() const
{
    for(Coalition c:mCoalitions)
    {
        if(c.getSize()>=61)
        {
            return true;
        }
    }

    for(int i=0;i<mGraph.getNumVertices();i++)
    {
        if(getParty(i).getState()!=Joined)
        {
            return false;
        }
    }
    return true;
}


const Graph &Simulation::getGraph() const
{
    return mGraph;
}

Graph &Simulation::getGraph()
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    vector<vector<int>> partiesByCoalitions;
    for(Coalition c:mCoalitions)
    {
        vector<int> coalParties;
        for(Party p:c.getParties())
        {
            coalParties.push_back(p.getId());
        }
        partiesByCoalitions.push_back(coalParties);
    }
    return partiesByCoalitions;
}

Coalition& Simulation::getCoalition(int coalitionId)
{
    /*
    for(Coalition c:mCoalitions)
    {
        if(c.getId()==coalitionId)
        {
            return c;
        }
    }
    return mCoalitions.at(0); 
    */
   return mCoalitions.at(coalitionId);
}

void Simulation::addAgent(int coalitionId, int partyId)
{
    Agent cloneAgent(mAgents.size(), partyId, coalitionId, (mAgents.at(coalitionId).getSelectionPolicy())->clone());
    mAgents.push_back(cloneAgent);
}