#ifndef VTMAPS_MESH_H
#define VTMAPS_MESH_H

#include "../Core.h"
#include <vector>
#include <glm/glm.hpp>

namespace Engine {
    class Mesh {
    private:
        struct Vertex;
        GLuint _vao, _vbo, _ebo;
        GLsizei _vboSize, _eboSize;
    public:
        Mesh(std::vector<float>& verticeDatas, std::vector<unsigned int>& indices);
        ~Mesh();

        void Draw() const;
        void Clean();
    };

    struct Mesh::Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };
}

#endif //VTMAPS_MESH_H
