#include "../include/OpenGL.hpp"
#include "../include/Ball.hpp"
#include "../include/Putter.hpp"
#include "../include/Flag.hpp"
#include "../include/Line.hpp"
#include "../include/Bezier.hpp"
#include "../include/Vertex.hpp"
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>

using namespace std;

OpenGL::OpenGL()
{
    info();
    cout << "Punto Inicial\n" << flush;
    Vertex Pi = getVertex(Pi);
    cout << "\n" << flush;
    cout << "Punto Final\n" << flush;
    Vertex Pf = getVertex(Pf);
    cout << "\n" << flush;
    this->Pi = Pi;
    this->Pf = Pf;
    cout << "Calculando...\n" << flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
}

int OpenGL::start(){
    GLFWwindow *window;

    if (!glfwInit()){
        cout << stderr << "Fallo al inicializar GLFW.\n" << flush;
        getchar();
        return -1;
        
    }
    window = glfwCreateWindow(1024, 768, "Proyecto", NULL, NULL);
    if (window == NULL){
        cout << stderr << "Fallo al abrir la ventana de GLFW.\n"<< flush;
        getchar();
        glfwTerminate();
        return -1;

    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //                               model,   r,   g,   b,  ka, kd
    Ball ball = Ball("models/golfball.ply", 1.0, 1.0, 1.0, 0.9, 0.9, this->Pi, this->Pf);
    ball.start();
    Putter putter = Putter("models/putter.ply", ball.getPosInit(), 0.6118, 0.6118, 0.6118, 0.9, 0.9);
    Flag flag = Flag("models/flag.ply", ball.getPosFin(), 1.0, 0.0, 0.0, 0.9, 0.9);

    arma::frowvec eye = {0.0, 0.0, 10.0};
    arma::frowvec camera = {0.0, 0.0, 0.0};
    arma::frowvec vup = {0.0, 1.0, 0.0};
    float Ia = 0.9;
    float Ip = 0.8; //Intensidad del foco
    arma::frowvec F = {0.0, 10.0, 0.0};
    int width, height;

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        //camara
        gluLookAt(eye[0], eye[1], eye[2],
                  camera[0], camera[1], camera[2],
                  vup[0], vup[1], vup[2]); //vup

        //Proyecciones
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glfwGetFramebufferSize(window, &width, &height);
        float ar = width / height;  //aspec ratio
        //Proyección en paralelo
        glViewport(0, 0, width, height);
        //       ar, ar, up, down,  proy frente, proy atras         
        glOrtho(-ar, ar, -1.0, 1.0, -20.0, 20.0);
        //Proyección en perspectiva
        //glFrustum(-ar, ar, -ar, ar, 2.0, 4.0);

        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            eye = {0.0, 10.0, 0.0};
            vup = {0.0, 0.0, -1.0};
            ball.start();
        }else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            eye = {10.0, 0.0, 10.0};
            vup = {0.0, 1.0, 0.0};
            ball.start();
        }else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            eye = {0.0, 0.0, 10.0};
            vup = {0.0, 1.0, 0.0};
            ball.start();
        }

        putter.draw(Ia, Ip, F);
        ball.draw(Ia, Ip, F);
        flag.draw(Ia, Ip, F);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    glfwTerminate();
    return 0;
}

Vertex OpenGL::getVertex(Vertex P){
    float x, y, z;

    cout << "Valor en X: ";
    x = validate(x);
    cout << "Valor en Y: ";
    y = validate(y);
    cout << "Valor en Z: ";
    z = validate(z);
    cout << "\n" << flush;
    Vertex V(x, y, z);
    cout << "Datos obtenidos: \n" << flush;
    V.print();

    return V;
}

float OpenGL::validate(float var){
    int flag = 0;
    
    do{
        cin >> var;
        if(var <= 1 && var >= -1){
            flag = 1;
        }else{
            cout << "Escribe valores entre 1 y -1 para su correcta visualizacion: ";
        }
    }while (flag==0);
    
    return var;
}


void OpenGL::info(){
    cout << "********************************************************************\n" << flush;
    cout << "*               Proyecto: Hole in One -Golf- 2022                  *\n" << flush;
    cout << "*                                                                  *\n" << flush;
    cout << "* Alumno: Daniel Alejandro Rodriguez Cardona                       *\n" << flush;
    cout << "* Profesor: Omar Rodriguez Gonzalez                                *\n" << flush;
    cout << "* Materia: Graficacion Por Computadora                             *\n" << flush;
    cout << "*                                                                  *\n" << flush;
    cout << "* Presiona enter para continuar...                                 *\n" << flush;
    cout << "********************************************************************\n" << flush;
    cin.get();
    system("clear");
    cout << "********************************************************************\n" << flush;
    cout << "* Antes de usar el software, se recomienda leer manual de usuario  *\n" << flush;
    cout << "* Existe la posibilidad que la curva mostrada no sea 'realista'    *\n" << flush;
    cout << "*                                                                  *\n" << flush;
    cout << "* Como ejemplo, puede usar:                                        *\n" << flush;
    cout << "* Punto Inicial:                                                   *\n" << flush;
    cout << "* X: -0.9                                                          *\n" << flush;
    cout << "* Y: -0.5                                                          *\n" << flush;
    cout << "* Z:  0.0                                                          *\n" << flush;
    cout << "*                                                                  *\n" << flush;
    cout << "* Punto Final:                                                     *\n" << flush;
    cout << "* X: -0.1                                                          *\n" << flush;
    cout << "* Y: -0.1                                                          *\n" << flush;
    cout << "* Z:  0.0                                                          *\n" << flush;
    cout << "*                                                                  *\n" << flush;
    cout << "* Presiona enter para capturar datos...                            *\n" << flush;
    cout << "********************************************************************\n" << flush;
    cin.get();
    system("clear");
}