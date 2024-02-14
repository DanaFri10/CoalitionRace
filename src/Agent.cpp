#include "Agent.h"
#include "SelectionPolicy.h"
#include "Simulation.h"
#include "Graph.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId),mCoalitionId(agentId), mSelectionPolicy(selectionPolicy)
{}

Agent::Agent(int agentId, int partyId, int coalitionId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId),mCoalitionId(coalitionId), mSelectionPolicy(selectionPolicy)
{}

Agent::~Agent()
{
    delete mSelectionPolicy;
}

Agent::Agent(const Agent& other) : mAgentId(other.getId()), mPartyId(other.getPartyId()), mCoalitionId(other.getCoalitionId()), mSelectionPolicy((*(other.getSelectionPolicy())).clone())
{}
    
    
Agent::Agent(Agent&& other): mAgentId(other.getId()), mPartyId(other.getPartyId()), mCoalitionId(other.getCoalitionId()), mSelectionPolicy(other.getSelectionPolicy())
{
    other.mSelectionPolicy=nullptr;
}

Agent& Agent::operator=(const Agent& other)
{
    this->mAgentId=other.getId();
    this->mPartyId=other.getPartyId();
    this->mCoalitionId=other.getCoalitionId();
    delete mSelectionPolicy;
    this->mSelectionPolicy=(*(other.getSelectionPolicy())).clone();
    return (*this);
}

Agent& Agent::operator=(Agent&& other)
{
    this->mAgentId=other.getId();
    this->mPartyId=other.getPartyId();
    this->mCoalitionId=other.getCoalitionId();
    this->mSelectionPolicy=other.getSelectionPolicy();
    other.mSelectionPolicy=nullptr;
    return (*this);
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

int Agent::getCoalitionId() const
{
    return mCoalitionId;
}

SelectionPolicy* Agent::getSelectionPolicy() const
{
    return mSelectionPolicy;
}

void Agent::step(Simulation &sim)
{
    vector<int> neighborsToOffer;
    for(int i=0;i<sim.getGraph().getNumVertices();i++)
    {
        if(satisfiesConditions(sim.getGraph(),i))
        {
            neighborsToOffer.push_back(i);
        }
    }
    if(neighborsToOffer.size()!=0)
    {
        Party* partyToOffer=mSelectionPolicy->select(sim.getGraph(), neighborsToOffer, mPartyId);
        partyToOffer->recieveOffer(mCoalitionId);
    }
}

bool Agent::satisfiesConditions(Graph graph, int partyId)
{
    if(graph.getEdgeWeight(mPartyId, partyId) <= 0)
    {
        return false;
    }
    if(graph.getParty(partyId).getState() == Joined)
    {
        return false;
    }
    if(graph.getParty(partyId).offerRecieved(mCoalitionId))
    {
        return false;
    }
    return true;
}