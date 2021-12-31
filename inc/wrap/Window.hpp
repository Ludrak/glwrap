
#ifndef GLWWINDOW_HPP
# define GLWWINDOW_HPP

# include <GL/glew.h>
# include <GLFW/glfw3.h>

# include <string>
# include <iostream>

# include "stbi_image.h"

# include "util/utils.hpp"

/* Events Types */
# define WIN_LOAD   0
# define WIN_SETUP  1
# define WIN_DRAW   2

namespace glw
{
    class Window
    {
        public:
            typedef void    (*event_func)(void);

            Window(const unsigned int width=1280, const unsigned int height=720, const std::string title="glwrap");
            virtual ~Window();

            void            setEvent(int event, event_func func);

            int             init();
            int             run(void);

            unsigned int    getWidth(void) const;
            unsigned int    getHeight(void) const;

            /* TODO implement inputs */
            virtual void    onKeyPressed(unsigned int key);
            virtual void    onKeyReleased(unsigned int key);

            virtual void    onMousePressed(unsigned int key);
            virtual void    onMouseReleased(unsigned int key);
            virtual void    onMouseMoved(unsigned int key);
            virtual void    onMouseScrolled(unsigned int key);

        private:
            GLFWwindow          *_window;

            unsigned int        _width;
            unsigned int        _height;
            const std::string   _title;

            event_func          _on_load;
            event_func          _on_setup;
            event_func          _on_draw;
    };
}

#endif