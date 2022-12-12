

#ifndef RadixTree_h
#define RadixTree_h

#include <string>
#include <unordered_set>
#include <vector>

#include <iostream>



template <typename ValueType>

class RadixTree
{
public:
    RadixTree();
    ~RadixTree();
    
    void insert (std::string key, const ValueType& value);
    ValueType* search (std::string key) const;
    
private:

    struct Node;
    struct Edge
    {
        Edge() {targetNode = new Node();};
        Node* targetNode;
        std::string label;

    };

    struct Node
    {
        Node()
        {
            //initializes each edge to null when a node is created
            for (int i = 0; i < 128; i++)
            {
                edges[i] = nullptr;
            }
            isLeaf = true;
            vvalue = nullptr;
        };

        Edge* edges[128];
        bool isLeaf;
        ValueType* vvalue;
    };

    Node* root;
    
    void FreeTree(Node* cur);
    
};

template <typename ValueType>
RadixTree<ValueType>::RadixTree()
{
    
    root = new Node();
    
}

template <typename ValueType>
void RadixTree<ValueType>::FreeTree(Node* cur)
{
    if (cur == nullptr)
        return;

    for (int i = 0; i < 128; i++)
    {
        if (cur->edges[i] != nullptr)
        {
            FreeTree(cur->edges[i]->targetNode);
        }
        delete cur->edges[i];

    }
    delete cur->vvalue;
    delete cur;
    
    
}

template <typename ValueType>
RadixTree<ValueType>::~RadixTree()
{
    FreeTree(root);

}

template <typename ValueType>
void RadixTree<ValueType>::insert (std::string key, const ValueType& value)
{



        //similar to search, but changing map when find mismatch instead of exiting
        Node* traverseNode = root;
        int charFound = 0;

        while (traverseNode != nullptr && charFound < key.length() /* && !traverseNode->isLeaf*/)
        {
            Edge* nextEdge = nullptr;
            std::string restOfKey = key.substr(charFound, key.length()-charFound);

            //next char in key that hasn't been found in the map yet
            int nextChar = key.at(charFound);

            if (traverseNode->edges[nextChar] == nullptr)
            {
                //no edge yet in spot need
                traverseNode->edges[nextChar] = new Edge();
                traverseNode->edges[nextChar]->label = restOfKey;
                traverseNode->isLeaf = false;
                
                traverseNode->edges[nextChar]->targetNode->vvalue = new ValueType(value);


                charFound = key.length();
                traverseNode = nullptr;

            }
            else
            {
                //there is an edge that starts with the correct next character

                Edge currentEdge = *traverseNode->edges[nextChar];
                int edgeLen = currentEdge.label.length();

                std::string keyCompareChars = key.substr(charFound, edgeLen);
                /*if the edge is a path down on the tree that will continue the key, continue with the loop and increase charFound by number of
                 characters that have been checked in key
                 */
                if (keyCompareChars == currentEdge.label)
                {
                    nextEdge = traverseNode->edges[nextChar];
                    traverseNode = nextEdge->targetNode;
                    charFound += nextEdge->label.length();

                    continue;
                }
                else
                {
                    //there is a mismatch, need to split current edge or add to end of it

                    int c = 0;

                    std::string labl = currentEdge.label;

                    while (c < restOfKey.length() && c < edgeLen && (restOfKey.at(c) == labl.at(c)))
                    {
                        //while their characters are the same and neither string has ended
                        c++;
                    }


                    //c should now hold index-1 of where the strings become different
                    if ( c+1 > restOfKey.length())
                    {
                        //label len > key len
                        std::string restOfLabel = labl.substr(c, edgeLen -  restOfKey.length());
                        Node* infoBeingMoved = traverseNode->edges[nextChar]->targetNode;

                        //shifting info down into new nodes

                        //sets new label
                        traverseNode->edges[nextChar]->label = restOfKey;
                        //new node for new label
                        Node* ng = new Node();
                        traverseNode->edges[nextChar]->targetNode = ng;
                        traverseNode->isLeaf = false;
                        
                        
                        ng->vvalue = new ValueType(value);

                        //adds rest of previous label to correct position in new node

                        int labelFirstCh = restOfLabel.at(0);
                        ng->edges[labelFirstCh] = new Edge();
                        ng->edges[labelFirstCh]->label = restOfLabel;
                        ng->edges[labelFirstCh]->targetNode = infoBeingMoved;


                        //key has fully been added
                        charFound = key.length();
                        traverseNode = nullptr;


                    }
                    else if (c+1 > labl.length())
                    {
                        //key len > label len
                        std::string keySuffix = restOfKey.substr(labl.length(), restOfKey.length()-labl.length());
                        int keyFirstChar = keySuffix.at(0);

                        //node that current edge points to
                        Node* target = traverseNode->edges[nextChar]->targetNode;
                        //set label in targetNode to hold the rest of key not covered in the og label
                        target->edges[keyFirstChar] = new Edge();
                        traverseNode->isLeaf = false;
                        target->edges[keyFirstChar]->label = keySuffix;
                        target->edges[keyFirstChar]->targetNode = new Node();
                        //insert value into new node

                        target->edges[keyFirstChar]->targetNode->vvalue = new ValueType(value);


                        //key has fully been added
                        charFound = key.length();
                        traverseNode = nullptr;
                    }
                    else
                    {
                        //c is index of character that is still in both strings, where their next characters are different
                        std::string sharedPrefix = labl.substr(0, c);

                        std::string labelSuffix = labl.substr(c, labl.length()-c);
                        std::string keySuffix = restOfKey.substr(c, restOfKey.length()-c);

                        //set current label to the shared prfix
                        traverseNode->edges[nextChar]->label = sharedPrefix;

                        //hold pointer to previous node pointed to by edge
                        Node* infoBeingMoved = traverseNode->edges[nextChar]->targetNode;

                        traverseNode->isLeaf = false;

                        Node* ng = new Node();
                        traverseNode->edges[nextChar]->targetNode = ng;
                        

                        int keyFirstChar = keySuffix.at(0);
                        int labelFirstChar = labelSuffix.at(0);

                        ng->edges[keyFirstChar] = new Edge();
                        ng->edges[keyFirstChar]->label = keySuffix;
                        //insert new keyvalue at ng->edges[keyFirstChar]->targetNode
                        
                        ng->edges[keyFirstChar]->targetNode->vvalue = new ValueType(value);


                        ng->edges[labelFirstChar] = new Edge();
                        ng->edges[labelFirstChar]->label = labelSuffix;
                        ng->edges[labelFirstChar]->targetNode = infoBeingMoved;



                        //key has fully been added
                        charFound = key.length();
                        traverseNode = nullptr;

                    }
                }
            }
        }
    
    return;
}

