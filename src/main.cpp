// NOTE: GLAD library header must be included before
// other header files that require OpenGL (like GLFW).
// clang-format off
#include <glad/glad.h>
// clang-format on

#include <GLFW/glfw3.h>
#include <iostream>

/// Shaders
#include <shaders/triangle_shaders.hpp>

std::pair<GLuint, GLuint> createVertexObjects();
GLuint compileShaders();

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void processRender(GLFWwindow *window, GLuint shaderProgram, GLuint VAO, GLuint VBO);

int main(int argc, char *argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // shaders
    auto [vao, vbo] = createVertexObjects();
    auto shaderProgram = compileShaders();

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // rendering commands her
        processRender(window, shaderProgram, vao, vbo);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

std::pair<GLuint, GLuint> createVertexObjects()
{
    const float vertices[] = {
        -0.5f, -0.5f, 0.0f, //
        0.5f, -0.5f, 0.0f,  //
        0.0f, 0.5f, 0.0f    //
    };

    GLuint VAO;                 // vertex array object
    glGenVertexArrays(1, &VAO); // generate vertex array ID
    glBindVertexArray(VAO);

    GLuint VBO;            // vertex buffer object (VBO)
    glGenBuffers(1, &VBO); // generate buffer ID
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // copy vertices array in a buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    return { VAO, VBO };
}

GLuint compileShaders()
{
    // Compiling vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Logging shader compiling status
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Compiling fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Logging shader compiling status
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Linking shaders in shader programm
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Logging shaders linking status
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAMM::LINKAGE_FAILED\n" << infoLog << std::endl;
    }

    // Delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void processRender(GLFWwindow *window, GLuint shaderProgram, GLuint VAO, GLuint VBO)
{
    // Clear screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Use shader programm
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
