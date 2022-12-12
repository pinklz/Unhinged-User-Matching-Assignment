
#include "PersonProfile.h"
#include <set>
#include <map>

using namespace std;


void PersonProfile::AddAttValPair (const AttValPair& attval)
{

    unordered_set<std::string>* val = ats.search(attval.attribute);
    if (val == nullptr)
    {
        unordered_set<std::string> s;
        
        //if there is no pair with same attribute, add new pair
        s.insert(attval.value);
        numPairs++;
        vecPairs.push_back(attval);
        ats.insert(attval.attribute, s);
        
    }
    else if (val->count(attval.value) == 0)
    {
        //otherwise, the attribute is already mapped in, need to add new value to set of values with that attribute
        numPairs++;
        vecPairs.push_back(attval);
        ats.search(attval.attribute)->insert(attval.value);
    }
    
    
}

int PersonProfile::GetNumAttValPairs() const
{
    return numPairs;
}

bool PersonProfile::GetAttVal (int attribute_num, AttValPair& attval) const
{

    if (attribute_num>GetNumAttValPairs() || attribute_num<0)
        return false;
    
    
    attval = vecPairs[attribute_num];
    return true;
}

