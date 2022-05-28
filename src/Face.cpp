#include <iostream>
#include "../include/Face.hpp"  
#include "../include/Vertex.hpp"  
#include <armadillo>

using namespace std;

Face::Face(vector<unsigned int> vectex_indices){
    this->vectex_indices = vectex_indices;
}

void Face::print(){
    /*
    int salto = 0;
    for(int i=0; i<this->vectex_indices.size(); i++){
        salto++;
        cout << this->vectex_indices[i] << " ";
        if(salto==3){
            cout << endl;
            salto=0;
        }
    }
    */
    cout << "Ecuacion del plano: ";
    cout << this->A << "x + ";
    cout << this->B << "y + ";
    cout << this->C << "z + ";
    cout << this->D << " = 0" << endl;
    cout << endl;
}

vector<unsigned long> Face::getIndVertex(){
    int salto = 0;
    vector<unsigned long> lista;
    for(int i=0; i<this->vectex_indices.size(); i++){
        salto++;
        lista.push_back(vectex_indices[i]);
        if(salto==3){
            cout << endl;
            salto=0;
        }
    }
    return(lista);
}

void Face::calculatePlaneEcuation(Vertex v1, Vertex v2, Vertex v3){
    Vertex v2v1 = Vertex(v2.getX() - v1.getX(), v2.getY() - v1.getY(), v2.getZ() - v1.getZ());
    Vertex v3v1 = Vertex(v3.getX() - v1.getX(), v3.getY() - v1.getY(), v3.getZ() - v1.getZ());

    this->A = (v2v1.getY()*v3v1.getZ()) - (v2v1.getZ()*v3v1.getY());
    this->B = (v2v1.getZ()*v3v1.getX()) - (v2v1.getX()*v3v1.getZ());
    this->C = (v2v1.getX()*v3v1.getY()) - (v2v1.getY()*v3v1.getX());
    this->D = -((A*v1.getX()) + (B*v1.getY()) + (C*v1.getZ()));
}

arma::frowvec3 Face::getNormal(){
    arma::frowvec3 N = {this->A, this->B, this->C};
    N = arma::normalise(N);

    return N;
}