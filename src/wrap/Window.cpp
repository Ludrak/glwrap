
#define STB_IMAGE_IMPLEMENTATION
#include "Window.hpp"
#include <sys/time.h>

glw::Window::Window(const unsigned int width, const unsigned int height, const std::string &title)
:	_window(NULL),
	_width(width),
	_height(height),
	_title(title),
	_on_key_pressed(NULL),
	_on_key_released(NULL),
	_on_mouse_pressed(NULL),
	_on_mouse_released(NULL),
	_on_mouse_moved(NULL),
	_on_mouse_scrolled(NULL)

{
  //  this->_on_load();
}

glw::Window::~Window()
{

}

int             glw::Window::run()
{
    glw::Logger::info("executing window setup");
    if (this->_on_setup)
        this->_on_setup();

    glw::Logger::info("running window");
	
	gettimeofday(&this->_last_time, NULL);
    /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(this->_window))
	{
		gettimeofday(&this->_current_time, NULL);
		if ((this->_current_time.tv_usec - this->_last_time.tv_usec + 
		   ((this->_current_time.tv_sec - this->_last_time.tv_sec) & 0xFF) * 1000000) > 1000000)
		{
			this->_last_time = this->_current_time;
			this->_fps = this->_frames;
			this->_frames = 0;
		}

		/* Clears previous buffers */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Running */
        if (this->_on_draw)
		    this->_on_draw();


		/* Swap front and back buffers */
		glfwSwapBuffers(this->_window);
		/* Poll for and process events */
		glfwPollEvents();

		glfwGetCursorPos(this->_window, &this->_mouse_x, &this->_mouse_y);
		++this->_frames;
	}
    return (0);
}

unsigned int    glw::Window::getWidth(void) const
{
    return(this->_width);
}

unsigned int    glw::Window::getHeight(void) const
{
    return (this->_height);
}

int             glw::Window::getFPS(void) const
{
	return (this->_fps);
}


void			glw::Window::setTitle(const std::string& new_title)
{
	glfwSetWindowTitle(this->_window, new_title.c_str());
	this->_title = new_title;
}


void            glw::Window::mapEvent(int event, void (*func)(void))
{
    switch (event)
    {
        case WIN_LOAD:
            this->_on_load = func;
            break;
        case WIN_SETUP:
            this->_on_setup = func;
            break;
        case WIN_DRAW:
            this->_on_draw = func;
            break;
    }
}


void            glw::Window::mapInputEvent(int event, void (*func)(int))
{
	static bool key_event_set = false;
	static bool mouse_event_set = false;

    switch (event)
    {
		case WIN_KEYPRESS:
			LOG_INFO("hooked keypress input event")
			this->_on_key_pressed = func;
			if (!key_event_set)
			{
				glfwSetKeyCallback(this->_window, &glw::key_callback);
				key_event_set = true;
			}
			break;
		case WIN_KEYRELEASE:
			LOG_INFO("hooked keyrelease input event")
			this->_on_key_released = func;
			if (!key_event_set)
			{
				glfwSetKeyCallback(this->_window, &glw::key_callback);
				key_event_set = true;
			}
			break;
		case WIN_MOUSEPRESS:
			LOG_INFO("hooked mousepress input event")
			this->_on_mouse_pressed = func;
			if (!mouse_event_set)
			{
				glfwSetMouseButtonCallback(this->_window, &glw::mouse_button_callback);
				mouse_event_set = true;
			}
			break;
		case WIN_MOUSERELEASE:
			LOG_INFO("hooked mouserelease input event")
			this->_on_mouse_released = func;
			if (!mouse_event_set)
			{
				glfwSetMouseButtonCallback(this->_window, &glw::mouse_button_callback);
				mouse_event_set = true;
			}
			break;
    }
}


void            glw::Window::mapInputEvent(int event, void (*func)(double, double))
{
    switch (event)
    {
		case WIN_MOUSEMOVE:
			this->_on_mouse_moved = func;
			break;
		case WIN_MOUSESCROLL:
			LOG_INFO("hooked mousescroll input event")
			this->_on_mouse_scrolled = func;
			glfwSetScrollCallback(this->_window, &glw::mouse_scroll_callback);
			break;
    }
}


double          glw::Window::getMouseX(void) const
{
	return  (this->_mouse_x);
}

double          glw::Window::getMouseY(void) const
{
	return  (this->_mouse_y);
}





int             glw::Window::init(void)
{
	stbi_set_flip_vertically_on_load(true);  

    if (!glfwInit())
	{
		LOG_ERROR("GLFW (v" << glfwGetVersionString() << "): glewInit: " << glfwGetError(NULL));
		return (1);
	}

#ifdef __APPLE__
  	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
  	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
  	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	LOG_INFO("initalized GLFW (v" << glfwGetVersionString() << ")");

    /* create glfw window */
	this->_window = glfwCreateWindow(this->_width, this->_height, this->_title.c_str(), NULL, NULL);
	if (!this->_window)
	{
        char *description;
        glfwGetError((const char**)&description);
		LOG_ERROR("cannot glfwCreateWindow() : " << description);
		glfwTerminate();
		return (1);
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(this->_window);

	/* GLEW */
    glewExperimental = GL_TRUE;
	GLenum glew_err = glewInit();
	if (glew_err != GLEW_OK)
	{
		LOG_ERROR("GLEW (v" << glewGetString(GLEW_VERSION) << "): glewInit: " << glewGetErrorString(glew_err));
		return (1);
	}

	glfwSetWindowUserPointer(this->_window, this);

	LOG_INFO("initalized GLEW (v" << glewGetString(GLEW_VERSION) << ")");
    glw::Logger::info("executing load");
    if (this->_on_load)
        this->_on_load();
    return (0);
}
