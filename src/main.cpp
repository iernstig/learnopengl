#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

float verticies[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,600, "learnopengl", NULL, NULL);
    if (window == NULL)
    {
        cout << "failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    } 
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "failed to initialize GLAD" << endl;
        return -1;
    }

    glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window)) 
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0,0,width,height);
}
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}