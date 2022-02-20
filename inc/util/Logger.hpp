
#ifndef GLWLLOGGER_HPP
# define GLWLLOGGER_HPP

# include <iostream>
# include <string>
# include <sstream>

/* Log macros for stream input */

#ifndef GLW_DISABLE_LOG

# define LOG_DEBUG(msg) { std::stringstream ss; ss << msg; Logger::debug(ss); }
# define LOG_INFO(msg) { std::stringstream ss; ss << msg; Logger::info(ss); }
# define LOG_WARNING(msg) { std::stringstream ss; ss << msg; Logger::warning(ss); }
# define LOG_ERROR(msg) { std::stringstream ss; ss << msg; Logger::error(ss); }
# define LOG_SHADER(msg) { std::stringstream ss; ss << msg; Logger::shader(ss); }

/* Log style */

# define LOGGER_GLWRAP  "[\033[1;36mGL\033[0;97mWRAP\033[0m]"

# define LOGGER_ERROR   "[\033[1;31mERROR\033[0m] "
# define LOGGER_SHADER  "[\033[0;31mS\033[0;33mH\033[0;32mA\033[0;36mD\033[0;34mE\033[0;35mR\033[0m]"
# define LOGGER_INFO    "[\033[1;32mINFO\033[0m]  "

#else

# define LOG_DEBUG(msg) 
# define LOG_INFO(msg) 
# define LOG_WARNING(msg) 
# define LOG_ERROR(msg) 
# define LOG_SHADER(msg)

#endif 

namespace glw
{
    class Logger
    {
        private:
            static void     log(const std::string &prefix, const std::string &message);

        public:
            static void     debug(const std::string &message);
            static void     info(const std::string &message);
            static void     warning(const std::string &message);
            static void     error(const std::string &message);
            static void     shader(const std::string &message);

            static void     debug(const std::stringstream& message);
            static void     info(const std::stringstream& message);
            static void     warning(const std::stringstream& message);
            static void     error(const std::stringstream& message);
            static void     shader(const std::stringstream& message);

    };
}

#endif