
#ifndef GLWUTILS_HPP
# define GLWUTILS_HPP

# include "Logger.hpp"

/* define GLW_DEBUG to run in debug mode*/
# ifdef GLW_DEBUG

/* define GLW_DEBUG to expand debug mode to print all glw calls */
# ifndef GLW_DEBUG_FULL

#   define GLW_ERROR(comment, sstr) \
    {\
        bool   has_err = false; \
        GLenum errorCode = 0; \
        while ((errorCode = glGetError()) != GL_NO_ERROR) \
        { \
            has_err = true; \
            std::string error; \
            switch (errorCode) \
            { \
                case GL_INVALID_ENUM:                  error = "GL_INVALID_ENUM"; break; \
                case GL_INVALID_VALUE:                 error = "GL_INVALID_VALUE"; break; \
                case GL_INVALID_OPERATION:             error = "GL_INVALID_OPERATION"; break; \
                case GL_STACK_OVERFLOW:                error = "GL_STACK_OVERFLOW"; break; \
                case GL_STACK_UNDERFLOW:               error = "GL_STACK_UNDERFLOW"; break; \
                case GL_OUT_OF_MEMORY:                 error = "GL_OUT_OF_MEMORY"; break; \
                case GL_INVALID_FRAMEBUFFER_OPERATION: error = "GL_INVALID_FRAMEBUFFER_OPERATION"; break; \
            } \
            std::cout << LOGGER_GLWRAP"[\033[1;31mGL_ERROR\033[0m] \033[38;2;255;200;200m" << __FILE__ << ":" << __LINE__ << "\033[0m: \033[1;31mError\033[0m: " << comment << ": \033[38;2;255;150;0m" << error << "\033[0m (" << errorCode << ")" << std::endl; \
        }\
        if (has_err) \
            exit (errorCode); \
    }

#  else

#   define GLW_ERROR(comment, sstr) \
    {\
        std::stringstream ss; \
        ss << sstr; \
        std::cout << comment << "(" << ss.str() << ")" << std::endl; \
        bool   has_err = false; \
        GLenum errorCode = 0; \
        while ((errorCode = glGetError()) != GL_NO_ERROR) \
        { \
            has_err = true; \
            std::string error; \
            switch (errorCode) \
            { \
                case GL_INVALID_ENUM:                  error = "GL_INVALID_ENUM"; break; \
                case GL_INVALID_VALUE:                 error = "GL_INVALID_VALUE"; break; \
                case GL_INVALID_OPERATION:             error = "GL_INVALID_OPERATION"; break; \
                case GL_STACK_OVERFLOW:                error = "GL_STACK_OVERFLOW"; break; \
                case GL_STACK_UNDERFLOW:               error = "GL_STACK_UNDERFLOW"; break; \
                case GL_OUT_OF_MEMORY:                 error = "GL_OUT_OF_MEMORY"; break; \
                case GL_INVALID_FRAMEBUFFER_OPERATION: error = "GL_INVALID_FRAMEBUFFER_OPERATION"; break; \
            } \
            std::cout << LOGGER_GLWRAP"[\033[1;31mGL_ERROR\033[0m] \033[38;2;255;200;200m" << __FILE__ << ":" << __LINE__ << "\033[0m: \033[1;31mError\033[0m: " << comment << ": \033[38;2;255;150;0m" << error << "\033[0m (" << errorCode << ")" << std::endl; \
        }\
        if (has_err) \
            exit (errorCode); \
    }

#  endif

# else
#  define GLW_ERROR(comment, sstr)
# endif

# endif