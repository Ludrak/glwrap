
//#define STB_IMAGE_IMPLEMENTATION
#include "Texture.hpp"

glw::Texture::Texture()
:   _tex(0),
    _tex_target(GL_TEXTURE_2D),
    _width(0),
    _height(0),
    _n_channels(0)
{
    
}

glw::Texture::~Texture()
{
    
}


bool    glw::Texture::load(const std::string& filename, GLenum target)
{
    this->_tex_target = target;
    unsigned char* data = stbi_load(filename.c_str(), &this->_width, &this->_height, &this->_n_channels, 0);
    if (!data)
    {
        LOG_ERROR("unable to load texture: " << filename);
        return (false);
    }

    glGenTextures(1, &this->_tex);
    GLW_ERROR("glGenTextures", 1 << ", " << &this->_tex)
    
    this->bind();
    glTexImage2D(target, 0, GL_RGB, this->_width, this->_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    GLW_ERROR("glTexImage2D", target << ", " << 0 << ", " << GL_RGB << ", " << this->_width << ", " << this->_height << ", " << 0 << ", " << GL_RGB << ", " << GL_UNSIGNED_BYTE << ", " << data)

    stbi_image_free(data);
    return (true);
}

void    glw::Texture::paramWrap(GLenum s_wrap, GLenum t_wrap)
{
    glTexParameteri(this->_tex_target, GL_TEXTURE_WRAP_S, s_wrap);
    GLW_ERROR("glTexParameteri", this->_tex_target << ", " << GL_TEXTURE_WRAP_S << ", " << s_wrap)
    glTexParameteri(this->_tex_target, GL_TEXTURE_WRAP_T, t_wrap);
    GLW_ERROR("glTexParameteri", this->_tex_target << ", " << GL_TEXTURE_WRAP_T << ", " << t_wrap)
}

void    glw::Texture::paramFilter(GLenum min_filter, GLenum mag_filter)
{
    glTexParameteri(this->_tex_target, GL_TEXTURE_MAG_FILTER, mag_filter);
    GLW_ERROR("glTexParameteri", GL_TEXTURE_MAG_FILTER << ", " << mag_filter)
    glTexParameteri(this->_tex_target, GL_TEXTURE_MIN_FILTER, min_filter);
    GLW_ERROR("glTexParameteri", GL_TEXTURE_MIN_FILTER << ", " << min_filter)
}


void    glw::Texture::activate(GLenum texture_id)
{
    if (texture_id >= GL_MAX_TEXTURE_UNITS)
    {
        LOG_ERROR("texture unit overflow: loading texture: GL_TEXTURE" << texture_id - GL_TEXTURE0 << " but maximum is " << GL_MAX_TEXTURE_UNITS - GL_TEXTURE0 - 1);
        return ;
    }
    glActiveTexture(texture_id);
    GLW_ERROR("glActiveTexture", texture_id)
    this->bind();
}

void    glw::Texture::generateMipmap(void)
{
    glGenerateMipmap(this->_tex_target);
    GLW_ERROR("glActiveTexture", this->_tex_target)
}


void    glw::Texture::bind(void)
{
    glBindTexture(this->_tex_target, this->_tex);
    GLW_ERROR("glBindTexture", this->_tex_target << ", " << this->_tex);
}