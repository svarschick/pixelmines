#pragma once

#include <QtTypes>

#include <algorithm>

namespace utility
{

template<typename T>
T ValueRange(T value, T min, T max)
{
    return std::max(min, std::min(value, max));
}

} // namespace utility
