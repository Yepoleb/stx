#pragma once
#include <cassert>
#include <stdint.h>

#include "stx/stream.hpp"
#include "stx/serializer.hpp"
#include "stx/filestream.hpp"
#include "stx/conversion.hpp"



namespace stx {

class TextSerializer : public BaseSerializer
{
public:
    constexpr TextSerializer() : BaseSerializer() {}
    constexpr TextSerializer(BaseStream* stream) : BaseSerializer(stream) {}
    constexpr TextSerializer(BaseStream& stream) : BaseSerializer(&stream) {}

    void write(const std::string& str);
    void write(const char* str);
    void print(const std::string& str);
    void print(const char* str);
    std::string read(int64_t size = -1);
    std::string readUntil(char sep = '\n', int64_t size = -1);
    std::string readLine(int64_t size = -1);

    template<typename T, typename... Targs>
    void print(T first, Targs... args)
    {
        print(first);
        print_space(args...);
    }

    template<typename T>
    void print(T arg)
    {
        print(stx::to_str(arg));
    }

    void print()
    {

    }

    template<typename... Targs>
    void println(Targs... args)
    {
        print(args...);
        print("\n");
    }

    void printf(const char* format)
    {
        print(format);
    }

    template<typename T, typename... Targs>
    void printf(const char* format, T value, Targs... args)
    {
        for (; *format != '\0'; format++) {
            if (*format == '%') {
               print(value);
               printf(format + 1, args...);
               return;
            }
            print(*format);
        }
    }

    template<typename... Targs>
    void printf(std::string format, Targs... args)
    {
        printf(format.c_str(), args...);
    }

private:

    template<typename T>
    void print_space(T last)
    {
        print(" ");
        print(last);
    }

    template<typename T, typename... Targs>
    void print_space(T middle, Targs... args)
    {
        print(" ");
        print(middle);
        print_space(args...);
    }
};



static TextSerializer txtout(stx::sout);
static TextSerializer txtin(stx::sin);
static TextSerializer txterr(stx::serr);

template<typename... Targs>
void print(Targs... args)
{
    txtout.print(args...);
}

template<typename... Targs>
void println(Targs... args)
{
    txtout.println(args...);
}

template<typename... Targs>
void printf(Targs... args)
{
    txtout.printf(args...);
}

}
