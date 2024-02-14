#pragma once

#include "Party.h"
#include "Graph.h"

class SelectionPolicy 
{
public:
    virtual Party* select(Graph& graph, vector<int>& neighbors, int partyId)=0;
    virtual SelectionPolicy* clone()=0;
    virtual ~SelectionPolicy()=default;
};


class MandatesSelectionPolicy: public SelectionPolicy
{
public:
    virtual Party* select(Graph& graph, vector<int>& neighbors, int partyId);
    virtual SelectionPolicy* clone();
};

class EdgeWeightSelectionPolicy: public SelectionPolicy
{
public:
    virtual Party* select(Graph& graph, vector<int>& neighbors, int partyId);
    virtual SelectionPolicy* clone();
};