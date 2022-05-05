//Header file : Test.h 

#include <cppunit/TestCase.h> 
#include "class.h"

using namespace CppUnit; 

class AlgoTestCase : public TestCase 

{ 
public:

void testcomparisonAT();
void testcomparisonPID();
//void testfcfs();
static Test* suite(); 

}; 