template <typename ValueType>
ValueType* RadixTree<ValueType>::search(std::string key) const
{

    Node* traverseNode = root;
    int charFound = 0;

    while (traverseNode != nullptr && charFound < key.length())
    {

        
        Edge* nextEdge = nullptr;


        if (key.at(charFound) == '\r')
        {
            charFound++;
            break;
        }
        //select edge from traveseNode.edges where edge.label is next part of key

        //should get ascii encoding for this character, which would respond to its index in the array of edges
        int firstChar = key.at(charFound);
        //gets edge at this position in array, unless it's empty
        if (traverseNode->edges[firstChar] == nullptr)
        {
            traverseNode = nullptr;
            break;
        }
        Edge currentEdge = *traverseNode->edges[firstChar];
        int edgeLen = currentEdge.label.length();

        std::string keyCompareChars = key.substr(charFound, edgeLen);

        if ((keyCompareChars == currentEdge.label) || (keyCompareChars+"\r" == currentEdge.label))
        {
            nextEdge = traverseNode->edges[firstChar];
            charFound += edgeLen;
        }



        if (nextEdge != nullptr)
        {
            //moves onto the next node that held the next character portion of key
            traverseNode = nextEdge->targetNode;

        }
        else
        {
            //ends loop, no following portion of key was found in any of the edge nodes
            traverseNode = nullptr;
        }

    }


    if (traverseNode != nullptr && (charFound == key.length()+1 || charFound == key.length()))
    {
        return traverseNode->vvalue;
    }

    return nullptr;


}




#endif /* Header_h */
