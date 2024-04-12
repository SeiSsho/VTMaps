//
// Created by tts on 4/2/2024.
//

#include "Camera.h"

Camera::Camera(int width, int height,
               const glm::vec3 &position,
               const glm::vec3 &eulerAngles,
               const Projection& projection,
               float fov, float nearClipping, float farClipping)
: _width(width), _height(height),
  _projection(projection),
  _position(position),
  _rotation(glm::quat(glm::radians(eulerAngles))),
  _fov(fov), _nearClipping(nearClipping), _farClipping(farClipping) {
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(_position,
                       _position + glm::normalize(_rotation * glm::vec3(0.0, 0.0, 1.0)),
                       _rotation * glm::vec3(0.0, 1.0, 0.0));
}

glm::mat4 Camera::GetProjectionMatrix() const {
    float ratio = (float) _width / _height;
    switch (_projection) {
        case Projection::Perspective:
            return glm::perspective(glm::radians(_fov), ratio, _nearClipping, _farClipping);
        case Projection::Ortho:
            return glm::ortho(0.0f, ratio, 0.0f, 1.0f, _nearClipping, _farClipping);
        case Projection::Frustrum:
            return glm::frustum(-ratio, ratio, -1.0f, 1.0f, _nearClipping, _farClipping);
    }
}

glm::quat Camera::GetQuaternionRotation() const {
    return _rotation;
}

glm::vec3 Camera::GetEulerRotation() const {
    return glm::degrees(glm::eulerAngles(_rotation));
}

glm::vec3 Camera::GetPosition() const {
    return _position;
}

void Camera::SetPosition(const glm::vec3 &position) {
    _position = position;
}

void Camera::SetWidth(int width) {
    _width = width;
}

void Camera::SetHeight(int height) {
    _height = height;
}

void Camera::SetProjection(const Camera::Projection &projection) {
    _projection = projection;
}

Camera::Projection Camera::GetProjection() const {
    return _projection;
}

