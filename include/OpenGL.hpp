#ifndef OPENGL_H
#define OPENGL_H
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "Vertex.hpp"
#include <string>

#pragma once

class OpenGL
{
public:
    OpenGL();
    int start();
private:
    void info();
    Vertex Pi;
    Vertex Pf;
    Vertex getVertex(Vertex P);
    float validate(float var);
};

#endif
