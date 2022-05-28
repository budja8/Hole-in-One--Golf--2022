#include "../include/Putter.hpp"
#include <GL/glu.h>

Putter::Putter(string file, Vertex pos, float r, float g, float b, float ka, float kd) : Object(file)
{
    // Matrix identidad (diagonales en 1)
    this->matrix = arma::eye(4, 4);

    this->Sp = Tr.S(0.02, 0.02, 0.02);
    this->Tp = Tr.T(pos.getX(), pos.getY(), pos.getZ());
    this->Rp = Tr.Ry(180) * Tr.Rx(-90);

    this->matrix = Tp * Rp * Sp;
    this->r = r;
    this->g = g;
    this->b = b;
    this->ka = ka;
    this->kd = kd;
}

void Putter::setTransf(arma::Mat<double> transf){
     this->matrix = transf;
}

void Putter::draw(float Ia, float Ip, arma::frowvec3 F){
    // Dibujar Putter
    vector<Face> putter_faces = getFaces();
    vector<Vertex> putter_vertices = getVertex();
    
    glBegin(GL_TRIANGLES);
    for (Face f : putter_faces)
    {
        arma::frowvec3 N = f.getNormal();
        arma::frowvec3 V = {putter_vertices[f.getIndVertex()[0]].getX(),
                            putter_vertices[f.getIndVertex()[0]].getY(),
                            putter_vertices[f.getIndVertex()[0]].getZ()};
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
            arma::Col<double> vp = this->matrix * putter_vertices[v_ind].homg();
            glVertex3f(vp.at(0), vp.at(1), vp.at(2));
        }
    }
    glEnd();
    // Fin dibujado de Putter
}