//
// Created by tts on 4/2/2024.
//

#ifndef VTMAPS_MESH_H
#define VTMAPS_MESH_H

#include <vector>

#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <GLES3/gl3ext.h>

#include "Vertex.h"


class Mesh
{
    friend class Renderer;
public:
    // TODO: should make a static/dynamic buffer
    // Here just static buffer
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    ~Mesh();
    /**
     * Draw the mesh. Please bind shader before call Draw.
     */
    void Draw();

    void Clean();
private:
    GLuint						_vao;
    GLuint						_vbo;
    GLuint						_ebo;
    unsigned int _vboSize, _eboSize;
//    std::vector<Vertex>			_vertices;
//    std::vector<unsigned int>	_indices;
};


#endif //VTMAPS_MESH_H
