#ifndef BALL_H
#define BALL_H
#include "Object.hpp"
#include "Transformaciones.hpp"
#include <armadillo>

#pragma once

class Ball : public Object {
public:
    Ball(string file, float r, float g, float b, float ka, float kd, Vertex V1, Vertex V2);
    void setTransf(arma::Mat<double> transf);
    void draw(float Ia, float Ip, arma::frowvec3 F);
    vector<Vertex> start();
    Vertex getPosInit();
    Vertex getPosFin();
private:
    float r, g, b, ka, kd;
    Vertex V1;
    Vertex V2;
    int pos_curva;
    vector<Vertex> curve;
    arma::Mat<double> matrix;
    Transformaciones Tr = Transformaciones();
    arma::Mat<double> Sb;
};

#endif