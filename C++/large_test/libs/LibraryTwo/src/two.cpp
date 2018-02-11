#include "LibraryTwo/two.hpp"
#include <algorithm>


auto twotwo( gsl::span<int> range ) noexcept -> int
{
    return std::accumulate(range.cbegin(), range.cend(), 0);
}
