#include <iostream>
#include "iblt.h"
#include "murmurhash3.h"
#include "utilstrencodings.h"
#include "testFunctions.h"
#include <string>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>


using namespace std;

template<typename T>
std::uint64_t Toint(T vector)
{
  std::uint64_t num;
  num=vector[1]*256+vector[0];
  return num;
}

vector<uint8_t>** subArray(vector<uint8_t>** aVals, int startpoint, int size)
{
    vector<uint8_t>** subArray=new vector<uint8_t> *[size];
      for (int i=0; i<size; i++)
    {   
    	subArray[i]=new vector<uint8_t>[2];
    	subArray[i]=aVals[startpoint+i];
    }
    return subArray;
}

// testing the tolerance of IBLT, adjusting the IBLT size with different numbers of entries.
//get the relation of IBLT size with the number of difference and the entry number of key value pairs
//IBLTsize=ratioFromEntries*ratioOfDif*(numEntriesA+numEntriesB);

int main()
{
    //input the number of entries for IBLTA and IBLTB. startpoint means the 
    //starting point to retreive element from the original array from ID txt file. 
   int numEntries;
   

  //creates multidimensioanl arrays of key/value pairs for each iblt table
   vector<uint8_t>** myEntries = entryArray("KeyTxIDFile7.txt", numEntries); 

   cout<<"IBLTsize:           "<<"ratioOfdifference:  "<<"KeyValuePairs:      "<<"Success:            "<<endl;
   // cout<<numEntries<<endl;
   for (int a=150; a<2500; a=a+100)
   { 
   	for (double b=0.01; b<0.3; b=b+0.02)
   	{   
   		for(double c=0.1; c<1.5; c=c+0.2)
   		{

   int numEntriesA=a;
   int numEntriesB=a;
   int startpointA=0;
   double ratioOfDif=b;
   double ratioFromEntries=c;
   int IBLTsize=std::ceil(ratioFromEntries*ratioOfDif*(numEntriesA+numEntriesB));
   int startpointB=std::ceil(ratioOfDif*(numEntriesA+numEntriesB)/2);
   vector<uint8_t>** myEntriesA=subArray(myEntries, startpointA, numEntriesA);
   vector<uint8_t>** myEntriesB=subArray(myEntries, startpointB, numEntriesB);
 
  //Creat two IBLT tables, note the size of table should be the same for following substraction. 

  IBLT* ibltA = new IBLT(size_t(IBLTsize), myEntriesA[0][1].size());

  IBLT* ibltB = new IBLT(size_t(IBLTsize), myEntriesB[0][1].size()); 
  //adds entries into the IBLT
  addEntries(myEntriesA, ibltA, numEntriesA); 
  addEntries(myEntriesB, ibltB, numEntriesB);
  std::set<std::pair<uint64_t,std::vector<uint8_t> > > positiveValuesC;
  std::set<std::pair<uint64_t,std::vector<uint8_t> > > negativeValuesC;
  IBLT ibltC = *ibltA - *ibltB;
  bool successfulC = ibltC.listEntries(positiveValuesC, negativeValuesC);

  std::set<std::pair<uint64_t, std::vector<uint8_t> > > entrySetA;

  for (int i = 0; i < numEntriesA; i++)
  {
    entrySetA.insert(std::make_pair(Toint(myEntriesA[i][0]), myEntriesA[i][1]));
  }
    
    entrySetA.insert(negativeValuesC.begin(),negativeValuesC.end());

    // cout<< "output the key in B-set after adding the difference of A"<<endl; 
    std::set<std::pair<uint64_t, std::vector<uint8_t> > > entrySetB;
  for (int i = 0; i < numEntriesB; i++)
  {
    entrySetB.insert(std::make_pair(Toint(myEntriesB[i][0]), myEntriesB[i][1]));
  } 
    entrySetB.insert(positiveValuesC.begin(),positiveValuesC.end());
   
     //check whether the IBLTA+positiveValues==IBLTB+negativeValues. 
    bool success=entrySetA==entrySetB;
    if(success)
    {
       cout<<c<<"                   "<<b<<"                   "<<2*a<<"                   "<<success<<"                   "<<endl;	
    }
     

    	 }


   	 }
   

   }
   
  return 0;
}
