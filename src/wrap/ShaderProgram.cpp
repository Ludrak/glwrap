
#include "ShaderProgram.hpp"


glw::ShaderProgram::ShaderProgram()
: _program(0), _name("unnamed_program")
{
}


glw::ShaderProgram::ShaderProgram(const std::string &name)
: _program(0), _name(name)
{
}


glw::ShaderProgram::~ShaderProgram()
{	
    for (std::vector<GLuint>::iterator it = this->_shaders.begin(); it != this->_shaders.end(); ++it)
    {
        glDeleteShader(*it);
		GLW_ERROR("glDeleteShader", *it);
    }
    glDeleteProgram(this->_program);
	GLW_ERROR("glDeleteProgram", this->_program);
	LOG_SHADER("deleted program '" << this->_name << "'");
}


void	glw::ShaderProgram::create()
{
	this->_program = glCreateProgram();
	GLW_ERROR("glCreateProgram", "");
	LOG_SHADER("created program '" << this->_name << "'");
}


void    glw::ShaderProgram::use() const
{
    glUseProgram(this->_program);
	GLW_ERROR("glUseProgram", this->_program);
}


int     glw::ShaderProgram::addShader(const std::string &shader_source, GLenum type)
{
    GLuint 	shader;

	/* creating and compiling shader */
	shader = glCreateShader(type);
	GLW_ERROR("glCreateShader", static_cast<intptr_t>(type));

	char *content = new char[shader_source.length() + 1];
	std::strcpy(content, shader_source.c_str());
	content[shader_source.length()] = 0;
	glShaderSource(shader, 1, (const char*const *)&content, NULL);
	GLW_ERROR("glShaderSource", shader << ", " << 1 << ", " << (const char*const *)&content << ", " << NULL);

	delete[] content;
	glCompileShader(shader);
	GLW_ERROR("glCompileShader", shader);

	/* check if compilation errors occured */
	int  success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	GLW_ERROR("glGetShaderiv", shader << ", " <<  static_cast<intptr_t>(GL_COMPILE_STATUS) << ", " << &success);
	if(success != GL_TRUE)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		GLW_ERROR("glGetShaderInfoLog", shader << ", " << 512 << ", " << NULL << ", " << infoLog);
		LOG_ERROR((type == GL_VERTEX_SHADER ? "vertex_shader[" : "fragment_shader[")  << this->_shaders.size() << "]" << ": Compilation Error:\033[38;2;255;200;200m\n" << infoLog << "\033[0m");
		glDeleteShader(shader);
		GLW_ERROR("glDeleteShader", shader);
        return (0);
	}
	LOG_SHADER("added " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader to program '" << this->_name << "'")
	this->_shaders.push_back(shader);
	glAttachShader(this->_program, shader);
	GLW_ERROR("glAttachShader", this->_program << ", " << shader);
    return (shader);
}


int     glw::ShaderProgram::addShaderFromFile(const std::string &shader_path, GLenum type)
{
	std::ifstream	vertex_file;
	vertex_file.open(shader_path);
	if (!vertex_file.is_open())
		return (-1);
	std::stringstream ss;
	ss << vertex_file.rdbuf();
    return (this->addShader(ss.str(), type));
}


int     glw::ShaderProgram::link()
{
    glLinkProgram(this->_program);
	GLW_ERROR("glLinkProgram", this->_program);

    /* check shader linker errors */
	int		success;
	glGetProgramiv(this->_program, GL_LINK_STATUS, &success);
	GLW_ERROR("glGetProgramiv", this->_program << ", " << (void*)GL_LINK_STATUS << ", " << &success);
	if(success != GL_TRUE)
	{
		GLchar infoLog[512];
    	glGetProgramInfoLog(this->_program, 512, NULL, infoLog);
		GLW_ERROR("glGetProgramInfoLog", this->_program << ", " << 512 << ", " << NULL << ", " << infoLog);
		LOG_ERROR("Linker Error:\n" << infoLog);

		for (std::vector<GLuint>::iterator it = this->_shaders.begin(); it != this->_shaders.end(); ++it)
        {
            glDeleteShader(*it);
			GLW_ERROR("glDeleteShader", *it);
        }
        glDeleteProgram(this->_program);
		GLW_ERROR("glDeleteProgram", this->_program);
		return (1);
	}
	LOG_SHADER("linked program '" << this->_name << "'");
	return (0);
}


void    glw::ShaderProgram::setUniform1i  (const std::string& name, int value)
{
    glUniform1i (glGetUniformLocation(this->_program, name.c_str()), value);
	//GLW_ERROR("glUniform1i");
}


void    glw::ShaderProgram::setUniform1ui (const std::string& name, unsigned int value)
{
    glUniform1ui(glGetUniformLocation(this->_program, name.c_str()), value);
	//GLW_ERROR("glUniform1ui");
}


void    glw::ShaderProgram::setUniform1d  (const std::string& name, double value)
{
    glUniform1d (glGetUniformLocation(this->_program, name.c_str()), value);
	//GLW_ERROR("glUniform1d");
}


void    glw::ShaderProgram::setUniform1f  (const std::string& name, float value)
{
    glUniform1f (glGetUniformLocation(this->_program, name.c_str()), value);
	//GLW_ERROR("glUniform1f");
}


void    glw::ShaderProgram::setUniform2i  (const std::string& name, int value1, int value2)
{
    glUniform2i (glGetUniformLocation(this->_program, name.c_str()), value1, value2);
	//GLW_ERROR("glUniform2i");
}


void    glw::ShaderProgram::setUniform2ui (const std::string& name, unsigned int value1, unsigned int value2)
{
    glUniform2ui(glGetUniformLocation(this->_program, name.c_str()), value1, value2);
	//GLW_ERROR("glUniform2ui");
}


void    glw::ShaderProgram::setUniform2d  (const std::string& name, double value1, double value2)
{
    glUniform2d (glGetUniformLocation(this->_program, name.c_str()), value1, value2);
	//GLW_ERROR("glUniform2d");
}


void    glw::ShaderProgram::setUniform2f  (const std::string& name, float value1, float value2)
{
    glUniform2f (glGetUniformLocation(this->_program, name.c_str()), value1, value2);
	//GLW_ERROR("glUniform2f");
}


void    glw::ShaderProgram::setUniform3i  (const std::string& name, int value1, int value2, int value3)
{
    glUniform3i (glGetUniformLocation(this->_program, name.c_str()), value1, value2, value3);
	//GLW_ERROR("glUniform3i");
}


void    glw::ShaderProgram::setUniform3ui (const std::string& name, unsigned int value1, unsigned int value2, unsigned int value3)
{
    glUniform3ui(glGetUniformLocation(this->_program, name.c_str()), value1, value2, value3);
	//GLW_ERROR("glUniform3ui");
}


void    glw::ShaderProgram::setUniform3d  (const std::string& name, double value1, double value2, double value3)
{
    glUniform3d (glGetUniformLocation(this->_program, name.c_str()), value1, value2, value3);
	//GLW_ERROR("glUniform3d");
}


void    glw::ShaderProgram::setUniform3f  (const std::string& name, float value1, float value2, float value3)
{
    glUniform3f (glGetUniformLocation(this->_program, name.c_str()), value1, value2, value3);
	//GLW_ERROR("glUniform3f");
}


void    glw::ShaderProgram::setUniform4i  (const std::string& name, int value1, int value2, int value3, int value4)
{
    glUniform4i (glGetUniformLocation(this->_program, name.c_str()), value1, value2, value3, value4);
	//GLW_ERROR("glUniform4i");
}


void    glw::ShaderProgram::setUniform4ui (const std::string& name, unsigned int value1, unsigned int value2, unsigned int value3, unsigned int value4)
{
    glUniform4ui(glGetUniformLocation(this->_program, name.c_str()), value1, value2, value3, value4);
	//GLW_ERROR("glUniform4ui");
}


void    glw::ShaderProgram::setUniform4d  (const std::string& name, double value1, double value2, double value3, double value4)
{
    glUniform4d (glGetUniformLocation(this->_program, name.c_str()), value1, value2, value3, value4);
	//GLW_ERROR("glUniform4d");
}


void    glw::ShaderProgram::setUniform4f  (const std::string& name, float value1, float value2, float value3, float value4)
{
    glUniform4f (glGetUniformLocation(this->_program, name.c_str()), value1, value2, value3, value4);
	//GLW_ERROR("glUniform4f");
}


void    glw::ShaderProgram::setUniform1iv (const std::string& name, GLsizei count, int *value)
{
	glUniform1iv(glGetUniformLocation(this->_program, name.c_str()), count, value);
	//GLW_ERROR("glUniform1iv");
}


void    glw::ShaderProgram::setUniform1fv (const std::string& name, GLsizei count, float *value)
{
	glUniform1fv(glGetUniformLocation(this->_program, name.c_str()), count, value);
	//GLW_ERROR("glUniform1fv");
}


void    glw::ShaderProgram::setUniform1dv (const std::string& name, GLsizei count, double *value)
{
	glUniform1dv(glGetUniformLocation(this->_program, name.c_str()), count, value);
	//GLW_ERROR("glUniform1dv");
}


void    glw::ShaderProgram::setUniform1uiv(const std::string& name, GLsizei count, unsigned int *value)
{
	glUniform1uiv(glGetUniformLocation(this->_program, name.c_str()), count, value);
	//GLW_ERROR("glUniform1ui");
}


void    glw::ShaderProgram::setUniform2iv (const std::string& name, GLsizei count, int *value)
{
	glUniform2iv(glGetUniformLocation(this->_program, name.c_str()), count, value);
	//GLW_ERROR("glUniform2iv");
}


void    glw::ShaderProgram::setUniform2fv (const std::string& name, GLsizei count, float *value)
{
	glUniform2fv(glGetUniformLocation(this->_program, name.c_str()), count, value);
	//GLW_ERROR("glUniform2fv");
}


void    glw::ShaderProgram::setUniform2dv (const std::string& name, GLsizei count, double *value)
{
	glUniform2dv(glGetUniformLocation(this->_program, name.c_str()), count, value);
	//GLW_ERROR("glUniform2dv");
}


void    glw::ShaderProgram::setUniform2uiv(const std::string& name, GLsizei count, unsigned int *value)
{
	glUniform2uiv(glGetUniformLocation(this->_program, name.c_str()), count, value);
	//GLW_ERROR("glUniform2ui");
}


void    glw::ShaderProgram::setUniform3iv (const std::string& name, GLsizei count, int *value)
{
	glUniform3iv(glGetUniformLocation(this->_program, name.c_str()), count, value);
	//GLW_ERROR("glUniform3iv");
}


void    glw::ShaderProgram::setUniform3fv (const std::string& name, GLsizei count, float *value)
{
	glUniform3fv(glGetUniformLocation(this->_program, name.c_str()), count, value);
	//GLW_ERROR("glUniform3fv");
}


void    glw::ShaderProgram::setUniform3dv (const std::string& name, GLsizei count, double *value)
{
	glUniform3dv(glGetUniformLocation(this->_program, name.c_str()), count, value);
	//GLW_ERROR("glUniform3dv");
}


void    glw::ShaderProgram::setUniform3uiv(const std::string& name, GLsizei count, unsigned int *value)
{
	glUniform3uiv(glGetUniformLocation(this->_program, name.c_str()), count, value);
	//GLW_ERROR("glUniform3ui");
}


void    glw::ShaderProgram::setUniform4iv (const std::string& name, GLsizei count, int *value)
{
	glUniform4iv(glGetUniformLocation(this->_program, name.c_str()), count, value);
	//GLW_ERROR("glUniform4iv");
}


void    glw::ShaderProgram::setUniform4fv (const std::string& name, GLsizei count, float *value)
{
	glUniform4fv(glGetUniformLocation(this->_program, name.c_str()), count, value);
	//GLW_ERROR("glUniform4fv");
}


void    glw::ShaderProgram::setUniform4dv (const std::string& name, GLsizei count, double *value)
{
	glUniform4dv(glGetUniformLocation(this->_program, name.c_str()), count, value);
	//GLW_ERROR("glUniform4dv");
}


void    glw::ShaderProgram::setUniform4uiv(const std::string& name, GLsizei count, unsigned int *value)
{
	glUniform4uiv(glGetUniformLocation(this->_program, name.c_str()), count, value);
	//GLW_ERROR("glUniform4ui");
}

/*
void    glw::ShaderProgram::setUniformMatrix2dv(const std::string &name, glm::mat2 mat, GLsizei count, GLenum transpose)
{
	glUniformMatrix2dv(glGetUniformLocation(this->_program, name.c_str()), count, transpose, glm::value_ptr(mat));
}*/

void    glw::ShaderProgram::setUniformMatrix2fv(const std::string &name, glm::mat2 mat, GLsizei count, GLenum transpose)
{
	glUniformMatrix2fv(glGetUniformLocation(this->_program, name.c_str()), count, transpose, glm::value_ptr(mat));
}
/*
void    glw::ShaderProgram::setUniformMatrix3dv(const std::string &name, glm::mat3 mat, GLsizei count, GLenum transpose)
{
	glUniformMatrix3dv(glGetUniformLocation(this->_program, name.c_str()), count, transpose, glm::value_ptr(mat));
}*/

void    glw::ShaderProgram::setUniformMatrix3fv(const std::string &name, glm::mat3 mat, GLsizei count, GLenum transpose)
{
	glUniformMatrix3fv(glGetUniformLocation(this->_program, name.c_str()), count, transpose, glm::value_ptr(mat));
}
/*
void    glw::ShaderProgram::setUniformMatrix4dv(const std::string &name, glm::mat4 mat, GLsizei count, GLenum transpose)
{
	glUniformMatrix4dv(glGetUniformLocation(this->_program, name.c_str()), count, transpose, glm::value_ptr(mat));
}*/

void    glw::ShaderProgram::setUniformMatrix4fv(const std::string &name, glm::mat4 mat, GLsizei count, GLenum transpose)
{
	glUniformMatrix4fv(glGetUniformLocation(this->_program, name.c_str()), count, transpose, glm::value_ptr(mat));
}

