#ifndef VERTEX_H
#define VERTEX_H
#pragma once

#include <armadillo>

class Vertex{
    private:
        float x, y, z;
    public:
        Vertex();
        Vertex(float x, float y, float z);
        float getX();
        float getY();
        float getZ();
        void print();
        arma::Col<double> homg();  
};
#endif