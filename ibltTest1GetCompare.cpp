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

  //Creat  IBLT tables

  IBLT* ibltA = new IBLT(size_t(1.5*numEntriesA), myEntriesA[0][1].size());

  //adds entries into the IBLT
  addEntries(myEntriesA, ibltA, numEntriesA); 

  for(int numEntries=500; numEntries<6000;numEntries +=500)
  {


  bool success=0;
  int numsuccess=0;
  for (int i=0; i<numEntries; i++)
  {  
  	 vector<uint8_t> value;
  	 success = ibltA->get(Toint(myEntriesA[i][0]), value);
  	 if(value==myEntriesA[i][1])
  	 {
  	 	 numsuccess++;
  	 	 // cout<<"get value successffully, numsuccess= "<<numsuccess<<endl;
  	 }
  }

  double ratio=numsuccess/numEntries;
  if(numsuccess==numEntries)
  	{cout<<"successfully get all the TxID from the IBLT, successfully rate 100%"<<endl;} 
  else 
  	{cout<<"the successfully rate is: "<<ratio<<endl;}


   }
 
return 0;

}



    
     