#pragma once

#include <vector>
#include <sstream>
#include <exception>


namespace MomentSketchQuery {

    using Float64 = double;

    using DType = Float64;

    template <typename T>
    using Vec = std::vector<T>;

    using Int32 = int;
    using UInt32 = unsigned int;
    using VecD = std::vector<DType>;
    using VecUInt = std::vector<UInt32>;
    using VecInt = std::vector<Int32>;

    #define ENSURE(cond, message) \
        if(!(cond)) { \
            std::stringstream ss; \
            ss << message; \
            throw std::runtime_error(ss.str()); \
        }\


    // #define ASSERT(cond, message) \
    //     #ifndef NDEBUG \
    //     if (!(cond)) { \
    //         std::stringstream ss; \
    //         ss << message; \
    //         assert(false, ss.str()); \
    //     }\
    //     #endif \




}

#include "utils.h"
#include "max_ent_loss.h"

