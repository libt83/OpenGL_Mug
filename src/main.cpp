/******
 *
 *  Brandon Semba
 *  TCSS 458
 *  Assignment 5
 *  08/15/2016
 *
 *  The main that is used to create a context and window. It loads the shaders and textures. Creates all buffers
 *  and renders the model from its data that has been loaded into a struct. The 5 meshes form a mug with
 *  the use of the school's 3 primary colors. A UWT log and campus scene are displayed on the outer wall and rotation and lighting
 *  have been implemented as well.
 *
 *  Original source code was derived from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-8-basic-shading/
 *  The use of VAO's and creation of additional textures were added.
 *
 *****/

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <shader.hpp>
#include <texture.hpp>
#include <controls.hpp>
#include <objloader.hpp>

using namespace glm;
using namespace std;

int main( void )
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "Assignment 5: Brandon Semba", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the mouse at the center of the screen
    glfwPollEvents();
    
    glfwSetCursorPos(window, 1024/2, 768/2);
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    // Compiles shaders and creates a usable program
    GLuint programID = LoadShaders( "/Users/B/Desktop/Loader/Loader/vert.glsl",
                                   "/Users/B/Desktop/Loader/Loader/frag.glsl" );
    
    // Gets the location of uniform variables for the MVP, V, and M
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
    GLuint ModelMatrixID = glGetUniformLocation(programID, "M");
    
    // Loads the textures from .BMP files
    GLuint Texture1 = loadBMP_custom("/Users/B/Desktop/Loader/Loader/campus2.bmp");
    
    GLuint Texture2 = loadBMP_custom("/Users/B/Desktop/Loader/Loader/uw_logo.bmp");
    
    GLuint Texture3 = loadBMP_custom("/Users/B/Desktop/Loader/Loader/gold.bmp");
    
    GLuint Texture4 = loadBMP_custom("/Users/B/Desktop/Loader/Loader/purple.bmp");
    
    GLuint Texture5 = loadBMP_custom("/Users/B/Desktop/Loader/Loader/metallic_gold.bmp");
    
    // Get the location of the uniform sampler variables witin the fragment shader
    GLuint TextureID_1  = glGetUniformLocation(programID, "sampler1");
    
    GLuint TextureID_2  = glGetUniformLocation(programID, "sampler2");
    
    GLuint TextureID_3  = glGetUniformLocation(programID, "sampler3");
    
    GLuint TextureID_4  = glGetUniformLocation(programID, "sampler4");
    
    GLuint TextureID_5  = glGetUniformLocation(programID, "sampler5");
    
    struct objData obj_data;
    
    bool res = loadAssimp("/Users/B/Desktop/Loader/Loader/mug_v14.obj", &obj_data);
    

    GLuint VAO_1, VAO_2, VAO_3, VAO_4, VAO_5;
    
    //Setup VAO and associated buffers for the 5 meshes
