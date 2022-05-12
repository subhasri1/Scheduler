
#include "../inc/test_algo.h"



using namespace CppUnit; 

#include <iostream> 

using namespace std; 

//testcase01
void AlgoTestCase::testfcfs(){
ofstream file;
file.open("../data/dt.txt");
string s[]={"1,55,0,2,0,0","1,56,1,2,0,0","1,57,5,3,0,0","1,58,6,4,0,0"};
for(int i=0;i<4;i++){
file<<s[i]<<endl;
}
file.close();
struct process exp[]={{55,1,2,0,0,0,0,2,2,0,0,0},{56,1,2,1,0,0,1,3,4,0,0,1},{57,1,3,5,0,0,0,3,8,0,0,0},{58,1,4,6,0,0,2,6,12,0,0,2}};
struct process *ret=fcfs();
int length=sizeof(exp)/sizeof(struct process);
for(int i=0;i<length;i++){
CPPUNIT_ASSERT(exp[i].WaitingTime==ret[i].WaitingTime);
CPPUNIT_ASSERT(exp[i].TurnAroundTime==ret[i].TurnAroundTime);
CPPUNIT_ASSERT(exp[i].ComplitionTime==ret[i].ComplitionTime);
}
}

 
//testcase02
void AlgoTestCase::testcomparisonAT()
{
struct process p1,p2;
p1.ArrivalTime=5;
p2.ArrivalTime=10;	 
bool expected=true;
CPPUNIT_ASSERT(expected==comparisonAT(p1,p2));

} 
//testcase03
void AlgoTestCase::failcomparisonAT()
{
struct process p1,p2;
p1.ArrivalTime=20;
p2.ArrivalTime=10;	 
bool expected=true;
CPPUNIT_ASSERT(expected==comparisonAT(p1,p2)); 
}

//testcase04
void AlgoTestCase::testcomparisonPID()
{
struct process p1,p2;
p1.pid=5568;
p2.pid=5689;
	 
bool expected=true;
CPPUNIT_ASSERT(expected==comparisonPID(p1,p2)); 
}
//testcase05
void AlgoTestCase::testpriority(){
ofstream file;
file.open("../data/dt.txt",ios::out);
string s[]={"2,55,11,0,2,0","2,56,28,5,0,0","2,57,2,12,3,0","2,58,10,2,1,0","2,59,16,9,4,0"};
struct process exp[]={{56,2,28,5,0,0,0,5,33,0,0,0},{58,2,10,2,1,0,23,25,35,0,0,0},{55,2,11,0,2,0,24,24,35,0,0,0},{57,2,2,12,3,0,33,45,47,0,0,0},{59,2,16,9,4,0,31,40,56,0,0,0}};

int length=sizeof(exp)/sizeof(struct process);
for(int i=0;i<length;i++){
file<<s[i]<<endl;
}
file.close();
//cout<<length<<endl;
struct process *ret=priority();

for(int i=0;i<length;i++){
CPPUNIT_ASSERT(exp[i].WaitingTime==ret[i].WaitingTime);
//cout<<ret[i].ComplitionTime<<"-"<<exp[i].ComplitionTime<<endl;
CPPUNIT_ASSERT(exp[i].TurnAroundTime==ret[i].TurnAroundTime);

CPPUNIT_ASSERT(exp[i].ComplitionTime==ret[i].ComplitionTime);
}

}
//testcase06

void AlgoTestCase::testrr(){
ofstream file;
file.open("../data/dt.txt",ios::out);
string s[]={"3,55,5,0,0,4","3,56,6,1,0,4","3,57,3,2,0,4","3,58,1,3,0,4","3,59,5,4,0,4","3,60,4,6,0,4"};
struct process exp[]={{55,3,5,0,0,4,16,21,0,0,0,0},{56,3,6,1,0,4,16,22,0,0,0,0},{57,3,3,2,0,4,6,9,0,0,0,0},{58,3,1,3,0,4,8,9,0,0,0,0},{59,3,5,4,0,4,15,20,0,0,0,0},{60,3,4,6,0,4,10,14,0,0,0,0}};
int length=sizeof(exp)/sizeof(struct process);
cout<<"input"<<endl;
for(int i=0;i<length;i++){
file<<s[i]<<endl;
}
file.close();

cout<<"output"<<endl;
struct process *ret=rr();
cout<<ret[0].WaitingTime<<endl;

cout<<length<<endl;

for(int i=0;i<length;i++){
CPPUNIT_ASSERT(exp[i].WaitingTime==ret[i].WaitingTime);
CPPUNIT_ASSERT(exp[i].TurnAroundTime==ret[i].TurnAroundTime);

}
}

//creating suite of tests for various functionalities 

Test* AlgoTestCase::suite() 

{ 

TestSuite *testsuite = new TestSuite("AlgoTestCase");	 

testsuite->addTest(new TestCaller< AlgoTestCase>("testcomparisonAT",& AlgoTestCase ::testcomparisonAT)); 
testsuite->addTest(new TestCaller< AlgoTestCase>("testcomparisonPID",& AlgoTestCase ::testcomparisonPID)); 

testsuite->addTest(new TestCaller< AlgoTestCase>("failcomparisonAT",& AlgoTestCase ::failcomparisonAT));

testsuite->addTest(new TestCaller< AlgoTestCase>("testfcfs",& AlgoTestCase ::testfcfs));

testsuite->addTest(new TestCaller< AlgoTestCase>("testPriority",& AlgoTestCase ::testpriority));

//testsuite->addTest(new TestCaller< AlgoTestCase>("testrr",& AlgoTestCase ::testrr));

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







 
