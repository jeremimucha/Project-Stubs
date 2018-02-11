#include <iostream>
#include "toplevel.hpp"


auto toplevel_function( gsl::span<int> ints ) noexcept -> void
{
    auto first = true;
    for( auto i : ints ){
        if( !first ){
            std::cout << ", ";
            first = false;
        }
        std::cout << i;
    }
}
