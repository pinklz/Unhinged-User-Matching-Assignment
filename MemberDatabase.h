
#ifndef MemberDatabase_hpp
#define MemberDatabase_hpp

#include <string>
#include <vector>
#include "provided.h"
#include "PersonProfile.h"
#include "RadixTree.h"

class MemberDatabase
{
public:
    MemberDatabase() {};
    
    bool LoadDatabase (std::string filename);
    
    std::vector <std::string> FindMatchingMembers (const AttValPair& input) const;
    
    const PersonProfile* GetMemberByEmail(std::string email) const;
    
    
private:
    RadixTree<PersonProfile> profiles;    //maps emails to member profiles
    RadixTree<std::vector<std::string>> emailPairs;
    
    
};


#endif /* MemberDatabase_hpp */
