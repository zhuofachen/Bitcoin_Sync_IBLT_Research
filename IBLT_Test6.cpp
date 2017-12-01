#include <iostream>
#include "iblt.h"
#include "murmurhash3.h"
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
//IBLTsize=1.5*ratioOfDif*(numEntriesA+numEntriesB); 

int main()
{
    
   int numEntries;
   

  //creates multidimensioanl arrays of key/value pairs for each iblt table
   vector<uint8_t>** myEntries = entryArray("KeyTxIDFile1.txt", numEntries); 

   
    
   int a=2000;     // set the entry number for the two IBLT set. 

for(double m=1.1; m<=1.5; m +=0.02)    //m is the ratio of BILT over the difference. 

  {
   int numberLoop=50;  //define the loop number.
   double successfulrate=0.0;  //define successful rate. 
   int numsuccess=0;
   for (int j=0; j < numberLoop; j++)  //loop operate for 100 times. 
    {
       int numEntriesA=a;
       int numEntriesB=a;
       int startpointA=0; //set the start point in the original entry Array to insert data into IBLTA. 
       double ratioOfDif=0.1; //set the ratio of difference between two IBLT
       int IBLTsize=std::ceil(m*ratioOfDif*(numEntriesA+numEntriesB));  //calculate the size of the IBLTA and IBLTB, also for IBLTC. 
       int startpointB=std::ceil(ratioOfDif*(numEntriesA+numEntriesB)/2); //set the start point in the original entry Array to insert data into IBLTB. 
       vector<uint8_t>** myEntriesA=subArray(myEntries, startpointA, numEntriesA);
       vector<uint8_t>** myEntriesB=subArray(myEntries, startpointB, numEntriesB);
 
        //Creat two IBLT tables, note the size of table should be the same for following substraction. 

       IBLT* ibltA = new IBLT(size_t(IBLTsize), myEntriesA[0][1].size());
       IBLT* ibltB = new IBLT(size_t(IBLTsize), myEntriesB[0][1].size()); 
       //adds entries into two IBLT
       addEntries(myEntriesA, ibltA, numEntriesA); 
       addEntries(myEntriesB, ibltB, numEntriesB); 
       std::set<std::pair<uint64_t,std::vector<uint8_t> > > positiveValuesC;
       std::set<std::pair<uint64_t,std::vector<uint8_t> > > negativeValuesC;
       //subtract two IBLT and assgin to IBLTC. 
       IBLT ibltC = *ibltA - *ibltB;
       bool successfulC = ibltC.listEntries(positiveValuesC, negativeValuesC);
       //create a set entrySetA to store all the element in IBLTA and the negativeValue, which is unique to IBLTB.
       std::set<std::pair<uint64_t, std::vector<uint8_t> > > entrySetA;

        for (int i = 0; i < numEntriesA; i++)
          {
             entrySetA.insert(std::make_pair(Toint(myEntriesA[i][0]), myEntriesA[i][1]));
          }
    
       entrySetA.insert(negativeValuesC.begin(),negativeValuesC.end());

       //create a set entrySetB to store all the element in IBLTB and the positiveValue, which is unique to IBLTA.
       std::set<std::pair<uint64_t, std::vector<uint8_t> > > entrySetB;
        for (int i = 0; i < numEntriesB; i++)
          {
             entrySetB.insert(std::make_pair(Toint(myEntriesB[i][0]), myEntriesB[i][1]));
          } 
       entrySetB.insert(positiveValuesC.begin(),positiveValuesC.end());
   
        //check whether the IBLTA+positiveValues==IBLTB+negativeValues. 

        if(entrySetA==entrySetB) { numsuccess++;}

        delete ibltA;   //release space; 
        delete ibltB;
   	}
    successfulrate=double(numsuccess)/numberLoop;
    cout<<"when IBLT is "<<m<<" times of the entry number, the successfully rate is "
    <<successfulrate<<endl;  

  }
  
  return 0;
}
