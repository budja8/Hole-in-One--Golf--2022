#include "../include/Ball.hpp"
#include "../include/Line.hpp"
#include "../include/Bezier.hpp"
#include <GL/glu.h>

Ball::Ball(string file, float r, float g, float b, float ka, float kd, Vertex V1, Vertex V2) : Object(file)
{
    // Matrix identidad (diagonales en 1)
    this->matrix = arma::eye(4, 4);
    this->V1 = V1;
    this->V2 = V2;
    this->Sb = Tr.S(0.3, 0.3, 0.3);
    this->r = r;
    this->g = g;
    this->b = b;
    this->ka = ka;
    this->kd = kd;
}

void Ball::setTransf(arma::Mat<double> transf){
     this->matrix = transf * Sb;
}

vector<Vertex> Ball::start(){
    double t = 1.0;
    this->pos_curva = 0;

    Vertex P1 = this->V1;
    Line l;
    Vertex P2 = this->V2;
    Vertex P3(P2.getX()*-1, P2.getY(), P2.getZ()*-1);
    Vertex P4(P1.getX()*-1, P1.getY(), P1.getZ()*-1);

    Bezier bz(P1, P2, P3, P4);
    this->curve = bz.curva();

    return bz.curva();
}

Vertex Ball::getPosInit(){
    return this->V1;
}

Vertex Ball::getPosFin(){
    Vertex P4(this->V1.getX()*-1, this->V1.getY(), this->V1.getZ()*-1);
    return P4;
}

void Ball::draw(float Ia, float Ip, arma::frowvec3 F){
    // Dibujar Pelota de golf
    arma::Mat<double> Tb = Tr.T(this->curve[this->pos_curva].getX(),
                                this->curve[this->pos_curva].getY(),
                                this->curve[this->pos_curva].getZ());

    if(this->pos_curva < this->curve.size()-1){
        this->pos_curva++;
    }

    this->matrix = Tb * Sb;
    vector<Face> ball_faces = getFaces();
    vector<Vertex> ball_vertices = getVertex();
                
    glBegin(GL_TRIANGLES);
    for (Face f : ball_faces)
    {
        arma::frowvec3 N = f.getNormal();
        arma::frowvec3 V = {ball_vertices[f.getIndVertex()[0]].getX(),
                            ball_vertices[f.getIndVertex()[0]].getY(),
                            ball_vertices[f.getIndVertex()[0]].getZ()};
        arma::frowvec3 L = F - V;
        L = arma::normalise(L);
        float costheta = arma::dot(N, L);
        float I = (Ia * this->ka) + (Ip * this->kd * costheta);

        float rl = this->r * I;
        float gl = this->g * I;
        float bl = this->b * I;

        glColor3f(rl, gl, bl);
        // Recorrer los vértices de la cara
        for (long v_ind : f.getIndVertex())
        {
            // Dibujar el objeto....
            arma::Col<double> vp = this->matrix * ball_vertices[v_ind].homg();
            glVertex3f(vp.at(0), vp.at(1), vp.at(2));
        }
    }
    glEnd();
    // Fin dibujado de Pelota de golf
}

