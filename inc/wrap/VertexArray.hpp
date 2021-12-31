
#ifndef GLWVERTEX_ARRAY_HPP
# define GLWVERTEX_ARRAY_HPP

# include "utils.hpp"
# include "ShaderProgram.hpp"
# include "Texture.hpp"

# include <GLFW/glfw3.h>
# include <map>

namespace glw
{
    class VertexArray
    {
        protected:
            typedef struct  s_vertex_buffer
            {
                GLint   id;
                GLenum  type;
                GLsizei type_size;
                GLsizei size;

                s_vertex_buffer(void)
                : id(0), type(0), type_size(0), size(0) { }

                s_vertex_buffer(GLint id, GLenum  type, GLsizei type_size, GLsizei size)
                : id(id), type(type), type_size(type_size), size(size) { }

                s_vertex_buffer(const struct s_vertex_buffer &copy)
                : id(copy.id), type(copy.type), type_size(copy.type_size), size(copy.size) { }

            }               VertexBuffer;

        public:
            VertexArray();
            VertexArray(const VertexArray &copy);
            virtual ~VertexArray(void);

            void            create(void);
            void            bind(void);
            void            bindBuffer(GLenum target, GLuint idx);

            template <typename T>
            GLuint          addBufferData(GLuint idx, GLenum target, GLenum type, T *data, GLsizei size, GLenum usage);

            void            attribPointer(GLuint location, GLint size, GLuint stride, GLulong offset, GLboolean normalized=GL_FALSE);
            void            enableAttrib(GLuint location);
            void            disableAttrib(GLuint location);

            void            addTexture(const Texture &tex);
            void            delTexture(const Texture &tex);

            void            setShader(ShaderProgram *shader);
            virtual void    onShaderUse(void);

            virtual void    draw(void);
        
        private:
            GLuint                          _vao;

            std::map<int, VertexBuffer*>    _buffers;
            VertexBuffer*                   _bound_buffer;

            ShaderProgram*                  _shader;
    };

    template <typename T>
    GLuint            VertexArray::addBufferData(GLuint idx, GLenum target, GLenum type, T *data, GLsizei size, GLenum usage)
    {
        if (this->_buffers.count(idx) != 0)
        {
            LOG_ERROR("Buffer " << idx << " of vao " << this->_vao << " was already assigned");
            return 0;
        }
        GLuint      buffered_data;
        glGenBuffers(idx, &buffered_data);
        GLW_ERROR("glGenBuffers", idx << ", " << &buffered_data);

        glBindBuffer(target, buffered_data);
        GLW_ERROR("glBindBuffer", target << ", " << buffered_data);

        glBufferData(target, size, (void*)data, usage);
        GLW_ERROR("glBufferData", target << ", " << size << ", " << (void*)data << ", " << usage);

        this->_buffers[idx] = new VertexBuffer(buffered_data, type, sizeof(T), size);
        return (buffered_data);
    }

}

#endif
