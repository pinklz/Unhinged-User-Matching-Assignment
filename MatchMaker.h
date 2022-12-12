

#ifndef MatchMaker_hpp
#define MatchMaker_hpp

#include <vector>
#include <string>
#include <map>
#include "provided.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"

class MatchMaker
{
public:
    
    MatchMaker (const MemberDatabase& mdb, const AttributeTranslator& at);

    
    std::vector<EmailCount> IdentifyRankedMatches (std::string email, int threshold) const;
    
private:
    const MemberDatabase& MDB;
    const AttributeTranslator& AT;
};


#endif /* MatchMaker_hpp */
