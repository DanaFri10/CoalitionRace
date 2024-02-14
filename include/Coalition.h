#pragma once

#include "Party.h"
#include <vector>

using std::vector;

class Coalition
{
public:
    Coalition(int coalitionId, vector<Party> parties);
    const int getId() const;
    const vector<Party>& getParties() const;
    const int getSize() const;
    void joinCoalition(Party& p);
    void print();

private:
    int mId;
    vector<Party> mParties;
    int mSize;
};