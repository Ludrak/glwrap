
#include "VertexArray.hpp"

glw::VertexArray::VertexArray()
:   
    _buffers(),
    _bound_buffer(NULL)
{
}

glw::VertexArray::VertexArray(const VertexArray &copy)
:   _vao(copy._vao),
    _buffers(copy._buffers),
    _bound_buffer(copy._bound_buffer)
{

}


glw::VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &this->_vao);
}


void    glw::VertexArray::create()
{
	glGenVertexArrays(1, &this->_vao);
    GLW_ERROR("glGenVertexArrays", 1 << ", " << &this->_vao);
}


void            glw::VertexArray::bind(void)
{
    glBindVertexArray(this->_vao);
    GLW_ERROR("glBindVertexArray", this->_vao);
}


void            glw::VertexArray::bindBuffer(GLenum target, GLuint idx)
{
    if (this->_buffers.count(idx) == 0)
    {
        LOG_ERROR("Unable to bind buffer " << idx <<" of vao " << this->_vao);
        return ;
    }
    glBindBuffer(target, this->_buffers[idx]->id);
    GLW_ERROR("glBindBuffer", target << ", " << this->_buffers[idx]->id);
    this->_bound_buffer = this->_buffers[idx];
}


void            glw::VertexArray::attribPointer(GLuint location, GLint size, GLuint stride, GLulong offset, GLboolean normalized)
{
    if (!this->_bound_buffer)
    {
        LOG_ERROR("Can't set attrib pointer to unbound buffer of vao " << this->_vao);
        return ;
    }
    GLintptr off = offset * this->_bound_buffer->type_size;
	glVertexAttribPointer(location, size, this->_bound_buffer->type, normalized, stride * this->_bound_buffer->type_size, (GLvoid*)(off));
    GLW_ERROR("glVertexAttribPointer", location << ", " << size << ", " << this->_bound_buffer->type << ", " << normalized << ", " << stride * this->_bound_buffer->type_size << ", " << (GLvoid*)(off));
}


void            glw::VertexArray::enableAttrib(GLuint location)
{
    if (!this->_bound_buffer)
    {
        LOG_ERROR("Can't enable attrib array to unbound buffer of vao " << this->_vao);
        return ;
    }
	glEnableVertexAttribArray(location);
    GLW_ERROR("glEnableVertexAttribArray", location);
}


void            glw::VertexArray::disableAttrib(GLuint location)
{
    if (!this->_bound_buffer)
    {
        LOG_ERROR("Can't disable attrib array to unbound buffer of vao " << this->_vao);
        return ;
    }
	glDisableVertexAttribArray(location);
    GLW_ERROR("glDisableVertexAttribArray", location);
}


void    glw::VertexArray::draw()
{
    this->bind();
	glDrawElements(GL_TRIANGLES, this->_buffers[this->_indices_buffer]->size, GL_UNSIGNED_SHORT, (void*)0);
    GLW_ERROR("glDrawElements", GL_TRIANGLES << ", " << 6 << ", " << GL_UNSIGNED_SHORT << ", " << (void*)0);
}
