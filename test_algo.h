//Header file : Test.h 
#include <cppunit/TestCase.h> 

#include <cppunit/TestCaller.h> 

#include <cppunit/TestSuite.h> 

#include <cppunit/ui/text/TestRunner.h> 
 
#include "class.h"
#include<fstream>

using namespace CppUnit; 

class AlgoTestCase : public TestCase 

{ 
public:

void testcomparisonAT();
void failcomparisonAT();
void testcomparisonPID();
void testfcfs();
void testpriority();
void testrr();
static Test* suite(); 

}; 
