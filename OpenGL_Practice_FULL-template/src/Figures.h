#ifndef FIGURES_H
#define FIGURES_H

#include <glm.hpp>
#include "Vertex.h"

using namespace glm;

// данные о вершинах
int triangleVertexCount = 3;
int cubeVertexCount = 3 * 2 * 6;
Vertex triangleVertexes[] = {
    //                ВЕРШИНА                   ЦВЕТ
    Vertex(vec3( 0.0f,  1.0f,  0.0f),   vec3(0.5f, 0.8f, 0.5f)),
    Vertex(vec3(-1.0f, -1.0f,  1.0f),   vec3(0.5f, 0.8f, 0.5f)),
    Vertex(vec3( 1.0f, -1.0f,  1.0f),   vec3(0.5f, 0.8f, 0.5f))
};

Vertex cubeVertexes[] = {
    Vertex(vec3(0.5f, 0.5f, -0.5f), vec3(1.0f, 1.0f, 0.0f)),
    Vertex(vec3(-0.5f, 0.5f, -0.5f), vec3(1.0f, 0.0f, 1.0f)),
    Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3(0.2f, 0.8f, 0.6f)),

    Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3(0.24f, 0.985f, 0.3f)),
    Vertex(vec3(0.5f, -0.5f, -0.5f), vec3(0.8f, 0.7f, 0.5f)),
    Vertex(vec3(0.5f, 0.5f, -0.5f), vec3(0.25f, 0.89f, 0.7f)),


    Vertex(vec3(0.5f, 0.5f, -0.5f), vec3(0.42f, 0.88f, 0.23f)),
    Vertex(vec3(-0.5f, 0.5f, -0.5f), vec3(0.8f, 0.7f, 0.5f)),
    Vertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0.62f, 0.9f, 0.6f)),

    Vertex(vec3(0.5f, 0.5f, -0.5f), vec3(0.55f, 0.56f, 0.57f)),
    Vertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0.8f, 0.7f, 0.5f)),
    Vertex(vec3(0.5f, 0.5f, 0.5f), vec3(0.61f, 0.62f, 0.63f)),


    Vertex(vec3(0.5f, -0.5f, -0.5f), vec3(0.4f, 0.5f, 0.6f)),
    Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3(0.8f, 0.7f, 0.5f)),
    Vertex(vec3(-0.5f, -0.5f, 0.5f), vec3(0.1f, 0.2f, 0.3f)),

    Vertex(vec3(0.5f, -0.5f, -0.5f), vec3(0.4f, 0.5f, 0.6f)),
    Vertex(vec3(-0.5f, -0.5f, 0.5f), vec3(0.8f, 0.7f, 0.5f)),
    Vertex(vec3(0.5f, -0.5f, 0.5f), vec3(0.1f, 0.2f, 0.3f)),


    Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3(0.4f, 0.82f, 0.6f)),
    Vertex(vec3(-0.5f, 0.5f, -0.5f), vec3(0.8f, 0.7f, 0.5f)),
    Vertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0.6f, 0.6f, 0.9f)),

    Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3(0.3f, 0.15f, 0.9f)),
    Vertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0.8f, 0.7f, 0.5f)),
    Vertex(vec3(-0.5f, -0.5f, 0.5f), vec3(0.1f, 0.8f, 0.7f)),


    Vertex(vec3(0.5f, -0.5f, -0.5f), vec3(1.0f, 1.0f, 1.0f)),
    Vertex(vec3(0.5f, 0.5f, -0.5f), vec3(0.8f, 0.7f, 0.5f)),
    Vertex(vec3(0.5f, 0.5f, 0.5f), vec3(0.25f, 0.9f, 0.9f)),

    Vertex(vec3(0.5f, -0.5f, -0.5f), vec3(1.0f, 1.0f, 1.0f)),
    Vertex(vec3(0.5f, 0.5f, 0.5f), vec3(0.8f, 0.7f, 0.5f)),
    Vertex(vec3(0.5f, -0.5f, 0.5f), vec3(0.6f, 0.1f, 0.1f)),


    Vertex(vec3(0.5f, 0.5f, 0.5f), vec3(0.25f, 0.9f, 0.9f)),
    Vertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0.8f, 0.7f, 0.5f)),
    Vertex(vec3(-0.5f, -0.5f, 0.5f), vec3(0.1f, 0.0f, 0.7f)),

    Vertex(vec3(-0.5f, -0.5f, 0.5f), vec3(0.1f, 0.0f, 0.7f)),
    Vertex(vec3(0.5f, -0.5f, 0.5f), vec3(0.8f, 0.7f, 0.5f)),
    Vertex(vec3(0.5f, 0.5f, 0.5f), vec3(0.25f, 0.9f, 0.9f))
};

#endif
