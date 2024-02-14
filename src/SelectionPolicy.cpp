#include "SelectionPolicy.h"

#include <vector>

using std::vector;

Party* MandatesSelectionPolicy::select(Graph& graph, vector<int>& neighbors, int partyId)
{
    Party* maxMandatesParty;
    int maxMandatesNum = 0;
    for(int party : neighbors)
    {
        Party& currParty=graph.getParty(party);
        int currMandates=currParty.getMandates();
        if(currMandates==maxMandatesNum)
        {
            if(currParty.getId()<maxMandatesParty->getId())
            {
                maxMandatesParty=&currParty;
            }
        }
        else if(currMandates>maxMandatesNum)
        {
            maxMandatesNum=currMandates;
            maxMandatesParty=&currParty;
        }
    }
    return maxMandatesParty;
}

Party* EdgeWeightSelectionPolicy::select(Graph& graph, vector<int>& neighbors, int partyId)
{
    int maxEdgeParty = neighbors.at(0);
    int maxEdge = graph.getEdgeWeight(partyId, maxEdgeParty);
    for(int party : neighbors)
    {
        int currEdge=graph.getEdgeWeight(partyId, party);
        if(currEdge==maxEdge)
        {
            if(party<maxEdgeParty)
            {
                maxEdgeParty=party;
            }
        }
        else if(currEdge>maxEdge)
        {
            maxEdge=currEdge;
            maxEdgeParty=party;
        }
    }
    return &(graph.getParty(maxEdgeParty));
}

SelectionPolicy* MandatesSelectionPolicy::clone()
{
    return new MandatesSelectionPolicy();
}

SelectionPolicy* EdgeWeightSelectionPolicy::clone()
{
    return new EdgeWeightSelectionPolicy();
}