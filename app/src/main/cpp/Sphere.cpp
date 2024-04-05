//
// Created by tts on 4/2/2024.
//

#include "Sphere.h"
#include "Vertex.h"
#include "Mesh.h"

Sphere::Sphere(Material* material) {
    _material = material;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    const unsigned int X_SEGMENTS = 64;
    const unsigned int Y_SEGMENTS = 64;
    const float PI = 3.14159265359f;
    for (unsigned int x = 0; x <= X_SEGMENTS; ++x) {
        for (unsigned int y = 0; y <= Y_SEGMENTS; ++y) {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

            vertices.push_back({
                glm::vec3(xPos, yPos, zPos),
                glm::vec3(xPos, yPos, zPos),
                glm::vec4(1.0),
                glm::vec2(xSegment, ySegment),
                glm::vec2(0.0)
                               });
        }
    }

    bool oddRow = false;
    for (unsigned int y = 0; y < Y_SEGMENTS; ++y) {
        if (!oddRow) /* even rows: y == 0, y == 2; and so on*/ {
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x) {
                indices.push_back(y * (X_SEGMENTS + 1) + x);
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
            }
        } else {
            for (int x = X_SEGMENTS; x >= 0; --x) {
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                indices.push_back(y * (X_SEGMENTS + 1) + x);
            }
        }
        oddRow = !oddRow;
    }

//    material->renderFace = Front;
//    std::vector<std::shared_ptr<Mesh>> meshes = { std::make_shared<Mesh>(vertices, indices) };
//    Renderer* r = this->AddComponent<Renderer>(material, meshes);
//    r->SetDrawMode(Renderer::DrawMode::TriangleStrip);
    _meshes = {new Mesh(vertices, indices)};

}

void Sphere::Draw(Camera &camera) {
    Shader* shader = _material->_shader.get();
    shader->Bind();
    _material->UpdateShader();
    // Update transform to render scene
    glm::mat4 mvp = camera.GetProjectionMatrix() * camera.GetViewMatrix() * _transform.GetMatrix();
    shader->SetMat4("uMVP", mvp);
    for(auto& mesh : _meshes) {
        mesh->Draw();
    }
    glBindVertexArray(0);
    shader->Unbind();
}
