#pragma once

#include <kiss_fft.h>

namespace MomentSketchQuery {


VecD discreteCosineTransform(const VecD & f) {
    VecD transformed(f.size());
    const UInt32 n = f.size() - 1;
    if (f.size() == 2) {
        transformed[0] = 0.5 * (f[0] + f[1]);
        transformed[1] = 0.5 * (f[0] - f[1]);
    } else {
        VecD x(n);
        x[0] = 0.5 * (f[0] + f[n]);
        x[n >> 1] = f[n >> 1];
        DType t1 = 0.5 * (f[0] - f[n]);

        for(UInt32 i = 1; i < n >> 1; ++i) {
            DType a = 0.5D * (f[i] + f[n - i]);
            DType k = static_cast<DType>(i) * M_PI / static_cast<DType>(n);
            DType b = std::sin(k) * (f[i] - f[n - i]);
            DType c = std::cos(k) * (f[i] - f[n - i]);
            x[i] = a - b;
            x[n - i] = a + b;
            t1 += c;
        }


    }

}


}