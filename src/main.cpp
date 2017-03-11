#include <GLFW/glfw3.h>

#include <iostream>

#include "boid.h"

int window_width = 800;
int window_height = 800;

GLfloat translation[3] = {0.0f, 0.0f, 0.0f};
GLfloat rotation[3] = {0.0f, 0.0f, 0.0f};
float zoom = 0.5f;

long t = 0;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (key) {
            
        case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GLFW_TRUE); break;
        case GLFW_KEY_Q: glfwSetWindowShouldClose(window, GLFW_TRUE); break;
        case GLFW_KEY_LEFT :
            if (action && mods == GLFW_MOD_SHIFT) translation[0] -= 0.001f * window_width;
            else if (action) rotation[1] -= 15.0f;
            break;
        case GLFW_KEY_RIGHT:
            if (action && mods == GLFW_MOD_SHIFT) translation[0] += 0.001f * window_width;
            else if (action) rotation[1] += 15.0f;
            break;
        case GLFW_KEY_UP:
            if (action && mods == GLFW_MOD_SHIFT) translation[1] += 0.001f * window_height;
            else if (action) rotation[0] += 15.0f;
            break;
        case GLFW_KEY_DOWN:
            if (action && mods == GLFW_MOD_SHIFT) translation[1] -= 0.001f * window_height;
            else if (action) rotation[0] -= 15.0f;
            break;
        case GLFW_KEY_EQUAL:
            if (action && mods == GLFW_MOD_SHIFT) zoom -= 0.25f;
            break;
        case GLFW_KEY_MINUS:
            if (action) zoom += 0.25f;
        default: break;
    }
    
}

void display(GLFWwindow* window) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // clear background screen to black
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the color buffer (sets everything to black)

    glMatrixMode(GL_PROJECTION); // You had GL_MODELVIEW
    glLoadIdentity();
        glOrtho(-20 * zoom, 20 * zoom, -20 * zoom, 20 * zoom, 20 * zoom, -20 * zoom); // ZOOM!
    glMatrixMode(GL_MODELVIEW);                  // indicate we are specifying camera transformations
    glLoadIdentity();                            // make sure transformation is "zero'd"

    glPushMatrix();
    glTranslatef(translation[0], translation[1], translation[2]);
    glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);
    glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);


    glPopMatrix();
    
    glfwSwapBuffers(window);

    t++;
    
}

void size_callback(GLFWwindow* window, int width, int height)
{
    // Get the pixel coordinate of the window
    // it returns the size, in pixels, of the framebuffer of the specified window
    glfwGetFramebufferSize(window, &window_width, &window_height);
    
    glViewport(0, 0, window_width, window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, window_width, 0, window_height, 1, -1);
    
    display(window);
}

int main(int argc, char *argv[]) {
    if (!glfwInit()) {
        std::cout << "GLFW could not be initialied." << std::endl;
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Flock Demo", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(window, &window_width, &window_height);

    /* Zoom out! */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(-20, 20, -20, 20, 20, -20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glEnable(GL_DEPTH_TEST);	// enable z-buffering
    glDepthFunc(GL_LESS);

    glfwSetWindowTitle(window, "Flock Demo");
    glfwSetWindowSizeCallback(window, size_callback);
    glfwSetKeyCallback(window, key_callback);

    while(!glfwWindowShouldClose(window)) {
        display(window);
//        glfwSetWindowSize(window, window_width, window_height);
        glfwPollEvents();
    }

    return 0;
}
