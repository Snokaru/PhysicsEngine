#include "MathUtils.h"

double clamp(double x, double min_value, double max_value) {
    if (x < min_value)
        return min_value;
    else if (x > max_value)
        return max_value;
    return x;
}
