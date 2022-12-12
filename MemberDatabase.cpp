
#include "MemberDatabase.h"
#include <string>
#include <vector>
#include "PersonProfile.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>
using namespace std;



bool MemberDatabase:: LoadDatabase (string filename)
{
    
    ifstream inFile(filename);
    
    if (inFile.is_open())
    {
        
        string name;
        while (getline(inFile, name))
        {
            //if it is the empty string, means new person follows
            if(name == "" || iscntrl(name[0]))
                continue;
            string email;
            string numString;
            
            getline(inFile, email);
            
            //creates new person from email and string
            PersonProfile* person = new PersonProfile(name, email);
            
            getline(inFile, numString);
            int numAtts = std::stoi(numString);
                        
            
            int index = 0;
            while (index < numAtts)
            {
                //for each attribute, add to person's list of attributes
                string atp;
                getline(inFile, atp);
                int comma = atp.find(',');
                string att = atp.substr(0, comma);
                string val = atp.substr(comma+1, atp.length());
            

                AttValPair atval(att, val);
                person->AddAttValPair(atval);

                //also for each attribute, add this person's email to the list of people with this attribute
                vector<string>* atvals = emailPairs.search(att+","+val);
                if (atvals == nullptr)
                {
                    vector<string> emailsWithAt;

                    emailsWithAt.push_back(email);
                    emailPairs.insert(att+","+val, emailsWithAt);


                }
                else
                {
                    emailPairs.search(att+","+val) -> push_back(email);
                }
                
                index++;
            }
            
            vector<PersonProfile> newPerson;
            
            newPerson.push_back(*person);
            profiles.insert(email, *person);
            
            
            getline(inFile, name);
        }
        
        

        return true;
        
    }
            
 

    return false;
}


vector<string> MemberDatabase::FindMatchingMembers (const AttValPair& input) const
{

    vector<string> s;
    
    string pair = input.attribute + "," + input.value;
    
    if (emailPairs.search(pair) == nullptr)
        return s;
    else
    {
        return *emailPairs.search(pair);
    }

}


const PersonProfile* MemberDatabase::GetMemberByEmail (string email) const
{
    return profiles.search(email);
    
}
