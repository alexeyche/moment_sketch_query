
#include "moment_sketch_query.h"


#include <iostream>

using namespace MomentSketchQuery;

namespace UtilsTest {
    void getBinomials_test() {
        auto b = getBinomials(6);
        ENSURE(b[5][2] == 10L, "getBinomials_test failed");
    }


    void shiftPowerSum_test() {
        auto r = shiftPowerSum({1.0, 2.0, 3.0}, 2.0, 0.5);
        auto exp = VecD{1.0,0.75,0.3125};
        ENSURE(r == exp, "shiftPowerSum_Test failed");
    }

    void powerSumsToChebyMoments_test() {
        VecD uniformPowerSums = {1001,500500,333833500,250500250000};
        VecD r = powerSumsToChebyMoments(uniformPowerSums, 0, 1000);
        VecD exp = {1.0, 0, -0.332, 0};
        ENSURE(r == exp, "powerSumsToChebyMoments_test failed");
    }
}


// std::cout << "scaledPowerSums = "; for (auto rr: scaledPowerSums) { std::cout << rr << ","; }; std::cout << "\n";



int main(int argc, const char** argv) {
    UtilsTest::getBinomials_test();
    UtilsTest::shiftPowerSum_test();
    UtilsTest::powerSumsToChebyMoments_test();
    std::cout << "Done\n";
}

