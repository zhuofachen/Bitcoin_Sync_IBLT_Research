#include <iostream>
#include "iblt.h"
#include "murmurhash3.h"
#include "testFunctions.h"
#include <string>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
std::uint64_t Toint(T vector)
{
  std::uint64_t num;
  num=vector[1]*256+vector[0];
  return num;
}



// test the functionality of the IBLT subtraction. 
//enerate a IBLT_C which stores the elements unique to one of the IBLTs. 

int main()
{
  
  // cout << "Testing IBLT Subtraction, delete " << endl;
  int numEntriesA, numEntriesB;
  //creates multidimensioanl arrays of key/value pairs for each iblt
  vector<uint8_t>** myEntriesA = entryArray("KeyTxIDFile1.txt", numEntriesA); 
  vector<uint8_t>** myEntriesB = entryArray("KeyTxIDFile2.txt", numEntriesB);
  //Creat two IBLT tables, note the size of table should be the same for following substraction. 

  IBLT* ibltA = new IBLT(size_t(numEntriesB), myEntriesA[0][1].size());

  IBLT* ibltB = new IBLT(size_t(numEntriesB), myEntriesB[0][1].size()); 

  //adds entries into the IBLT
  addEntries(myEntriesA, ibltA, numEntriesA); 
  addEntries(myEntriesB, ibltB, numEntriesB);

  std::set<std::pair<uint64_t,std::vector<uint8_t> > > positiveValuesC;

  std::set<std::pair<uint64_t,std::vector<uint8_t> > > negativeValuesC;
     
  // subtracts the iblts
  IBLT ibltC = *ibltA - *ibltB;

  cout<<"subtracts the iblts"<<endl;

  //lists the entries from the new iblt
  bool successfulC = ibltC.listEntries(positiveValuesC, negativeValuesC);

  cout<<"The result of substract is: "<<successfulC<<endl;

  //checks if listing entries was successful
  if (successfulC)
  {
    cout << "Successful listing of entries out of IBLT C Made from A- B" << endl;
    
  }
   
  vector<uint64_t> differences = makeDiffVector(myEntriesA, myEntriesB, numEntriesA, numEntriesB);  
  std::set<std::pair<uint64_t, std::vector<uint8_t> > >::iterator it;

  cout << "Keys only in A:" << endl;
  cout  << endl;

  //iterates through the set of keys only in A
  for (it = positiveValuesC.begin(); it != positiveValuesC.end(); it++)
  {
    uint64_t key1 = std::get<0>(*it);

    cout << key1 << endl;  
    vector<uint8_t> vec1; 
    //use the key to get the value vector store in the IBLT table. 
    bool success1 = ibltA->get(key1, vec1); 
    for (unsigned int i=0; i<vec1.size(); i++)
          {    
               
              cout<<unsigned(vec1[i])<<"  ";

          } 
      cout<<endl;
  }

  cout << "Keys Only in B:" << endl;
   cout  << endl;

  //iterates through the set of keys only in B
  for (it = negativeValuesC.begin(); it != negativeValuesC.end(); it++)
  {
    uint64_t key2 = std::get<0>(*it);

    cout << key2 << endl;
    vector<uint8_t> vec2; 
     // use the key to get the value vector store in the IBLT table. 
    // result in some error if use i<64, should always use vec.size(),prevent out of range. 
    bool success2 = ibltB->get(key2, vec2); 
    for (unsigned int i=0; i<vec2.size(); i++)
          {    
               
              cout<<unsigned(vec2[i])<<"  ";

          } 
      cout<<endl;
  }
  // print the difference in IBLTA and IBLTB, note this elements are before erasing. 
    for (int i = 0; i < differences.size(); i++)
  {
    cout << differences[i]<< endl;
  } 
   return 0;
 }