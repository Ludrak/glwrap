
#ifndef GLWCAMERA_HPP
# define GLWCAMERA_HPP

# include "glm/glm.hpp"
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>
# include <glm/gtc/quaternion.hpp>
# include "GL/glew.h"

namespace glw
{
    enum  CameraMode
    {
        ORTHOGRAPHIC,
        PERSPECTIVE  
    };

    class Camera
    {
        public:
            Camera();
            ~Camera();

            void        rotate(const glm::vec3 rotation_amount);
            void        move(const glm::vec3 direction, const float speed);

            void        rotateTo(const glm::vec3 rotation);
            void        moveTo(const glm::vec3 position);

            void        lookAt(const glm::vec3 position, const glm::vec3 up_vector=glm::vec3(0.0f, 1.0f, 0.0f));


            void        setFov(const GLfloat fov);
            void        setMode(const CameraMode mode);
            
            GLfloat     getFov(void);
            CameraMode  getMode(void);
            glm::vec3   getPosition();
            glm::vec3   getDirection();

            glm::mat4   getViewMatrix();

        private:
            GLfloat     _fov;
            CameraMode  _mode;

            glm::vec3   _position;
            glm::vec3   _direction;

            glm::vec3   _front;
            glm::vec3   _up;

            glm::mat4   _view;
    };
}

#endif