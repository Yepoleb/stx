#include <string>
#include <cstdlib>

#include "stx/path.hpp"
#include "stx/string.hpp"



namespace stx {

std::string home()
{
    const char* home_env = std::getenv("HOME");
    if (!home_env) {
        return "";
    }
    return home_env;
}

std::string expandHome(const std::string& path)
{
    if (!stx::startswith("~/", path)) {
        return path;
    }
    return home() + path.substr(1);
}

}
