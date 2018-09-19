#pragma once
#include <memory>
#include <string>

#include "stream.hpp"
#include "textserializer.hpp"
#include "string.hpp"



namespace stx {

constexpr int LOGLVL_UNSET = 0;
constexpr int LOGLVL_ERROR = 100;
constexpr int LOGLVL_WARN  = 110;
constexpr int LOGLVL_INFO  = 120;
constexpr int LOGLVL_DEBUG = 130;
constexpr int LOGLVL_TRACE = 140;


class LoggerConfig;

LoggerConfig& getLoggerConfig(const std::string& name);



class LoggerConfig
{
public:
    LoggerConfig();
    LoggerConfig(std::string name);

    std::string displayname;
    int loglevel;
};

class Logger
{
public:
    constexpr Logger(const char* name) :
        m_name(name)
    {

    }

    template <typename... Args>
    void trace(const char* fmt, Args... args) const
    {
        log(LOGLVL_TRACE, "Trace", fmt, args...);
    }

    template <typename... Args>
    void debug(const char* fmt, Args... args) const
    {
        log(LOGLVL_DEBUG, "Debug", fmt, args...);
    }

    template <typename... Args>
    void info(const char* fmt, Args... args) const
    {
        log(LOGLVL_INFO, "Info", fmt, args...);
    }

    template <typename... Args>
    void warn(const char* fmt, Args... args) const
    {
        log(LOGLVL_WARN, "Warning", fmt, args...);
    }

    template <typename... Args>
    void error(const char* fmt, Args... args) const
    {
        log(LOGLVL_ERROR, "Error", fmt, args...);
    }

    template <typename... Args>
    void log(int req_lvl, const char* lvlname, const char* fmt, Args... args) const
    {
        LoggerConfig cfg = getLoggerConfig(m_name);

        int loglevel = cfg.loglevel;
        if (!loglevel) {
            loglevel = getLoggerConfig("").loglevel;
        }
        if (loglevel < req_lvl) {
            return;
        }

        if (cfg.displayname.empty()) {
            stx::txterr.printf("[%] ", lvlname);
        } else {
            stx::txterr.printf("[%][%] ", lvlname, cfg.displayname);
        }
        stx::txterr.printf(fmt, args...);
        stx::txterr.print("\n");
    }

    const char* getName() const
    {
        return m_name;
    }

    LoggerConfig& getConfig() const
    {
        return getLoggerConfig(m_name);
    }

private:
    const char* m_name;
};

}
