/**
 **************************************************************
 * @file    SkipListTest.cpp
 * @brief   Tests implementation of SkipList by adding randomly and printing out. Visual evaluation
 * @remarks
 *      This Skip List was created to fulfill an assignment in my Data Structures class
 * 
 * @author  Cade Powers
 * @date    Friday, January 25
 **************************************************************  
 */

#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include "SkipList.cpp"

int main()
{

  //length of test values added to Skip List
  const int testLength = 50;
    
  //create skiplist and add nodes
  SkipList<int> list;
  for (int i = 0; i < testLength; i++) 
    list.add(rand());
  list.add(12);
  list.add(123);
  //list.add("Cade");


  //test search functions
  SkipNode<int> *valueFound = list.search(12);
  if (valueFound){
    std::cout << "The memory address of 12 is: " << valueFound << "\n";
    std::cout << "The value found was: " << valueFound->getKey() << std::endl;
  }


  //test remove function
  list.remove(12);
  if(!list.search(12))
    std::cout << "Value was removed successfully...\n\n";
  
  
  //user verification
  std::cout << "\n\nVerify list structure and press enter...";
  std::cin.ignore();
  

  std::cout << "All done...\n";
  return 0;
}