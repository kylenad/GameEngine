// Libraries---------------------------------------------------------
#include <iostream>
#include <shaders/shader.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Window.h>
#include <Geometry.h>
#include <Texture.h>
// ------------------------------------------------------------------

//Function definitions
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//variables
float mixValue = 0.2f;

int main () {

    //Create window
    Window window(800, 600, "Game Engine: Demo Window");
    GLFWwindow* glfwWindow = window.getGLFWwindow();

    //Intitalize Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << '\n';
    return -1;
    }

    // Custom shader library
    Shader ourShader(ASSETS_DIR "/shaders/3.3.shader2.vs", ASSETS_DIR "/shaders/3.3.shader.fs");
    Shader anotherShader(ASSETS_DIR "/shaders/3.3.shader.vs", ASSETS_DIR "/shaders/3.3.shader2.fs");
    Shader textShader(ASSETS_DIR "/shaders/text.shader.vs", ASSETS_DIR "/shaders/text.shader.fs");

    float offset = 0.3f;
    anotherShader.setFloat("yOffset", offset);

    float cubeVerts[] = {
        -0.5f, 0.8f, 0.0f, 1.0f, 0.0f, 0.0f,// Front top left
        -0.5f, -0.8f, 0.0f, 1.0f, 0.0f, 1.0f, // Front bottom left
        0.5f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f, // Front bottom right
        0.5f, 0.8f, 0.0f,  0.0f, 1.0f, 1.0f,// Front top right

        -0.5f, 0.8f, 0.4f, 0.0f, 1.0f, 1.0f,// Back top left
        -0.5f, -0.8f, 0.4f, 0.0f, 1.0f, 0.0f, // Back bottom left
        0.5f, -0.8f, 0.4f, 1.0f, 0.0f, 1.0f, // Back bottom right
        0.5f, 0.8f, 0.4f, 1.0f, 0.0f, 0.0f// Back top right

    };

    unsigned int cubeIndices[] = {
        0, 1, 3, // Front triangle 1
        1, 2, 3, // Front triangle 2

        4, 5, 7, // Back triangle 1
        5, 6, 7, // Back triangle 2

        4, 5, 0, // Left triangle 1
        5, 1, 0, // Left triangle 2

        7, 6, 3, // Right triangle 1
        6, 2, 3, // Right triangle 2

        0, 3, 4, // Top triangle 1
        3, 7, 4, // Top triangle 2

        1, 2, 5, // Bottom triangle 1
        2, 6, 5 // Bottom triangle 2
    };


    float rectTexture[] = {
    // positions          // colors           // texture coords
     0.8f,  0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right
     0.8f, -0.8f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right
     0.0f, -0.8f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
     0.0f,  0.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // top left 
    };
    unsigned int indicesTexture[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    float verts[] = {
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
    };

    // Gen VAOs for shapes to be rendered
    unsigned int RectVBO, RectEBO, VertsVBO;
    unsigned int RectVAO, Rect2VAO, VertsVAO;
    bool hasTextCords;
    RectVAO = Geometry::createRectangle(cubeVerts, sizeof(cubeVerts), cubeIndices, sizeof(cubeIndices), RectVBO, RectEBO, hasTextCords = false);
    Rect2VAO = Geometry::createRectangle(rectTexture, sizeof(rectTexture), indicesTexture, sizeof(indicesTexture), RectVBO, RectEBO, hasTextCords = true);
    VertsVAO = Geometry::createTriangle(verts, sizeof(verts), VertsVBO);

    //Textures
    int width, height, nrChannels;
    unsigned int texture1, texture2;
    texture1 = Texture::setTexture(ASSETS_DIR "/textures/wall.jpg", width, height, nrChannels, true);
    texture2 = Texture::setTexture(ASSETS_DIR "/textures/drake.png", width, height, nrChannels, true);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    textShader.use();
    glUniform1i(glGetUniformLocation(textShader.ID, "texture1"), 0); //manual option (use below for custom shader class function)
    textShader.setInt("texture2", 1);

    //Main loop
    while (!glfwWindowShouldClose(glfwWindow)) {
    // Input
        processInput(glfwWindow);

        // Clear screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render here
        // Draw two triangles, forming rectangle
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Get wireframe
        // Messing with drawing some sets of verts
        float timeValue = glfwGetTime();
        float redColor = (sin(timeValue) / 2.0f) + 0.5f;
        anotherShader.use();
        anotherShader.setVec4("ourColor", redColor, 0.0f, 0.0f, 0.0f);
        glBindVertexArray(VertsVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Rects with attatched texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1); //bind texture
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // Make transformations with glm
        glm::mat4  trans = glm::mat4(1.0f); // 4x4 identity matrix init
        trans = glm::translate(trans, glm::vec3(0.0f, 0.3f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
        textShader.use();
        textShader.setFloat("mixValue", mixValue);
        unsigned int transformLoc = glGetUniformLocation(textShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glBindVertexArray(Rect2VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glm::mat4 roat = glm::mat4(1.0f);
        roat = glm::rotate(roat,(float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));
        ourShader.use();
        unsigned int transformLoc2 = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(roat));
        glBindVertexArray(RectVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    // Swap buffers
        glfwSwapBuffers(glfwWindow);

    // Poll for and process events
        glfwPollEvents();
    }

    //De-allocate resources
    unsigned int VAOs[] = {RectVAO, Rect2VAO};
    glDeleteVertexArrays(3, VAOs);

    return 0;
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        mixValue += 0.002f;
        if (mixValue >= 1.0f) {
            mixValue = 1.0f;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        mixValue -= 0.002f;
        if (mixValue <= 0.0f) {
            mixValue = 0.0f;
        }
    }
}