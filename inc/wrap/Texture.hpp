
#ifndef  GLWTEXTURE_HPP
# define GLWTEXTURE_HPP

# include "utils.hpp"

# include <string>
# include <GL/glew.h>
# include <GLFW/glfw3.h>

//# ifndef STB_IMAGE_IMPLEMENTATION
//#  define STB_IMAGE_IMPLEMENTATION
# include "stbi_image.h"
//# endif

namespace glw
{
    class Texture
    {
        public:
            Texture();
            ~Texture();

            bool    load(const std::string& file_name, GLenum target=GL_TEXTURE_2D);
            void    paramWrap(GLenum s_wrap, GLenum t_wrap);
            void    paramFilter(GLenum min_filter, GLenum mag_filter);
            void    generateMipmap(void);
            
            void    bind(void);
            void    activate(GLenum texture_id);

        private:
            GLuint  _tex;
            GLenum  _tex_target;

            int     _width;
            int     _height;
            int     _n_channels;

    };
}

#endif