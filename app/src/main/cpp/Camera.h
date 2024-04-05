//
// Created by tts on 4/2/2024.
//

#ifndef VTMAPS_CAMERA_H
#define VTMAPS_CAMERA_H

#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class Camera {
public:
    enum class Projection {
        Ortho = 0,
        Frustrum = 1,
        Perspective = 2
    };

private:
    int _width, _height;
    Projection _projection;
    glm::vec3 _position;
    glm::quat _rotation;
    float _fov;
    float _nearClipping, _farClipping;
public:
    Camera(int width, int height, const glm::vec3& position,
           const glm::vec3& eulerAngles,
           const Projection& projection = Projection::Frustrum,
           float fov = 45.0f,
           float nearClipping = 0.0001f,
           float farClipping = 10.0f);

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

    void SetProjection(const Projection& projection);
    Projection GetProjection() const;

    glm::vec3 GetPosition() const;
    void SetPosition(const glm::vec3& position);
    glm::quat GetQuaternionRotation() const;
    glm::vec3 GetEulerRotation() const;

    void SetWidth(int width);
    void SetHeight(int height);
};


#endif //VTMAPS_CAMERA_H
