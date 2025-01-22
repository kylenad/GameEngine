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
    Shader ourShader(ASSETS_DIR "/shaders/3.3.shader.vs", ASSETS_DIR "/shaders/3.3.shader.fs");
    Shader anotherShader(ASSETS_DIR "/shaders/3.3.shader.vs", ASSETS_DIR "/shaders/3.3.shader2.fs");
    Shader textShader(ASSETS_DIR "/shaders/text.shader.vs", ASSETS_DIR "/shaders/text.shader.fs");

    float offset = 0.3f;
    anotherShader.setFloat("yOffset", offset);

    float verticies[] = {
        // position          //color
         -0.4f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f, // top right
         -0.4f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom right
        -0.9f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // bottom left
        -0.9f,  0.0f, 0.0f,  1.0f, 0.0, 1.0f,  // top left 
    };
    unsigned int indices[] = {  // note that we start from 0
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
    };  

    float triangle[] {
        0.1f, 0.3f, 0.0f,  // left
        0.3f, 0.3f, 0.0f,  // right
        0.2f, 0.5f, 0.0f   // top 
    };

    float triangle2[] {
        -0.3f, -0.9f, 0.0f,  // left
        0.6f, -0.9f, 0.0f,  // right
        0.15f, 0.0f, 0.0f   // top 
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

    // Gen VAOs for shapes to be rendered
    unsigned int RectVBO, RectEBO;
    unsigned int TriVBO;
    unsigned int RectVAO, TriVAO, Rect2VAO;
    bool hasTextCords;
    RectVAO = Geometry::createRectangle(verticies, sizeof(verticies), indices, sizeof(indices), RectVBO, RectEBO, hasTextCords = false);
    TriVAO = Geometry::createTriangle(triangle, sizeof(triangle), TriVBO);
    Rect2VAO = Geometry::createRectangle(rectTexture, sizeof(rectTexture), indices, sizeof(indices), RectVBO, RectEBO, hasTextCords = true);

    //Textures
    int width, height, nrChannels;
    unsigned int texture1, texture2;
    texture1 = Texture::setTexture(ASSETS_DIR "/textures/wall.jpg", width, height, nrChannels, true);
    texture2 = Texture::setTexture(ASSETS_DIR "/textures/awesomeface.png", width, height, nrChannels, true);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    textShader.use();
    glUniform1i(glGetUniformLocation(textShader.ID, "texture1"), 0); //manual option (use below for custom shader class function)
    textShader.setInt("texture2", 1);

    //Main loop
    while (!glfwWindowShouldClose(glfwWindow)) {
    //Input
        processInput(glfwWindow);

    // Render here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Draw two triangles, forming rectangle
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Get wireframe
        ourShader.use();
        glBindVertexArray(RectVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //draw separate triangle
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //turn off wireframe
        anotherShader.use();
        anotherShader.setFloat("yOffset", offset);
        //uniform color implementation
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        anotherShader.setVec4("ourColor", 0.0f, greenValue, 0.0f, 1.0f);
        //render triangle itself
        glBindVertexArray(TriVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //Draw a second rectangle with texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1); //bind texture
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // Make transformations with glm
        glm::mat4  trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.2f, -0.4f, 1.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 0.1f));
        textShader.use();
        textShader.setFloat("mixValue", mixValue);
        unsigned int transformLoc = glGetUniformLocation(textShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glBindVertexArray(Rect2VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


    // Swap buffers
        glfwSwapBuffers(glfwWindow);

    // Poll for and process events
        glfwPollEvents();
    }

    //De-allocate resources
    unsigned int VAOs[] = {RectVAO, TriVAO, Rect2VAO};
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