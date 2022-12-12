# Unhinged-User-Matching-Assignment
Course Assignment for CS32 Winter 2022: Unhinged
This project was completed on March 9, 2022.

The project was to implement the PersonProfile, MemberDatabase, AttributeTranslator, MatchMaker, and RadixTree
classes for a program that supports up to 100K members. Each member has attribute-value pairs and is matched with 
other users based on compatible attributes. Lists of users and compatible attributes were provided with the 
assignment, in addition to a 'provided.h' file that contained several struct definitions. The PersonProfile, 
MemberDatabase, and AttributeTranslator classes had to add and retrieve pairs in better than O(N) and could not 
use any STL map variants. The MatchMaker class was to run as efficiently as possible and was expected to be significantly 
faster than O(N). The RadixTree template was used to fulfill most Big O requirements.
