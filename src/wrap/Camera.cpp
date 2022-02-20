#include "Camera.hpp"

glw::Camera::Camera()
:  _fov(45.0f), _front(glm::vec3(1, 0, 0)), _up(glm::vec3(0, -1, 0)),  _view(glm::mat4(1))
{

}

void        glw::Camera::rotate(const glm::vec3 rotation)
{
    this->_front.x = cos(rotation.y) * cos(this->_front.x + rotation.x);
    this->_front.y = sin(rotation.x);
    this->_front.z = sin(rotation.y) * cos(this->_front.x + rotation.x);
    this->_front = glm::normalize(this->_front);
}

void        glw::Camera::move(const glm::vec3 direction, const float speed)
{
    this->_position += direction * speed;
}


void            glw::Camera::rotateTo(const glm::vec3 rotation)
{
    this->_front.x = cos(this->_front.y + rotation.y) * cos(this->_front.x + rotation.x);
    this->_front.y = sin(this->_front.x +rotation.x);
    this->_front.z = sin(this->_front.y + rotation.y) * cos(this->_front.x + rotation.x);
    this->_front = glm::normalize(this->_front);
}

void            glw::Camera::moveTo(const glm::vec3 position)
{
    this->_position = position;
}

void            glw::Camera::lookAt(const glm::vec3 position, const glm::vec3 up_vector)
{
    this->_view = glm::lookAt(this->_position, position, up_vector);
}


void            glw::Camera::setFov(const GLfloat fov)
{
    this->_fov = fov;
}

GLfloat         glw::Camera::getFov(void)
{
    return (this->_fov);
}


void            glw::Camera::setMode(const glw::CameraMode mode)
{
    this->_mode = mode;
}

glw::CameraMode glw::Camera::getMode(void)
{
    return (this->_mode);
}

glm::vec3       glw::Camera::getPosition()
{
    return (this->_position);
}

glm::vec3       glw::Camera::getDirection()
{
    return (this->_front);
}

glm::mat4       glw::Camera::getViewMatrix()
{
    this->_view = glm::lookAt(this->_position, this->_position + this->_front, this->_up);
    return (this->_view);
}