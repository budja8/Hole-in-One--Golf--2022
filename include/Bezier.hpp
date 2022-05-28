#ifndef BEZIER_H
#define BEZIER_H

#include <vector>
#include "Vertex.hpp"

#pragma once

using namespace std;

class Bezier
{
public:
    Bezier(Vertex P1, Vertex P2, Vertex P3, Vertex P4);
    vector<Vertex> curva();
private:
    vector<Vertex> pcurva;


};
#endif
