
#include "Logger.hpp"

void     glw::Logger::log(const std::string &prefix, const std::string &message)
{
    std::cout << prefix << " : " << message << "\033[0m" << std::endl;
}


void     glw::Logger::debug(const std::string &message)
{
    glw::Logger::log(LOGGER_GLWRAP"[DEBUG]", message);
}

void     glw::Logger::info(const std::string &message)
{
    glw::Logger::log(LOGGER_GLWRAP""LOGGER_INFO, message);
}

void     glw::Logger::warning(const std::string &message)
{
    glw::Logger::log(LOGGER_GLWRAP"[WARNING]", message);
}

void     glw::Logger::error(const std::string &message)
{
    glw::Logger::log(LOGGER_GLWRAP""LOGGER_ERROR, message);
}

void     glw::Logger::shader(const std::string &message)
{
    glw::Logger::log(LOGGER_GLWRAP""LOGGER_SHADER, message);
}


void     glw::Logger::debug(const std::stringstream &message)
{
    glw::Logger::log(LOGGER_GLWRAP"[DEBUG]", message.str());
}

void     glw::Logger::info(const std::stringstream &message)
{
    glw::Logger::log(LOGGER_GLWRAP""LOGGER_INFO, message.str());
}

void     glw::Logger::warning(const std::stringstream &message)
{
    glw::Logger::log(LOGGER_GLWRAP"[WARNING]", message.str());
}

void     glw::Logger::error(const std::stringstream &message)
{
    glw::Logger::log(LOGGER_GLWRAP""LOGGER_ERROR, message.str());
}

void     glw::Logger::shader(const std::stringstream &message)
{
    glw::Logger::log(LOGGER_GLWRAP""LOGGER_SHADER, message.str());
}

