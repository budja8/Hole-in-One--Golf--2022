#include "../include/Bezier.hpp"
#include <armadillo>
#include <iostream>

using namespace std;

Bezier::Bezier(Vertex P1, Vertex P2, Vertex P3, Vertex P4)
{
    this->pcurva = {};

    double delta_t = 0.02;
    // Curvas de Bezier
    arma::Mat<double> MB = { {-1, 3, -3, 1},
                             {3, -6, 3, 0},
                             {-3, 3, 0, 0},
                             {1, 0, 0, 0}};

    arma::Mat<double> GB = {{P1.getX(), P1.getY(), P1.getZ()}, //P1
                            {P2.getX(), P2.getY(), P2.getZ()}, //P2
                            {P3.getX(), P3.getY(), P3.getZ()}, //P3
                            {P4.getX(), P4.getY(), P4.getZ()}}; //P4


    for(double t = 0.0; t <= 1.0; t += delta_t){
        arma::Row<double> T = {pow(t, 3), pow(t, 2), t, 1};
        arma::Row<double> Qt = T * MB * GB;
        this->pcurva.push_back(Vertex(Qt[0], Qt[1], Qt[2]));
    }
}


vector<Vertex> Bezier::curva()
{
    return(this->pcurva);
}