/**
 * @file    SkipList.cpp
 * @brief   Implementation for a generic random Skip List 
 * 
 * @author  Cade Powers
 * @date    Wednesday, January 30
 */ 

#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <ctime>
#include "SkipNode.cpp"

template <typename valueType>
class SkipList{
    public:
        SkipList();
        ~SkipList();
        bool add(valueType key);
        std::ostream& printList(std::ostream& strm=std::cout);
        SkipNode<valueType>* search(valueType key);
        void remove(valueType key);



    private:
        int coinFlip();
        int maxLevel();

        SkipNode<valueType>* nexts[100];
        int currentNodes;
        int currentMaxLevel;
};


/**
 * @brief       Constructs an Skip List with no key values
 */ 
template <typename valueType>
SkipList<valueType>::SkipList() : currentNodes{0}, currentMaxLevel{0}
{
    for (int i = 0; i < 100; ++i)   //null all pointer values in the array
        nexts[i] = nullptr;  
    srand(time(0));                 //set here for adding function to be random
}

/**
 * @brief       Deconstructs the Skip List starting at front and going to back
 */ 
template <typename valueType>
SkipList<valueType>::~SkipList()
{
    SkipNode<valueType> *current = nexts[0];
    SkipNode<valueType> *copy = nexts[0];
    while(current != 0){
        current = current->getNext(0);
        delete copy;
        copy = current;
    }
}

/**
 * @brief       Prints the list
 * @param       strm        The ouput stream
 * @return      The stream with the list's nodes in it
 */ 
template <typename valueType>
std::ostream& SkipList<valueType>::printList(std::ostream& strm)
{
    SkipNode<valueType>* current = nexts[0];
    while(current){
        current->write(strm);
        current = current->getNext(0);
    }
    strm << "-> #\n";
    return strm;
}
/**
 * @brief       Finds a value in the list
 * @detailed    Returns a nullptr if the value was not found
 * @param       key     The key value to be found
 * @return      A pointer to the node containing the key value
 */ 
template <typename valueType>
SkipNode<valueType>* SkipList<valueType>::search(valueType key)
{
    SkipNode<valueType> *found = nullptr;
    SkipNode<valueType>* previous = nullptr;
    SkipNode<valueType>* current = nexts[currentMaxLevel];                                              //start at top level
    for(int currentLevel = currentMaxLevel; currentLevel >= 0 && found == nullptr; --currentLevel){     //search and add to each level until last level is reached
        while(current != 0 && current->getKey() != key && current->getKey() < key){
            previous = current;
            current = current->getNext(currentLevel);
        }
        if(current->getKey() == key)        //key was found
            found = current;
        else if(previous)                   //drop back and start one level lower
            current = previous;
        else                                //start one level lower from beginning
            current = nexts[currentLevel - 1];
    }
    return found;
}

/**
 * @brief       Removes the node with the key value
 * @param       key     The key value to be removed from the list
 */ 
template <typename valueType>
void SkipList<valueType>::remove(valueType key)
{
    SkipNode<valueType> *found = nullptr;
    SkipNode<valueType>* previous = nullptr;
    SkipNode<valueType>* current = nexts[currentMaxLevel];                          //start at top level
    for(int currentLevel = currentMaxLevel; currentLevel >= 0; --currentLevel){     //search and add to each level until last level is reached
        while(current != 0 && current->getKey() != key && current->getKey() < key){
            previous = current;
            current = current->getNext(currentLevel);
        }
        if(current->getKey() == key && previous){        //key was found with a previous
            previous->setNext(currentLevel, current->getNext(currentLevel));
            found = current;
            current = previous;
            
        }
        else if(current->getKey() == key){              //key was found without a previous
            nexts[currentLevel] = current->getNext(currentLevel);
            found = current;
            current = nexts[currentLevel - 1];
        }
        else if(previous)                       //if there is a previous go back
            current = previous;
        else                                    //else start at beginning of lower level
            current = nexts[currentLevel - 1];
    }
    delete found;
}

/**
 * @brief       Calculates the level at the time of execution
 * @return      The largest possible level of the SkipList
 */ 
template <typename valueType>
int SkipList<valueType>::maxLevel()
{
    int maxLevel = 1;
    if(currentNodes > 0)
        maxLevel = log2(currentNodes) + 1;
    return maxLevel;
}

/**
 * @brief       Calculates the number of next pointers a node will have
 * @return      Number of next pointers for the node
 */
template <typename valueType>
int SkipList<valueType>::coinFlip()
{
    int numOfNexts = 1;
    while(numOfNexts <= maxLevel() && rand() % 2 != 0)
        ++numOfNexts;   //if even then stop
    return numOfNexts;
}

/**
 * @brief       Adds a new node to the list
 * @param       key     The value to be added to the list
 * @return      A boolean value to indicate success or failure of addition
 */ 
template <typename valueType>
bool SkipList<valueType>::add(valueType key)
{
    bool success = true;
    int coinFlips = coinFlip();
    SkipNode<valueType>* newNode = new SkipNode<valueType>{key, coinFlips};
    if(newNode){
        coinFlips--;                        //puts into array subscripts to prevent off by one
        if(coinFlips > currentMaxLevel)     //updates the current max level
            currentMaxLevel = coinFlips;                                                      
        SkipNode<valueType>* previous = nullptr;
        SkipNode<valueType>* current = nexts[coinFlips];                        //start at level of coin flips
        for(int currentLevel = coinFlips; currentLevel >= 0; --currentLevel){   //search and add to each level until last level is reached
            while(current != 0 && current->getKey() < newNode->getKey()){
                previous = current;
                current = current->getNext(currentLevel);
            }
            newNode->setNext(currentLevel, current);
            if(previous){   //if there is a past node
                previous->setNext(currentLevel, newNode);
                current = previous;
            }
            else{           //no previous node
                nexts[currentLevel] = newNode;
                if(currentLevel != 0)
                    current = nexts[currentLevel - 1];
            }
            
        }
        currentNodes++;     //add to total nodes in the list
    }
    else
        success = false;
    return success;
}

#endif