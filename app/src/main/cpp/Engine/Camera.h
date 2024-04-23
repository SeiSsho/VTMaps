//
// Created by tts on 4/19/2024.
//

#ifndef VTMAPS_CAMERA_H
#define VTMAPS_CAMERA_H

#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Component/Transform.h"

namespace Engine {
    class Camera {
    public:
        enum class Projection {
            Ortho = 0,
            Frustrum,
            Perspective
        };
    private:
        Projection _projection;
        int _width, _height;
        float _fov;
        float _near, _far;
        Transform _transform;

    public:
        Camera(int width, int height, const glm::vec3& position,
               const glm::vec3& eulerAngles,
               const Projection& projection = Projection::Frustrum,
               float fov = 45.0f,
               float nearClipping = 0.0001f,
               float farClipping = 10.0f);

        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;

        /// Set the fov of camera, it will be convert to radians
        /// \param fov Euler angles
        void SetFov(float fov);
        /// Get fov of camera in euler angle
        /// \return fov of Camera
        float GetFov() const;

        void SetProjection(const Projection& projection);
        Projection GetProjection() const;

        void SetWidth(int width);
        void SetHeight(int height);

        int GetWidth() const;
        int GetHeight() const;

        Transform* GetTransform();
    };
}

#endif //VTMAPS_CAMERA_H
