#ifndef VTMAPS_SPHERE_H
#define VTMAPS_SPHERE_H

#include <vector>

#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <GLES3/gl3ext.h>
#include <jni.h>

#include <glm/glm.hpp>
#include "Material/Material.h"
#include "Mesh.h"
#include "Camera.h"

class Sphere {
public :
    enum DrawMode {
        Points,
        Lines,
        LineLoop,
        LineStrip,
        Triangles,
        TriangleStrip,
        TriangleFan,
    };

    static GLenum DrawModeToGL(const DrawMode& drawMode);

private:
    Material* _material;
    std::vector<Mesh*> _meshes;

    struct Transform {
        glm::vec3 position = glm::vec3(0.0);
        glm::vec3 scale = glm::vec3(1.0);
        glm::quat rotation = glm::quat();

        glm::mat4 GetMatrix() const {
            glm::mat4 positionMtx = glm::translate(glm::mat4(1.0), position);
            glm::mat4 scaleMtx = glm::scale(glm::mat4(1.0), scale);
            glm::mat4 rotationMtx = glm::toMat4(rotation);
            return positionMtx * rotationMtx * scaleMtx;
        }
    } _transform;
public:
    Sphere(Material* material);
    ~Sphere() = default;

    void Draw(Camera& camera);
};


#endif //VTMAPS_SPHERE_H
