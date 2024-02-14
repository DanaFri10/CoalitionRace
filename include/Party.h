#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

class JoinPolicy;
class Simulation;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); //constructor
    virtual ~Party(); //destructor
    Party(const Party& other); //copy constructor
    Party(Party&& other); //move constructor
    Party& operator=(const Party& other); //assignment operator
    Party& operator=(Party&& other); //move assignment operator

    int getId() const;
    const string &getName() const;
    int getMandates() const;
    JoinPolicy* getJoinPolicy() const;
    State getState() const;
    int getTimer() const;
    vector<int> getOffers() const;
    bool offerRecieved(int coalitionId);
    void recieveOffer(int coalitionId);
    const string toString() const;
    
    void setState(State state);
    void step(Simulation &s);
    

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int mTimer;
    vector<int> mOffers;

    vector<int> copyOffers(vector<int> other);
};
