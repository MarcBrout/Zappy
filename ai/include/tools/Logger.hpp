//
// Created by Pierre Bougon on 03/02/17.
//

#ifndef PLAZZA_LOGGER_HPP_
#define PLAZZA_LOGGER_HPP_

#include <fstream>
#include <string>
#include "Singleton.hpp"

namespace Debug
{
    extern bool DEBUG_MODE;
}

class Logger : public Singleton<Logger>
{
private:

    friend class Singleton<Logger>;

    Logger();
    Logger(const Logger&) = delete;
    virtual ~Logger();

public:
    enum Level
    {
        DEBUG = 0,
        INFO,
        WARNING,
        ERROR,
        NONE
    };

    void        setFile(std::string const &file);
    void        closeFile();
    void        log(std::string msg, Level lvl = INFO);
    void        logFile(std::string msg, Level lvl = INFO);
    std::string toString(Level lvl);

    static void log(Level lvl, std::string msg, bool abort = false);

private:
    std::ofstream outFile;
};


#endif // !PLAZZA_LOGGER_HPP_
