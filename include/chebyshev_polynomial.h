#pragma once

#include <functional>

namespace MomentSketchQuery {


struct ChebyshevPolynomial {
    VecD coeffs;

    ChebyshevPolynomial(VecD coeffs_): coeffs(coeffs_) {}


    static ChebyshevPolynomial fit(std::function<DType(DType)> f, Float64 tol) {

    }

};

}