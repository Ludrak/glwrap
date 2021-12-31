
#define STB_IMAGE_IMPLEMENTATION
#include "Window.hpp"

glw::Window::Window(const unsigned int width, const unsigned int height, const std::string title)
: _window(NULL), _width(width), _height(height), _title(title)
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

    /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(this->_window))
	{
		/* Clears previous buffers */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Running */
        if (this->_on_draw)
		    this->_on_draw();


		/* Swap front and back buffers */
		glfwSwapBuffers(this->_window);
		/* Poll for and process events */
		glfwPollEvents();
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

/* to override */
void            glw::Window::onKeyPressed(unsigned int key)
{(void)key;}

void            glw::Window::onKeyReleased(unsigned int key)
{(void)key;}


void            glw::Window::onMousePressed(unsigned int key)
{(void)key;}

void            glw::Window::onMouseReleased(unsigned int key)
{(void)key;}

void            glw::Window::onMouseMoved(unsigned int key)
{(void)key;}

void            glw::Window::onMouseScrolled(unsigned int key)
{(void)key;}

void            glw::Window::setEvent(int event, event_func func)
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


int             glw::Window::init(void)
{
	stbi_set_flip_vertically_on_load(true);  

    if (!glfwInit())
	{
		LOG_ERROR("GLFW (v" << glfwGetVersionString() << "): glewInit: " << glfwGetError(NULL));
		return (1);
	}

#ifdef __APPLE__
  	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
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

	LOG_INFO("initalized GLEW (v" << glewGetString(GLEW_VERSION) << ")");
    glw::Logger::info("executing load");
    if (this->_on_load)
        this->_on_load();
    return (0);
}


