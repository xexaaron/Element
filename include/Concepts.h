#include <type_traits>
#include <iostream>

namespace Concepts {

    template<typename T>
    concept StringType = std::is_convertible_v<T, std::string>;

    template <typename T>
    bool IsNumber(T arg) {
        return std::is_arithmetic_v<T> && std::numeric_limits<T>::is_integer; 
    }
}
