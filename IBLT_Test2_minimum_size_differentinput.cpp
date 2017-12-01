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
#include <cmath>
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

int main ()
{

  int numEntries;  //total number of txID in the file.

  //creates multidimensioanl arrays of key/value pairs for each iblt
  vector<uint8_t>** myEntries= entryArray("KeyTxIDFile1.txt", numEntries); 
   
  int startpointA=0;
  int numEntriesA=200; // set the number of txID we want to get. 
  vector<uint8_t>** myEntriesA=subArray(myEntries, startpointA, numEntriesA);
  cout<<"number of entries is: "<<numEntriesA<<endl;

  for(double m=1.1; m<=1.5; m +=0.02)    //m is the ratio of BILT over the numEntries. 

  {
   
      int numberLoop=10;
      float successfulrate[numberLoop];  //define an array to store the successful rate. 

      float ratesum=0.0;   //define the mean and stand deviation. ratesum refers to the sum of all the succesfulrate. 
 
     for (int j=0; j<numberLoop; j++)  //loop operate for 100 times. 
    {
      //Creat  IBLT tables

       IBLT* ibltA = new IBLT(size_t(m*numEntriesA), myEntriesA[0][1].size());
       //adds entries into the IBLT
       addEntries(myEntriesA, ibltA, numEntriesA); 
       bool success=0;
       int numsuccess=0;

         for (int i=0; i<numEntriesA; i++)
       {  
     vector<uint8_t> value;
     success = ibltA->get(Toint(myEntriesA[i][0]), value);
     if(value==myEntriesA[i][1])
       {
       numsuccess++;
       }
       }
      successfulrate[j]=float(numsuccess)/numEntriesA;
      ratesum=ratesum+successfulrate[j];
  
      delete ibltA;   //release space; 
    }

     float mean, std; 
     mean=ratesum/numberLoop; 
   //calculate standard deviation. 
     float numerator = 0;
     for(int h=0; h<numberLoop;h++)
      {
        numerator=numerator + pow((successfulrate[h] - mean), 2);
      }
      std=sqrt(numerator/numberLoop);
     cout<<"when IBLT is "<<m<<" times of the entry number, the mean successfully rate is "
     <<mean<<" with a standard deviation: "<<std<<endl;
  
  }

return 0;

}
