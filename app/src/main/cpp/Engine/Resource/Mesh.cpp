//
// Created by tts on 4/19/2024.
//

#include "Mesh.h"

Engine::Mesh::Mesh(std::vector<float> &verticeDatas, std::vector<unsigned int> &indices)
    : _vboSize(static_cast<GLsizei>(verticeDatas.size())),
      _eboSize(static_cast<GLsizei>(indices.size())) {
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);

    glBindVertexArray(_vao);

    constexpr int sizeOfVertex = sizeof(Vertex);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, verticeDatas.size() * sizeOfVertex, verticeDatas.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _eboSize * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeOfVertex, (void*) offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    // Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeOfVertex, (void*) offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    // UV
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeOfVertex, (void*) offsetof(Vertex, uv));
    glEnableVertexAttribArray(2);

    // Unbind to avoid modified
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Engine::Mesh::Draw() const {
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _eboSize, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Engine::Mesh::Clean() {
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
}

Engine::Mesh::~Mesh() {
    Clean();
}
