// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <cassert>
#include "Measurement.h"
#include "Measurements.h"

using DataLogger::MeasurementType;
using DataLogger::Measurement;


int main()
{
    assert(Measurement{1.0} != Measurement{2.0});
    assert(Measurement{1.0} == Measurement{1.0});
    assert(Measurement{1.1} == Measurement{1.0999});
    assert(Measurement{1.1} == Measurement{1.1009});
    assert(Measurement{1.1} != Measurement{1.001});

    assert(Measurement{1.0} < Measurement{2.0});
    assert(Measurement{2.0} > Measurement{1.0});
    assert(Measurement{2.0} > Measurement{-1.0});
    assert(Measurement{-2.0} < Measurement{1.0});

    assert(Measurement{1.0} <= Measurement{1.001});
    assert(Measurement{1.002} > Measurement{1.0});

    assert((Measurement{1.0} <=> Measurement{NAN}) == std::partial_ordering::unordered);
    return 0;
}
