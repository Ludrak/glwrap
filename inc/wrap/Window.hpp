
#ifndef GLWWINDOW_HPP
# define GLWWINDOW_HPP

# include <GL/glew.h>
# include <GLFW/glfw3.h>

# include <string>
# include <iostream>

# include "util/stbi_image.h"

# include "util/utils.hpp"

/* Events Types, map thoses with Window::mapEvent(int event, void (*callback)(...)) */
# define WIN_LOAD           0
# define WIN_SETUP          1
# define WIN_DRAW           2
# define WIN_KEYPRESS       3
# define WIN_KEYRELEASE     4
# define WIN_MOUSEPRESS     5
# define WIN_MOUSERELEASE   6
# define WIN_MOUSEMOVE      7
# define WIN_MOUSESCROLL    8

namespace glw
{
    class Window
    {
        public:
            typedef void    (*event_func)(void);

            typedef void    (*input_event_key_func)(const int key);
            typedef void    (*input_event_mouse_func)(const int button);
            typedef void    (*input_event_mouse_diff_func)(const double xoff, const double yoff);

            Window(const unsigned int width=1280, const unsigned int height=720, const std::string& title="glwrap");
            virtual ~Window();

            void            mapEvent(int event, void (*func)(void));
            void            mapInputEvent(int event, void (*func)(int));
            void            mapInputEvent(int event, void (*func)(double, double));

            int             init();
            int             run(void);

            unsigned int    getWidth(void) const;
            unsigned int    getHeight(void) const;

            int             getFPS(void) const;

            void            setTitle(const std::string &title);

            double          getMouseX(void) const;
            double          getMouseY(void) const;

        protected:
            friend void     key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
            friend void     mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
            friend void     mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

        private:
            GLFWwindow          *_window;

            unsigned int        _width;
            unsigned int        _height;
            double              _mouse_x;
            double              _mouse_y;
            std::string         _title;

            int                 _fps;
            int                 _frames;
            struct timeval      _current_time;
            struct timeval      _last_time;

            event_func          _on_load;
            event_func          _on_setup;
            event_func          _on_draw;

            /*  Input                                */
            input_event_key_func        _on_key_pressed;
            input_event_key_func        _on_key_released;
            input_event_mouse_func      _on_mouse_pressed;
            input_event_mouse_func      _on_mouse_released;
            input_event_mouse_diff_func _on_mouse_moved;
            input_event_mouse_diff_func _on_mouse_scrolled;
    };

    inline void    key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        (void)scancode;
        (void)mods;
        glw::Window *win = static_cast<glw::Window*>(glfwGetWindowUserPointer(window));
        if (win->_on_key_pressed && action == GLFW_PRESS)
            win->_on_key_pressed(key);
        else if (win->_on_key_released && action == GLFW_RELEASE)
            win->_on_key_released(key);

    }

    inline void    mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        (void)mods;
        glw::Window *win = static_cast<glw::Window*>(glfwGetWindowUserPointer(window));
        if (win->_on_mouse_pressed && action == GLFW_PRESS)
            win->_on_mouse_pressed(button);
        else if (win->_on_mouse_released && action == GLFW_RELEASE)
            win->_on_mouse_released(button);
    }

    inline void    mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        glw::Window *win = static_cast<glw::Window*>(glfwGetWindowUserPointer(window));
        if (win->_on_mouse_scrolled)
            win->_on_mouse_scrolled(xoffset, yoffset);
    }
}

#endif