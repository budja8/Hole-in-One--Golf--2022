#ifndef OBJECT_H
#define OBJECT_H
#pragma once

#include <string>
#include <vector>
#include "Vertex.hpp"
#include "Face.hpp"

using namespace std;

class Object
{
    private:
        vector<Face> faces;
        vector<Vertex> vertices;
        vector<string> split(const string& str, const string& delim);
    public:
        Object();
        Object(string file);
        vector<Face> getFaces();
        vector<Vertex> getVertex();
        void print();
};
#endif