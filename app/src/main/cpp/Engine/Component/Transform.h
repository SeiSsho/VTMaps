//
// Created by tts on 4/23/2024.
//

#ifndef VTMAPS_TRANSFORM_H
#define VTMAPS_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>

namespace Engine {
    class Transform {
        friend class Camera;
    private:
        glm::vec3 _position;
        glm::vec3 _scale;
        glm::quat _rotation;
    public:
        Transform();
        Transform(const glm::vec3& position, const glm::vec3& scale, const glm::quat& rotation);

        glm::vec3* GetPosition();
        glm::vec3 GetPosition() const;
        void SetPosition(const glm::vec3 &position);

        glm::vec3* GetScale();
        glm::vec3 GetScale() const;
        void SetScale(const glm::vec3 &scale);

        glm::vec3* GetEulerAngles() const;
        void SetEulerAngles(const glm::vec3 &eulerAngles);

        glm::quat* GetQuaternion();
        void SetQuaternion(const glm::quat& quaternion);

        glm::vec3 forward() const;
        glm::vec3 up() const;
        glm::vec3 right() const;
    };
}



#endif //VTMAPS_TRANSFORM_H
