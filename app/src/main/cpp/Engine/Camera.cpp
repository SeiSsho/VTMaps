//
// Created by tts on 4/19/2024.
//

#include "Camera.h"

Engine::Camera::Camera(int width, int height, const glm::vec3 &position,
                       const glm::vec3 &eulerAngles, const Engine::Camera::Projection &projection,
                       float fov, float nearClipping, float farClipping) {

}

glm::mat4 Engine::Camera::GetViewMatrix() const {
    return glm::lookAt(_transform._position, _transform._position + _transform.forward(), _transform.up());
}

glm::mat4 Engine::Camera::GetProjectionMatrix() const {
    float ratio = 1.0 * _width / _height;
    switch (_projection) {
        case Projection::Perspective:   return glm::perspective(_fov, ratio, _near, _far);
        case Projection::Frustrum:      return glm::frustum(0.0f, ratio, 0.0f, 1.0f, _near, _far);
        case Projection::Ortho:         return glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, _near, _far);
    }
}

void Engine::Camera::SetProjection(const Engine::Camera::Projection &projection) {
    _projection = projection;
}

Engine::Camera::Projection Engine::Camera::GetProjection() const {
    return Engine::Camera::Projection::Ortho;
}

void Engine::Camera::SetWidth(int width) {
    _width = width;
}

void Engine::Camera::SetHeight(int height) {
    _height = height;
}

Engine::Transform* Engine::Camera::GetTransform() {
    return &_transform;
}

int Engine::Camera::GetWidth() const {
    return _width;
}

int Engine::Camera::GetHeight() const {
    return _height;
}

void Engine::Camera::SetFov(float fov) {

}

float Engine::Camera::GetFov() const {
    return 0;
}
