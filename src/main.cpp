#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

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

    while (!glfwWindowShouldClose(window))
    {
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