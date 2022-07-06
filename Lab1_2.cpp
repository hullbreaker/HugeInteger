#include <iostream>
#include "TestHugeInteger.h"
#include <chrono>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

void HugeIntTiming() {
    int MAXNUMINTS = 100;
    int MAXRUN = 100;

    chrono::system_clock::time_point startTime, endTime;
    double runTime = 0.0;
    double durationMs = 0.0;
    int n = 5;
    for (int numInts = 0; numInts < MAXNUMINTS; numInts++) {
        cpp_int u = 4938298232; //creates a random integer of n digits
        cpp_int v = 4938298232; //creates a random integer of n digits
        startTime = chrono::system_clock::now();
        for (int numRun = 0; numRun < MAXRUN; numRun++) {
            cpp_int o = u * v;
        }
        endTime = chrono::system_clock::now();
        durationMs = (chrono::duration<double, std::milli>(endTime - startTime)).count();
        runTime += durationMs / ((double)MAXRUN);
    }
    runTime = runTime / ((double)MAXNUMINTS);
    cout << "runTime: " << runTime << endl;
    cout << "durationMs: " << durationMs << endl;
}
/*int main()
{
    using namespace boost::multiprecision;

    HugeIntTiming();

    return 0;
}*/
int main() {
    HugeIntTiming();
    // when test failed, the size of number <= NUM_DISPLAY, display the number
    unsigned int num_display = 1000;
    // iterate the MAX_SIZE_ARRAY MAX_RUN times
    unsigned int max_run = 50;
    // use for generating invalid string for constructor 1 (with string input)
    unsigned int max_invalid_string = 5;
    // different size for test
    vector<int> max_size_array = {1,5,10,50,100,500};
    //vector<int> max_size_array = {10};

    double totalMark = 0;

    string demoLab = "Lab2"; // set to Lab1 or Lab2

    TestHugeInteger thi(num_display, max_run, max_invalid_string, max_size_array);

    if (demoLab == "Lab1"){
        totalMark += thi.testConstructorString();
        totalMark += thi.testConstructorNumber();
        totalMark += thi.testPositiveAddition();

    }else{
        totalMark += thi.testAdditionSubtraction();
        totalMark += thi.testCompareTo();
        totalMark += thi.testMultiplication();
    }

    cout << "******************************" << endl;
    cout << "*** FINAL TOTAL MARK IS " << totalMark << " ***" << endl;
    cout << "******************************" << endl;

    //HugeIntTiming();

    return 0;
}

