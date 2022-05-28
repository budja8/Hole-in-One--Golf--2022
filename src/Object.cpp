#include "../include/Object.hpp"  
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

Object::Object(){
    
}

Object::Object(string file)
{
    string line;
    vector<Vertex> vertices = {};
    vector<Face> faces = {};
    int counter = 0;

    ifstream archivoPLY(file);
    while (getline(archivoPLY, line))
    {
        counter++;        
        vector<string> elems = split(line, " ");

        if(!elems.empty())
        {
            if(elems[0].compare("3") == 0)
            {
                counter=0;
                //Construir Edges
                unsigned int i1 = stoi(split(elems[1], " ")[0]);
                unsigned int i2 = stoi(split(elems[2], " ")[0]);
                unsigned int i3 = stoi(split(elems[3], " ")[0]);
                vector<unsigned long> vertex_index = {stoul(elems[1]), stoul(elems[2]), stoul(elems[3])};
                
                //Construir Face
                Face f({i1, i2, i3});
                f.calculatePlaneEcuation(vertices[vertex_index[0]],
                                   vertices[vertex_index[1]],
                                   vertices[vertex_index[2]]);
                faces.push_back(f);
            }
            /*Uncomment if 3d model are not using triangles
            if(elems[0].compare("4") == 0)
            {
                counter=0;
                //Construir Edges
                unsigned int i1 = stoi(split(elems[1], " ")[0]);
                unsigned int i2 = stoi(split(elems[2], " ")[0]);
                unsigned int i3 = stoi(split(elems[3], " ")[0]);
                unsigned int i4 = stoi(split(elems[4], " ")[0]);
               
                //Construir Face
                Face f({i1, i2, i3, i4});
                faces.push_back(f);
            }
            */

            if(counter >= 11)
            {
                //Construir Vertex
                float x = stof(elems[0]);
                float y = stof(elems[1]);
                float z = stof(elems[2]);
                Vertex v(x, y, z);
                vertices.push_back(v);
            }
        }
    }

    this->vertices = vertices;
    this->faces = faces;
}

vector<string> Object::split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if(pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if(!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

void Object::print()
{
    /*
    cout << "ply" << endl;
    cout << "format ascii 1.0" << endl;
    cout << "comment Created by Blender - www.blender.org" << endl;
    cout << "element vertex " << vertices.size() << endl;
    cout << "property floax x" << endl;
    cout << "property floax y" << endl;
    cout << "property floax z" << endl;
    cout << "elemet face " << faces.size() << endl;
    cout << "property list uchar uint vertex_indices" << endl;
    cout << "end_header" << endl;
    
    for(Vertex v : this->vertices)
        v.print();
    for(Face f: this->faces)
        f.print();
    */
    int counter = 1;
    for(int i=0; i<faces.size(); i++){
        cout << "Cara #" << counter++ << endl;
        faces.at(i).print();
    }
    
}

vector<Face> Object::getFaces(){
    vector<Face> f = this->faces;
    return(f);
}

vector<Vertex> Object::getVertex(){
    vector<Vertex> v = this->vertices;
    return(v);
}