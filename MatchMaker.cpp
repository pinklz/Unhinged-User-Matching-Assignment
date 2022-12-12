
#include "MatchMaker.h"
#include  "provided.h"
#include <string>
#include <vector>
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
#include <algorithm>

using namespace std;


MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) : MDB(mdb), AT(at)
{ }



bool compare(EmailCount a, EmailCount b)
{
    //used to sort vector of emailCount objects in descending order
    return a.count > b.count;
}

vector<EmailCount> MatchMaker::IdentifyRankedMatches (string email, int threshold) const
{
    
    vector<EmailCount> emailC;
    
    unordered_set<string> matchingAtts;
    unordered_set<string> matchingEmails;

    if (MDB.GetMemberByEmail(email) == nullptr)
        return emailC;
    
    const PersonProfile* user = MDB.GetMemberByEmail(email);
    
    vector<AttValPair> pairsOfUser;
    for (int i = 0; i < user->GetNumAttValPairs(); i++)
    {
        AttValPair currentAV;
        user->GetAttVal(i, currentAV);

        
        //holds all attributes that match with this specific attribute
        vector<AttValPair> matchingAttsVector = AT.FindCompatibleAttValPairs(currentAV);
        
        for (int j = 0; j < matchingAttsVector.size(); j++)
        {
            //inserts into set so no duplicate values
            AttValPair a = matchingAttsVector[j];
            string pair = a.attribute + "," + a.value;
            matchingAtts.insert(pair);
        }
    }
    
    
    //matchingAtts now holds unique set of compatible attributes (in string form)
    std::map<std::string, int> emailCountMap;

    unordered_set<string> :: iterator itr;
    for (itr = matchingAtts.begin(); itr != matchingAtts.end(); itr++)
    {
        string currentAV = *itr;
        int commaIndex = currentAV.find(',');
        
        AttValPair atv;
        atv.attribute = currentAV.substr(0, commaIndex);
        atv.value = currentAV.substr(commaIndex+1, currentAV.length()-commaIndex);
        
        //gets emails of all who have this compatible pair
        vector<string> emails = MDB.FindMatchingMembers(atv);
        
        for (int k = 0; k < emails.size(); k++)
        {
            if (emailCountMap.find(emails[k]) != emailCountMap.end())
            {
                //if there email is already in the map of users with any compatible pairs, increase their count
                emailCountMap.find(emails[k])->second++;
            }
            else
                emailCountMap.insert({emails[k], 1});
                //otherwise, insert this person with a count of one
        }
            
        
    }
    
    //loops through map (which is visited in alphabetical order already)
    for (map<string, int>::iterator p = emailCountMap.begin(); p != emailCountMap.end(); p++)
    {
        EmailCount a((*p).first, (*p).second);
        //add person to vector if their count is over the threshold
        if (a.count < threshold)
            continue;
        emailC.push_back(a);
    }
    
    //sorts the vector in descending order of count, but maintains alphabetical order b/c stable sort
    stable_sort(emailC.begin(), emailC.end(), compare);
    
    
    return emailC;
}