//--------------------------------------------------
    
    glGenVertexArrays(1, &VAO_1);
    glBindVertexArray(VAO_1);
    GLuint vertexbuffer1;
    glGenBuffers(1, &vertexbuffer1);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
    glBufferData(GL_ARRAY_BUFFER, obj_data.vertices1.size() * sizeof(vec3), &obj_data.vertices1[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    GLuint uvbuffer1;
    glGenBuffers(1, &uvbuffer1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer1);
    glBufferData(GL_ARRAY_BUFFER, obj_data.uvs1.size() * sizeof(vec2), &obj_data.uvs1[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    GLuint normalbuffer1;
    glGenBuffers(1, &normalbuffer1);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer1);
    glBufferData(GL_ARRAY_BUFFER, obj_data.normals1.size() * sizeof(vec3), &obj_data.normals1[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT,GL_FALSE, 0, 0);
    
//------------------------------------------------------

    glGenVertexArrays(1, &VAO_2);
    glBindVertexArray(VAO_2);
    GLuint vertexbuffer2;
    glGenBuffers(1, &vertexbuffer2);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
    glBufferData(GL_ARRAY_BUFFER, obj_data.vertices2.size() * sizeof(vec3), &obj_data.vertices2[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    GLuint uvbuffer2;
    glGenBuffers(1, &uvbuffer2);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer2);
    glBufferData(GL_ARRAY_BUFFER, obj_data.uvs2.size() * sizeof(vec2), &obj_data.uvs2[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    GLuint normalbuffer2;
    glGenBuffers(1, &normalbuffer2);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer2);
    glBufferData(GL_ARRAY_BUFFER, obj_data.normals2.size() * sizeof(vec3), &obj_data.normals2[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

//-------------------------------------------
    
    glGenVertexArrays(1, &VAO_3);
    glBindVertexArray(VAO_3);
    GLuint vertexbuffer3;
    glGenBuffers(1, &vertexbuffer3);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer3);
    glBufferData(GL_ARRAY_BUFFER, obj_data.vertices3.size() * sizeof(vec3), &obj_data.vertices3[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    GLuint uvbuffer3;
    glGenBuffers(1, &uvbuffer3);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer3);
    glBufferData(GL_ARRAY_BUFFER, obj_data.uvs3.size() * sizeof(vec2), &obj_data.uvs3[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    GLuint normalbuffer3;
    glGenBuffers(1, &normalbuffer3);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer3);
    glBufferData(GL_ARRAY_BUFFER, obj_data.normals3.size() * sizeof(vec3), &obj_data.normals3[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
 
//---------------------------------------------

    glGenVertexArrays(1, &VAO_4);
    glBindVertexArray(VAO_4);
    GLuint vertexbuffer4;
    glGenBuffers(1, &vertexbuffer4);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer4);
    glBufferData(GL_ARRAY_BUFFER, obj_data.vertices4.size() * sizeof(vec3), &obj_data.vertices4[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    GLuint uvbuffer4;
    glGenBuffers(1, &uvbuffer4);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer4);
    glBufferData(GL_ARRAY_BUFFER, obj_data.uvs4.size() * sizeof(vec2), &obj_data.uvs4[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    GLuint normalbuffer4;
    glGenBuffers(1, &normalbuffer4);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer4);
    glBufferData(GL_ARRAY_BUFFER, obj_data.normals4.size() * sizeof(vec3), &obj_data.normals4[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
 
//---------------------------------------------

    glGenVertexArrays(1, &VAO_5);
    glBindVertexArray(VAO_5);
    GLuint vertexbuffer5;
    glGenBuffers(1, &vertexbuffer5);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer5);
    glBufferData(GL_ARRAY_BUFFER, obj_data.vertices5.size() * sizeof(vec3), &obj_data.vertices5[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    
    GLuint uvbuffer5;
    glGenBuffers(1, &uvbuffer5);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer5);
    glBufferData(GL_ARRAY_BUFFER, obj_data.uvs5.size() * sizeof(vec2), &obj_data.uvs5[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    GLuint normalbuffer5;
    glGenBuffers(1, &normalbuffer5);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer5);
    glBufferData(GL_ARRAY_BUFFER, obj_data.normals5.size() * sizeof(vec3), &obj_data.normals5[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    // Get location of light position variable within fragment shader
    glUseProgram(programID);
    GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
    
    GLfloat scale = 0.0f;
    
    do{
        
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Compute the MVP matrix from keyboard and mouse input
        computeMatricesFromInputs();
        mat4 ProjectionMatrix = getProjectionMatrix();
        mat4 ViewMatrix = getViewMatrix();
        mat4 ModelMatrix = mat4(1.0);
        
        // Rotates the model around x, y, and/or z planes
        mat4 MVP = ProjectionMatrix * ViewMatrix * (rotate(ModelMatrix, radians(scale), vec3(1.0f, 0.0f, 0.0f)));
        scale += 1.0f;

        
        // Send our transformation to the currently bound shader,
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
        
        vec3 lightPos = vec3(4,4,4);
        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
        
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO_1);
        // Bind our texture in Texture Unit 0
        glBindTexture(GL_TEXTURE_2D, Texture5);
        // Set our "sampler5" sampler to user Texture Unit 0
        glUniform1i(TextureID_5, 0);
        // Render the first mesh
        glDrawArrays(GL_TRIANGLES, 0, obj_data.vertices1.size());
        
        
        glBindVertexArray(VAO_2);
        glBindTexture(GL_TEXTURE_2D, Texture4);
        // Set our "sampler4" sampler to user Texture Unit 0
        glUniform1i(TextureID_4, 0);
        // Render the second mesh
        glDrawArrays(GL_TRIANGLES, 0, obj_data.vertices2.size());

        glBindVertexArray(VAO_3);
        glBindTexture(GL_TEXTURE_2D, Texture3);
        // Set our "sampler3" sampler to user Texture Unit 0
        glUniform1i(TextureID_3, 0);
        // Render the third mesh
        glDrawArrays(GL_TRIANGLES, 0, obj_data.vertices3.size());
        
        glBindVertexArray(VAO_4);
        glBindTexture(GL_TEXTURE_2D, Texture1);
        // Set our "sampler1" sampler to user Texture Unit 0
        glUniform1i(TextureID_1, 0);
        // Render the fourth mesh
        glDrawArrays(GL_TRIANGLES, 0, obj_data.vertices4.size());
        
        glBindVertexArray(VAO_5);
        glBindTexture(GL_TEXTURE_2D, Texture2);
        // Set our "sampler2" sampler to user Texture Unit 0
        glUniform1i(TextureID_2, 0);
        // Render the fifth mesh
        glDrawArrays(GL_TRIANGLES, 0, obj_data.vertices5.size());
        
        // Swap buffers
        glfwSwapBuffers(window);
        
        glfwPollEvents();
        
    } // If ESC is pressed then close the rendering window
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    // Delete buffers, textures, and program
    glDeleteBuffers(1, &vertexbuffer1);
    glDeleteBuffers(1, &uvbuffer1);
    glDeleteBuffers(1, &normalbuffer1);
    glDeleteBuffers(1, &vertexbuffer2);
    glDeleteBuffers(1, &uvbuffer2);
    glDeleteBuffers(1, &normalbuffer2);
    glDeleteBuffers(1, &vertexbuffer3);
    glDeleteBuffers(1, &uvbuffer3);
    glDeleteBuffers(1, &normalbuffer3);
    glDeleteBuffers(1, &vertexbuffer4);
    glDeleteBuffers(1, &uvbuffer4);
    glDeleteBuffers(1, &normalbuffer4);
    glDeleteBuffers(1, &vertexbuffer5);
    glDeleteBuffers(1, &uvbuffer5);
    glDeleteBuffers(1, &normalbuffer5);
    glDeleteTextures(1, &Texture1);
    glDeleteTextures(1, &Texture2);
    glDeleteTextures(1, &Texture3);
    glDeleteTextures(1, &Texture4);
    glDeleteTextures(1, &Texture5);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}

