#include <iostream>
#include "Party.h"
#include "JoinPolicy.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), mTimer(1), mOffers() 
{}

Party::~Party()
{
    delete mJoinPolicy;
}

vector<int> Party::copyOffers(vector<int> other)
{
    vector<int> copyOffers;
    for(int otherOffer:other)
    {
        copyOffers.push_back(otherOffer);
    }
    return copyOffers;
}

Party::Party(const Party& other) : mId(other.getId()), mName(other.getName()), mMandates(other.getMandates()), mJoinPolicy((*(other.getJoinPolicy())).clone()), mState(other.getState()), mTimer(other.getTimer()), mOffers(copyOffers(other.getOffers()))
{}

Party::Party(Party&& other): mId(other.getId()), mName(other.getName()), mMandates(other.getMandates()), mJoinPolicy(other.getJoinPolicy()), mState(other.getState()), mTimer(other.getTimer()), mOffers(other.getOffers())
{
    other.mJoinPolicy=nullptr;
}

Party& Party::operator=(const Party& other)
{
    this->mId=other.getId();
    this->mName=other.getName();
    this->mMandates=other.getMandates();
    delete mJoinPolicy;
    this->mJoinPolicy=(*(other.getJoinPolicy())).clone();
    this->mState=other.getState();
    this->mTimer=other.getTimer();
    
    vector<int> copyOffers;
    for(int otherOffer:other.getOffers())
    {
        copyOffers.push_back(otherOffer);
    }
    this->mOffers=copyOffers;

    return (*this);
}

Party& Party::operator=(Party&& other)
{
    this->mId=other.getId(); 
    this->mName=other.getName();
    this->mMandates=other.getMandates();
    this->mJoinPolicy=other.getJoinPolicy();
    this->mState=other.getState();
    this->mTimer=other.getTimer();
    this->mOffers=other.getOffers();
    
    other.mJoinPolicy=nullptr;

    return (*this);
}

int Party::getId() const
{
    return mId;
}

const string & Party::getName() const
{
    return mName;
}

int Party::getMandates() const
{
    return mMandates;
}

JoinPolicy* Party::getJoinPolicy() const
{
    return mJoinPolicy;
}

State Party::getState() const
{
    return mState;
}

int Party::getTimer() const
{
    return mTimer;
}

vector<int> Party::getOffers() const
{
    return mOffers;
}

void Party::setState(State state)
{
    mState = state;
}

void Party::step(Simulation &s)
{
    if(mState==CollectingOffers)
    {
        if(mTimer>2)
        {
            if(mOffers.size()>0)
            {
                setState(Joined);
                Coalition& coalitionToJoin=mJoinPolicy->join(s, mOffers);
                coalitionToJoin.joinCoalition(*this);
                s.addAgent(coalitionToJoin.getId(), mId);
            }
        }
        else mTimer++;
    }
}

bool Party::offerRecieved(int coalitionId)
{
    for(int offer:mOffers)
    {
        if(offer==coalitionId)
        {
            return true;
        }
    }
    return false;
}

void Party::recieveOffer(int coalitionId)
{
    mOffers.push_back(coalitionId);
    setState(CollectingOffers);
}