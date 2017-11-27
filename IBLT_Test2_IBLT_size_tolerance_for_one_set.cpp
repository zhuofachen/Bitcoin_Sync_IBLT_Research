#include <iostream>
#include "iblt.h"
#include "murmurhash3.h"
#include <fstream>
#include "testFunctions.h"
#include <string>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std; 

  // testing different IBLT size with constant number of entries (5000). 
 // try to find the minimum size of IBLT. 

template<typename T>
std::uint64_t Toint(T vector)
{
  std::uint64_t num;
  num=vector[1]*256+vector[0];
  return num;
}

int main ()
{




  int numEntriesA;

  //creates multidimensioanl arrays of key/value pairs for each iblt
  vector<uint8_t>** myEntriesA = entryArray("KeyTxIDFile1.txt", numEntriesA); 
  // printArray(myEntriesA, numEntriesA);
  for(double m=1.1; m<=1.5; m +=0.04)

  {
  //Creat  IBLT tables

  IBLT* ibltA = new IBLT(size_t(m*numEntriesA), myEntriesA[0][1].size());

  //adds entries into the IBLT
  addEntries(myEntriesA, ibltA, numEntriesA); 
  bool success=0;
  int numsuccess=0;
  int numEntries=5000;
  for (int i=0; i<numEntries; i++)
  {  
     vector<uint8_t> value;
     success = ibltA->get(Toint(myEntriesA[i][0]), value);
     if(value==myEntriesA[i][1])
     {
       numsuccess++;
     }
  }
  double ratio=double(numsuccess)/numEntries;
  if(numsuccess==numEntries)
    {cout<<"when IBLT is "<<m<<"times of the entry number, the successfully rate 100%"<<endl;} 
  else 
    {cout<<"when IBLT is "<<m<<"times of the entry number, the successfully rate is: "<<ratio<<endl;}



  }

  
 
return 0;

}
