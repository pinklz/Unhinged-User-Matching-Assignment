
#ifndef PersonProfile_hpp
#define PersonProfile_hpp

#include <string>
#include <vector>
#include <unordered_set>
#include "provided.h"
#include "RadixTree.h"

class PersonProfile{
public:
    PersonProfile(std::string name, std::string email) : m_name(name), m_email(email), numPairs(0){};
        //contructs personProfile object, specifying name and email
    
    std::string GetName() const {return m_name;};
    std::string GetEmail() const {return m_email;};
    
    void AddAttValPair (const AttValPair& attval);

    
    
    int GetNumAttValPairs() const;

    
    bool GetAttVal (int attribute_num, AttValPair& attval) const;

    
    
private:
    std::string m_name;
    std::string m_email;
    int numPairs;
    RadixTree<std::unordered_set<std::string>> ats;
    std::vector<AttValPair> vecPairs;
};












#endif /* PersonProfile_hpp */
