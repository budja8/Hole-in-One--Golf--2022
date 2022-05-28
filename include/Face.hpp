#ifndef FACE_H
#define FACE_H
#include <vector>
#include "Vertex.hpp"
#pragma once

using namespace std;

class Face  
{
	private:
		vector<unsigned int> vectex_indices;
		float A, B, C, D;
	public:
		Face(vector<unsigned int> vectex_indices);
		void print();
		vector<unsigned long> getIndVertex();
		void calculatePlaneEcuation(Vertex v1, Vertex v2, Vertex v3);
		arma::frowvec3 getNormal();

};
#endif