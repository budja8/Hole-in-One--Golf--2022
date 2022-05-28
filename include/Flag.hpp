#ifndef FLAG_H
#define FLAG_H
#include "Object.hpp"
#include "Transformaciones.hpp"
#include <armadillo>
#pragma once

class Flag : public Object {
public:
    Flag(string file, Vertex pos, float r, float g, float b, float ka, float kd);
    void setTransf(arma::Mat<double> transf);
    void draw(float Ia, float Ip, arma::frowvec3 F);
private:
    arma::Mat<double> matrix;
    float r, g, b, ka, kd;
    Transformaciones Tr = Transformaciones();
    arma::Mat<double> Sf;
    arma::Mat<double> Rf;
    arma::Mat<double> Tf;
};

#endif