#ifndef LINE_H
#define LINE_H

#pragma once

#include "Line.hpp"
#include "Vertex.hpp"

class Line
{
public:
    Line();
    Vertex line_t(Vertex v1, Vertex v2, double t);

private:

};

#endif