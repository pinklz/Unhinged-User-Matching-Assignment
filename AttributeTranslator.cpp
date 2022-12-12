
#include "AttributeTranslator.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;


bool AttributeTranslator::Load (string filename)
{
    
    string transfile(filename);
    ifstream input_file(transfile);
    
    if (input_file.is_open())
    {
        string line;
        
        while (getline(input_file, line))
        {
            
            stringstream ss(line);
            
            //gets source attribute and following compatible attribute
            string source;
            string sp1;
            string sp2;
            AttValPair match;
            
            
            getline(ss, sp1, ',');
            getline(ss, sp2, ',');
            source = sp1+ ',' + sp2;
            string sourceCopy = source;
            

            getline(ss, match.attribute, ',');
            getline(ss, match.value, ',');

            
            
            
            //if the source attribute isn't already in the radix tree, add it + it's compatible pair
            if (compAtts.search(source) == nullptr)
            {
                vector<AttValPair> matches;
                matches.push_back(match);
                
                compAtts.insert(source, matches);
            }
            else
            {
                //otherwise, add new compatible pair to vector of this pair's compatible attributes
                compAtts.search(source)->push_back(match);
            }

        }
        
        return true;
    }
    //if the file didn't open, return false
    return false;
}

vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{

    vector<AttValPair> matches;
    if (compAtts.search(source.attribute+","+source.value) == nullptr)
        return matches;
    else
    {
        return *compAtts.search(source.attribute+","+source.value);
    }

}

