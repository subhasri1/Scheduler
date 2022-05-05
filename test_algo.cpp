#include <cppunit/TestCase.h> 

#include <cppunit/TestCaller.h> 

#include <cppunit/TestSuite.h> 

#include <cppunit/ui/text/TestRunner.h> 
#include "test_algo.h"



using namespace CppUnit; 

#include <iostream> 

using namespace std; 

/*
void AlgoTestCase::testfcfs()
{

54	  5		3		8	   0		3
55	  0		2		2	   0		2
56	  1		2		4	   1		3
57	  6		4		12	   2		6*/

//struct process input[]={{55,2,0},{56,2,1},{54,3,5},{57,4,6}};
/*struct process expected[4]={{54,5,3,8,0,3},{55,0,2,2,0,2},{56,1,2,4,1,3},{57,6,4,12,2,6}};
CPPUNIT_ASSERT(expected==fcfs()); 
}
*/ 

void AlgoTestCase::testcomparisonAT()
{
struct process p1,p2;
p1.ArrivalTime=5;
p2.ArrivalTime=10;	 
bool expected=true;
CPPUNIT_ASSERT(expected==comparisonAT(p1,p2)); 
} 

void AlgoTestCase::testcomparisonPID()
{
struct process p1,p2;
p1.pid=5568;
p2.pid=5689;
	 
bool expected=true;
CPPUNIT_ASSERT(expected==comparisonPID(p1,p2)); 
}

//creating suite of tests for various functionalities 

Test* AlgoTestCase::suite() 

{ 

TestSuite *testsuite = new TestSuite("AlgoTestCase");	 

testsuite->addTest(new TestCaller< AlgoTestCase>("testcomparisonAT",& AlgoTestCase ::testcomparisonAT)); 
testsuite->addTest(new TestCaller< AlgoTestCase>("testcomparisonPID",& AlgoTestCase ::testcomparisonPID)); 

//testsuite->addTest(new TestCaller< AlgoTestCase>("testfcfs",& AlgoTestCase ::testfcfs));

return testsuite; 

} 

int main(int argc, char *argv[]) 

{ 

if (argc!=2) 

{ 

cout << "usage error " << endl; 

cout << "tester <name of the class to be tested> " << endl; 

exit(1); 

} 

 

CppUnit::TextUi::TestRunner testrunner; 

testrunner.addTest(AlgoTestCase::suite()); 

testrunner.run(); 

}







 
