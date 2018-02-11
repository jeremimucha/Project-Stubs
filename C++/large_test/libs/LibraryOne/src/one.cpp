#include "LibraryOne/one.hpp"


auto oneone( std::ostream& os, const std::string& s ) noexcept -> void
{
    for( int i=0; i<3; ++i ){
        os << s << ", ";
    }
}
