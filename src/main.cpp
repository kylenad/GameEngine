#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shaders/shader.h>

//Function definitions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main () {

    //Intitalize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << '\n';
        return -1;
    }

    //Use OpenGL Version 4.1 (Highest version usable on MacOS)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create test window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Window!", NULL, NULL);
    if(!window) {
        std::cerr << "Failed to create window" << '\n';
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    //Intitalize Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << '\n';
    return -1;
    }

    //Simple Check
    std::cout << "Hello World!";
    std::cout << '\n' << "CMake Compilation" << '\n';

    //glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    //For using custom shader library
    Shader ourShader(ASSETS_DIR "/shaders/3.3.shader.vs", ASSETS_DIR "/shaders/3.3.shader.fs");
    Shader anotherShader(ASSETS_DIR "/shaders/3.3.shader.vs", ASSETS_DIR "/shaders/3.3.shader2.fs");

    float verticies[] = {
        // position          //color
         0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // top right
         0.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom right
        -0.9f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // bottom left
        -0.9f,  0.5f, 0.0f,  1.0f, 0.0, 1.0f,  // top left 
    };
    unsigned int indices[] = {  // note that we start from 0
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
    };  

    float triangle[] {
        0.1f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.46f, 0.5f, 0.0f   // top 
    };

    //Buffer object
    unsigned int VBOs[2], VAOs[2], EBO;
    glGenVertexArrays(2, VAOs);
    glGenBuffers(1, &EBO);
    glGenBuffers(2, VBOs);

    //for rectangle
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    //for triangle
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //Main loop
    while (!glfwWindowShouldClose(window)) {
    //Input
        processInput(window);

    // Render here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Draw two triangles, forming rectangle
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Get wireframe
        ourShader.use();
        glBindVertexArray(VAOs[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //draw separate triangle
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //turn off wireframe
        anotherShader.use();
        //uniform color implementation
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        anotherShader.setVec4("ourColor", 0.0f, greenValue, 0.0f, 1.0f);
        //render triangle itself
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

    // Swap buffers
        glfwSwapBuffers(window);

    // Poll for and process events
        glfwPollEvents();
    }

    //De-allocate resources
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}