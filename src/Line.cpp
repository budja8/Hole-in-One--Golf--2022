#include "../include/Line.hpp"

Line::Line()
{

}

Vertex Line::line_t(Vertex v1, Vertex v2, double t)
{
    float x = v1.getX() + t * (v2.getX() - v1.getX());
    float y = v1.getY() + t * (v2.getY() - v1.getY());
    float z = v1.getZ() + t * (v2.getZ() - v1.getZ());

    return(Vertex(x,y,z));

}
