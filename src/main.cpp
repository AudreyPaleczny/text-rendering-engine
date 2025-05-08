#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

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
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

int main()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // so version 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // make our window resizeable
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Text", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // if you have multiple windows open, you don't know which one to draw into --> this tells the program
    glfwMakeContextCurrent(window); 
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed Init Glad" << std::endl;
        return -1;
    }

    // glViewport(0, 0, 1920, 1080); // window holds together all vars in opengl context but isn't the rendering 
    // viewport is what opengl is actually rendering to 
    // window is the frame and viewport is the screen with the analogy of a computer 
    
    // when adding y, it goes downward

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // start our rendering pipeline
    float vertices[] = 
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    // create our buffer
    unsigned int VBO;
    // printf("%d\n", VBO); // 0
    glGenBuffers(1, &VBO); // 1 is how many we're creating
    // printf("%d\n", VBO); // 1
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // create our attrib buffer 
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);


    // send data to the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // what we're sending, how many we're sending, pointer to data itself, static.. means we'll send the data once
    // sent to buffer but not GPU yet 

    // create our vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // need shadersource for turning the global var strings above into something comprehensive for OpenGL
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // just compiling 1 shader rn
    glCompileShader(vertexShader); // turns strings into machine code

    // create our fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); 
    glCompileShader(fragmentShader);

    // create shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // attach our shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // tell OpenGL to use it
    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // specify our vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // check doc for param explanations
    // since we have a vec3, the size of the attributes should be 3
    glEnableVertexAttribArray(0); // which slot we're enabling 

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // r g b opacity
        glClear(GL_COLOR_BUFFER_BIT); // makes the screen the above color

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

}

// tell the program new window size if user resizes window
// anything you can't guarantee when it happens --> callback function (i.e. when the user presses space, jump)
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // update with the new width and new height
    glViewport(0, 0, width, height);
}