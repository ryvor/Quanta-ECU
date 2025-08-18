#include "thermistors.h"
#include <math.h>

float steinhart_temp_c(float resistance, float a, float b, float c) {
    float lnR = logf(resistance);
    float invT = a + b*lnR + c*lnR*lnR*lnR;
    return (1.0f/invT) - 273.15f;
}
