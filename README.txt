# IBLT-Research

This is Zhuofa Chen working on a new version of IBLT implementation.

Description of Files:

Original Files From Gavin Andresen's Repository: https://github.com/gavinandresen/IBLT_Cplusplus.

iblt.cpp - main implementation of the IBLT. iblt.h - accompanying header file for iblt.cpp. iblt_test.cpp - Andresen's testing program for his implementation. 
murmurhash3.cpp - C++ program containing the hash functions used for the IBLT. 
murmurhash3.h - accompanying header file to hash function file.

Added Files: 
testFunctions.cpp - originally from Matt Cote's repository: https://github.com/mwcote/IBLT-Research. This is a revised version containing necessary functions to run test programs. 
testFunctions.h - accompanying header file. 

IBLT_Test1_get_compare.cpp - Test program for list entries and get value function of IBLT.
IBLT_Test2_IBLT_size_tolerance_for_one_set.cpp - Test program for the different IBLT size with constant number of entries (5000). The program output the successfully rate of the get function.
IBLT_Test2_IBLT_size_tolerance_for_one_set_result - the result of "IBLT_Test2_IBLT_size_tolerance_for_one_set.cpp". 
IBLT_Test3_IBLT_subtraction_and makedifference.cpp - Test the functionality of the IBLT subtraction. Attempts to subtract two IBLTs and tests list entries of resulting IBLT. IBLT_Test4_IBLT_toleranceOfdiffrence.cpp - testing the tolerance of IBLT, adjusting the IBLT size with different numbers of entries and different ratio of difference between two IBLTs. IBLT_Test4_IBLT_toleranceOfdiffrence_result - the result of "IBLT_Test4_IBLT_toleranceOfdiffrence.cpp".

Compilation instructions: In order to run the new test programs, the files iblt.cpp, murmurhash3.cpp, testFunctions.cpp, and one of the test programs (ex: IBLT_Test1_get_compare.cpp) must all be compiled together.


This material is based upon work supported by the National Science Foundation under Grant No. CCF-1563753. Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation
