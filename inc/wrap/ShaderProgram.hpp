
#ifndef GLWSHADERPROGRAM_HPP
# define GLWSHADERPROGRAM_HPP

# include "util/utils.hpp"

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>
# include <GL/glew.h>

# include <vector>
# include <iostream>
# include <fstream>
# include <sstream>

namespace glw
{
    class ShaderProgram
    {
        public:
            ShaderProgram();
            ShaderProgram(const std::string &name);
            ~ShaderProgram();

            void    use() const;
            void    create();
            int     addShader(const std::string& shader_source, GLenum shader_type);
            int     addShaderFromFile(const std::string& shaderfile_path, GLenum shader_type);
            int     link();
            void    erase();

            void    setUniform1i  (const std::string& name, int value);
            void    setUniform1ui (const std::string& name, unsigned int value);
            void    setUniform1d  (const std::string& name, double value);
            void    setUniform1f  (const std::string& name, float value);

            void    setUniform2i  (const std::string& name, int value1, int value2);
            void    setUniform2ui (const std::string& name, unsigned int value1, unsigned int value2);
            void    setUniform2d  (const std::string& name, double value1, double value2);
            void    setUniform2f  (const std::string& name, float value1, float value2);

            void    setUniform3i  (const std::string& name, int value1, int value2, int value3);
            void    setUniform3ui (const std::string& name, unsigned int value1, unsigned int value2, unsigned int value3);
            void    setUniform3d  (const std::string& name, double value1, double value2, double value3);
            void    setUniform3f  (const std::string& name, float value1, float value2, float value3);
            
            void    setUniform4i  (const std::string& name, int value1, int value2, int value3, int value4);
            void    setUniform4ui (const std::string& name, unsigned int value1, unsigned int value2, unsigned int value3, unsigned int value4);
            void    setUniform4d  (const std::string& name, double value1, double value2, double value3, double value4);
            void    setUniform4f  (const std::string& name, float value1, float value2, float value3, float value4);
      
            /* as vectors */
            void    setUniform1iv (const std::string& name, GLsizei count, int *value);
            void    setUniform1fv (const std::string& name, GLsizei count, float *value);
            void    setUniform1dv (const std::string& name, GLsizei count, double *value);
            void    setUniform1uiv(const std::string& name, GLsizei count, unsigned int *value);
            void    setUniform2iv (const std::string& name, GLsizei count, int *value);
            void    setUniform2fv (const std::string& name, GLsizei count, float *value);
            void    setUniform2dv (const std::string& name, GLsizei count, double *value);
            void    setUniform2uiv(const std::string& name, GLsizei count, unsigned int *value);
            void    setUniform3iv (const std::string& name, GLsizei count, int *value);
            void    setUniform3fv (const std::string& name, GLsizei count, float *value);
            void    setUniform3dv (const std::string& name, GLsizei count, double *value);
            void    setUniform3uiv(const std::string& name, GLsizei count, unsigned int *value);
            void    setUniform4iv (const std::string& name, GLsizei count, int *value);
            void    setUniform4fv (const std::string& name, GLsizei count, float *value);
            void    setUniform4dv (const std::string& name, GLsizei count, double *value);
            void    setUniform4uiv(const std::string& name, GLsizei count, unsigned int *value);

            void    setUniformMatrix2dv(const std::string &name, glm::mat2 mat, GLsizei count, GLenum transpose=GL_FALSE);
            void    setUniformMatrix2fv(const std::string &name, glm::mat2 mat, GLsizei count, GLenum transpose=GL_FALSE);

            void    setUniformMatrix2x3dv(const std::string &name, glm::mat2x3 mat, GLsizei count, GLenum transpose=GL_FALSE);
            void    setUniformMatrix2x3fv(const std::string &name, glm::mat2x3 mat, GLsizei count, GLenum transpose=GL_FALSE);

            void    setUniformMatrix2x4dv(const std::string &name, glm::mat2x4 mat, GLsizei count, GLenum transpose=GL_FALSE);
            void    setUniformMatrix2x4fv(const std::string &name, glm::mat2x4 mat, GLsizei count, GLenum transpose=GL_FALSE);

            void    setUniformMatrix3dv(const std::string &name, glm::mat3 mat, GLsizei count, GLenum transpose=GL_FALSE);
            void    setUniformMatrix3fv(const std::string &name, glm::mat3 mat, GLsizei count, GLenum transpose=GL_FALSE);

            void    setUniformMatrix3x2dv(const std::string &name, glm::mat3x2 mat, GLsizei count, GLenum transpose=GL_FALSE);
            void    setUniformMatrix3x2fv(const std::string &name, glm::mat3x2 mat, GLsizei count, GLenum transpose=GL_FALSE);

            void    setUniformMatrix3x4dv(const std::string &name, glm::mat3x4 mat, GLsizei count, GLenum transpose=GL_FALSE);
            void    setUniformMatrix3x4fv(const std::string &name, glm::mat3x4 mat, GLsizei count, GLenum transpose=GL_FALSE);

            void    setUniformMatrix4dv(const std::string &name, glm::mat4 mat, GLsizei count, GLenum transpose=GL_FALSE);
            void    setUniformMatrix4fv(const std::string &name, glm::mat4 mat, GLsizei count, GLenum transpose=GL_FALSE);

            void    setUniformMatrix4x2dv(const std::string &name, glm::mat4x2 mat, GLsizei count, GLenum transpose=GL_FALSE);
            void    setUniformMatrix4x2fv(const std::string &name, glm::mat4x2 mat, GLsizei count, GLenum transpose=GL_FALSE);

            void    setUniformMatrix4x3dv(const std::string &name, glm::mat4x3 mat, GLsizei count, GLenum transpose=GL_FALSE);
            void    setUniformMatrix4x3fv(const std::string &name, glm::mat4x3 mat, GLsizei count, GLenum transpose=GL_FALSE);

        private:
            GLuint              _program;
            std::string         _name;

            std::vector<GLuint> _shaders;
    };
}

#endif
