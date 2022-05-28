#include <iostream>
#include "../include/Vertex.hpp"  

using namespace std;

Vertex::Vertex(){

}

Vertex::Vertex(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

float Vertex::getX(){
    return(this->x);
}

float Vertex::getY(){
    return(this->y);
}

float Vertex::getZ(){
    return(this->z);
}

void Vertex::print(){
    cout << this->x << " " << this->y << " " << this->z  << endl;
}

arma::Col<double> Vertex::homg()
{
    arma::Col<double> h = {this->x, this->y, this->z, 1};
    
    return(h);

}