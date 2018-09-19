#pragma once
#include <stdexcept>


namespace stx {

class NotImplementedError : public std::exception
{
    const char* what() const noexcept {
        return "Feature not implemented";
    }
};

}
