
#ifndef AttributeTranslator_hpp
#define AttributeTranslator_hpp

#include <string>
#include <vector>
#include "provided.h"
#include "RadixTree.h"

class AttributeTranslator
{
public:
    AttributeTranslator() {};
    
    bool Load (std::string filename);
    
    std::vector<AttValPair> FindCompatibleAttValPairs (const AttValPair& source) const;
private:
    std::vector<AttValPair> pairs;
    RadixTree<std::vector<AttValPair>> compAtts;
    
};


#endif /* AttributeTranslator_hpp */
