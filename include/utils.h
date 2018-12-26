

namespace MomentSketchQuery {


VecD zeros(UInt32 size) {
    return VecD(size, 0.0);
}

Vec<VecUInt> getBinomials(UInt32 m) {
    Vec<VecUInt> binoms(m);
    for (auto& b: binoms) b.resize(m);

    for (UInt32 i = 0; i<m; i++) {
        binoms[i][0] = 1;
        for (int j=1; j<=i; j++) {
            binoms[i][j] = binoms[i-1][j-1] + binoms[i-1][j];
        }
    }
    return binoms;
}

Vec<VecInt> getChebyCoefficients(UInt32 k) {
    Vec<VecInt> chebyCoeffs(k);
    for (VecInt& c: chebyCoeffs) c.resize(k);

    chebyCoeffs[0][0] = 1;
    if (k == 1) {
        return chebyCoeffs;
    }

    chebyCoeffs[1][1] = 1;
    for (UInt32 i = 2; i < k; i++) {
        const VecInt& c1 = chebyCoeffs[i-1];
        const VecInt& c2 = chebyCoeffs[i-2];
        chebyCoeffs[i][0] = -c2[0];
        for (UInt32 j = 1; j <= i; j++) {
            chebyCoeffs[i][j] = 2*c1[j-1] - c2[j];
        }
    }
    return chebyCoeffs;
}

VecD shiftPowerSum(VecD powerSums, DType r, DType xc) {
    ENSURE(powerSums.size() > 0, "Got empty powerSums");

    VecD scaledPowerSums(powerSums.size());
    VecD nxcPowers = zeros(powerSums.size());
    VecD rNegPowers = zeros(powerSums.size());

    nxcPowers[0] = 1.0;
    rNegPowers[0] = 1.0;

    for (UInt32 i=1; i<powerSums.size(); ++i) {
        nxcPowers[i] = nxcPowers[i-1] * (-xc);
        rNegPowers[i] = rNegPowers[i-1] / r;
    }

    Vec<VecUInt> mBinoms = getBinomials(powerSums.size());
    for (UInt32 m = 0; m < powerSums.size(); m++) {
        DType sum = 0.0;
        for (int j = 0; j<=m; j++) {
            sum += mBinoms[m][j]*nxcPowers[m-j]*powerSums[j];
        }
        scaledPowerSums[m] = rNegPowers[m] * sum;
    }
    return scaledPowerSums;
}

VecD powerSumsToZerodMoments(VecD powerSums, DType min, DType max) {
    ENSURE(powerSums.size() > 0, "Got empty powerSums");

    DType r = (max - min) / 2;
    DType xc = (max + min) / 2;
    VecD scaledPowerSums = shiftPowerSum(powerSums, r, xc);
    DType count = scaledPowerSums[0];
    for (UInt32 i = 0; i < powerSums.size(); ++i) {
        scaledPowerSums[i] /= count;
    }
    return scaledPowerSums;
}

VecD powerSumsToChebyMoments(VecD powerSums, DType min, DType max) {
    ENSURE(powerSums.size() > 0, "Got empty powerSums");

    DType r = (max - min) / 2;
    DType xc = (max + min) / 2;
    // First rescale the variables so that they lie in [-1,1]
    VecD scaledPowerSums = shiftPowerSum(powerSums,r,xc);

    DType count = powerSums[0];
    Vec<VecInt> cCoeffs = getChebyCoefficients(powerSums.size());
    // Then convert from power sums to chebyshev moments
    VecD scaledChebyMoments(powerSums.size());
    for (int i = 0; i <powerSums.size(); i++) {
        DType sum = 0.0;
        for (int j = 0; j <= i; j++) {
            sum += cCoeffs[i][j]*scaledPowerSums[j];
        }
        scaledChebyMoments[i] = sum / count;
    }
    return scaledChebyMoments;
}



}