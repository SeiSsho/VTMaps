//
// Created by tts on 4/23/2024.
//

#include "Transform.h"

glm::vec3* Engine::Transform::GetPosition() {
    return &_position;
}

void Engine::Transform::SetPosition(const glm::vec3 &position) {
    _position = position;
}

glm::vec3* Engine::Transform::GetScale() {
    return &_scale;
}

void Engine::Transform::SetScale(const glm::vec3 &scale) {
    _scale = scale;
}

glm::vec3* Engine::Transform::GetEulerAngles() const {
//    return _eulerAngles;
}

void Engine::Transform::SetEulerAngles(const glm::vec3 &eulerAngles) {
//    _eulerAngles = eulerAngles;
}

Engine::Transform::Transform()
: _position(0), _scale(1.0), _rotation(0.0, 0.0, 0.0, 0.0) {

}

Engine::Transform::Transform(const glm::vec3 &position, const glm::vec3 &scale,
                             const glm::quat &rotation)
                             : _position(position), _scale(scale), _rotation(rotation) {}

glm::vec3 Engine::Transform::forward() const {
    return _rotation * glm::vec3(0.0f, 0.0f, 1.0f);
}

glm::vec3 Engine::Transform::up() const {
    return _rotation * glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::vec3 Engine::Transform::right() const {
    return _rotation * glm::vec3(1.0f, 0.0f, 0.0f);
}

glm::vec3 Engine::Transform::GetPosition() const {
    return _position;
}

glm::vec3 Engine::Transform::GetScale() const {
    return _scale;
}

glm::quat *Engine::Transform::GetQuaternion() {
    return &_rotation;
}

void Engine::Transform::SetQuaternion(const glm::quat &quaternion) {
    _rotation = quaternion;
}
