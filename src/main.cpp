#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.3f, 0.2f, 1.0f);\n"
    "}\0";

const char *fragmentShader2Source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);"
    "}\0";

float vertices0[] = {
    // first triangle
    0.3f, 0.3f, 0.0f,
    0.6f, 0.3f, 0.0f,
    0.6f, 0.6f, 0.0f,
};
float vertices1[] = {
    -.3f, -.3f, 0.0f,
    -.6f, -.3f, 0.0f,
    -.6f, -.6f, 0.0f
};
// unsigned int indices[] = {
//     0,1,3, // first triangle
//     1,2,3,  // second triangle
// };

int main() {
    // set some parameters for the window which we'll create
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create the window
    GLFWwindow* window = glfwCreateWindow(800,600, "learnopengl", NULL, NULL);
    if (window == NULL)
    {
        cout << "failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    } 
    // attach GLAD to window context
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "failed to initialize GLAD" << endl;
        return -1;
    }

    // set viewport pa,rameters
    glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // load the vert shader source
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // bind the shader source to our shader object and compile it
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); 
    glCompileShader(vertexShader);

    // check shader compilation success or fail?
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }

    unsigned int fragmentShader; 
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }

    // create the final shader program mending everything together
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2,1, &fragmentShader2Source, NULL);

    glCompileShader(fragmentShader2);
    unsigned int shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);



    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if(!success) 
    {
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
        cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }


    // cleanup, don't need these any more apparently.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);


    // create a vertex buffer object to facilitate simpler data stream to gpu
    unsigned int VBO_0, VAO_0;
    // generate the buffer objects - the vao is the pointer for the vbo where the data is stored
    glGenVertexArrays(1, &VAO_0);
    glGenBuffers(1, &VBO_0);

    // bind the current vao into context
    glBindVertexArray(VAO_0);

    // bind the buffer to the current vao in context
    glBindBuffer(GL_ARRAY_BUFFER, VBO_0);
    // send data to the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices0), vertices0, GL_STATIC_DRAW);
    // tell openGL how to interpret the data we just sent
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // enable the vao
    glEnableVertexAttribArray(0);
    // glVertexAttribPointer(VAO_1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(VAO_1);
    unsigned int VBO_1, VAO_1; //, EBO;
    glGenVertexArrays(1, &VAO_1);
    glGenBuffers(1, &VBO_1);

    glBindVertexArray(VAO_1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO_0);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO_1);
    // glBindVertexArray(0);

    

    while(!glfwWindowShouldClose(window)) 
    {
        processInput(window);

        glClearColor(0.2f, 0.5f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO_0);
        glDrawArrays(GL_TRIANGLES, 0,3);

        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO_1);
        glDrawArrays(GL_TRIANGLES, 0,3);

        glBindVertexArray(0);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
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