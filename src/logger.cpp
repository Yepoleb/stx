#include <string>
#include <memory>
#include <mutex>
#include <map>

#include "stx/logger.hpp"


namespace stx {

static std::map<std::string,std::unique_ptr<LoggerConfig>> logger_map;
static std::mutex logger_mutex;



LoggerConfig::LoggerConfig()
{
    loglevel = 0;
}

LoggerConfig::LoggerConfig(std::string name)
{
    displayname = name;
    loglevel = 0;
}

LoggerConfig& getLoggerConfig(const std::string& name)
{
    logger_mutex.lock();
    if (logger_map.count(name)) {
        LoggerConfig& cfg = *logger_map[name];
        logger_mutex.unlock();
        return cfg;
    }

    std::unique_ptr<LoggerConfig> cfg_ptr = std::make_unique<LoggerConfig>(name);
    LoggerConfig& cfg = *cfg_ptr;
    if (name.empty()) {
        // Root logger
        cfg.loglevel = LOGLVL_ERROR;
    }
    logger_map.insert({name, std::move(cfg_ptr)});
    logger_mutex.unlock();
    return cfg;
}

}
