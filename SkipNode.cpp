/**
 * @file    SkipNode.cpp
 * @brief   Class definition of a Skipnode with accompanied implementations
 * 
 * @author  Cade Powers
 * @date    Friday, January 24
 */ 

#ifndef SKIPNODE_CPP
#define SKIPNODE_CPP
#include <iostream>
#include <stdexcept>

template <typename v_type>
class SkipNode{
    public:
        SkipNode(v_type newKey, int nexts);
        ~SkipNode();
        v_type getKey();
        void setKey(v_type key);
        std::ostream& write(std::ostream& strm=std::cout);
        SkipNode* getNext(int level);
        void setNext(int level, SkipNode* newNext);
        
      private:
        v_type key;
        SkipNode** nexts;
        int numOfNexts;      
};

/**
 * @brief       Constructor for SkipNode
 * @detailed    This constructor sets the variables and allocates a dynamic array for the specified number of levels
 *                  then nulls out the levels
 * @param       newKey      The key value being stored within the node
 * @param       levels      The number of levels that the node will keep pointers to
 */ 
template <typename v_type>
SkipNode<v_type>::SkipNode(v_type newKey, int levels) : key{newKey}, numOfNexts{levels}
{
    nexts = new SkipNode*[levels];          //creates an array to represent the different levels of the node within the skip list
    for (int i = 0; i < numOfNexts; ++i)    //null all levels
        nexts[i] = 0;
}

/**
 * @brief       Releases the dynamic memory that holds the pointers to subsequent nodes
 */
template <typename v_type>
SkipNode<v_type>::~SkipNode()
{
    delete[] nexts;
}

/**
 * @brief       Retrieves the key value within the node
 * @return      The key value of generic type
 */ 
template <typename v_type>
v_type SkipNode<v_type>::getKey()
{
    return key;
}

/**
 * @brief       Sets the key value within the node
 * @param       key     The key value
 */ 
template <typename v_type>
void SkipNode<v_type>::setKey(v_type key)
{
    this->key = key;
}

/**
 * @brief       Retrieves the next node on specified level
 * @param       level       the level the user wants to skip across
 * @return      A pointer to the next node on specified level
 */ 
template <typename v_type>
SkipNode<v_type>* SkipNode<v_type>::getNext(int level)
{   
    //verifies the input and takes appropriate action
    return (level < 0 || level >= numOfNexts) ? throw std::out_of_range{"Level does not exist in this node...\n"} : nexts[level];
}

/**
 * @brief       Writes the keys and the subsequent nodes to output stream
 * @param       strm        The stream that the node will be printed out to which defaults to std::cout
 * @return      The ouput stream containing the SkipNode key and levels
 */ 
template <typename v_type>
std::ostream& SkipNode<v_type>::write(std::ostream &strm)
{
    strm << key << " ";
    for (int i = 0; i < numOfNexts; ++i){                                   //print all next pointers
        strm << "(";
        (nexts[i] != 0) ? strm << nexts[i]->getKey() : strm << "------";    //prints key if next position is not null
        strm << ") ";
    }
    strm << std::endl;
    return strm;
}

/**
 * @brief       Sets the subsequent node on specified level
 * @param       level       The level the user wants to change
 */ 
template <typename v_type>
void SkipNode<v_type>::setNext(int level, SkipNode *newNext)
{
    //verifies the input and takes appropriate action
    (level < 0 || level >= numOfNexts) ? throw std::out_of_range{"Level does not exist in this node...\n"} : nexts[level] = newNext;
}

#endif