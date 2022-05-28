#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "include/OpenGL.hpp"

int main(void)
{   
    int status;
    OpenGL openGl;

    status = openGl.start();

    return status;
}