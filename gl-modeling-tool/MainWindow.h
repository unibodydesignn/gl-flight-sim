//
//  MainWindow.h
//  gl-modeling-tool
//
//  Created by Melih Mete on 17.02.2019.
//  Copyright © 2019 Melih Mete. All rights reserved.
//

#ifndef MainWindow_h
#define MainWindow_h
#define GLFW_STATIC

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Cube.h"
#include "Triangle.h"
#include "Shaders.h"

class MainWindow {

public:
    MainWindow() {
        windowsHeigth = 1600;
        windowsWidth  = 2560;
        programID = 0;
    }
    
    ~MainWindow() { }
    
    static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) {
        std::cout << "XPOS : " << xPos << " ypos : " << yPos << std::endl;
    }
    
    void cursorEnterCallback(GLFWwindow *window, int entered) {
        
    }
    
    void Init() {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        
        if(glfwInit()) {
            std::cout << "Initiated GLFW" << std::endl;
        }
        
        window = glfwCreateWindow(windowsWidth, windowsHeigth, "Modeling Tool", NULL, NULL);
        if(window == NULL) {
            std::cout << "Error creating on windows." << std::endl;
        }
        
        glfwSetCursorPosCallback(window, cursorPositionCallback);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwGetFramebufferSize(window, &windowsWidth, &windowsHeigth);
        glfwMakeContextCurrent( window );
        
        glewExperimental = GL_TRUE;
        if (glewInit () != GLEW_NO_ERROR) {
            std::cout << "Failed to initialize GLEW... " << std::endl;
            return;
        }
        
        glViewport(0.0f, 0.0f, windowsWidth, windowsHeigth);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, windowsWidth, 0, windowsHeigth, 0, 1000);
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity( );
    }

    void Run() {
        
        //Triangle *tri = new Triangle();
        //tri->Init();
        shader = new Shaders();
        Cube* cube = new Cube();
        cube->Init();
        
        while (!glfwWindowShouldClose(window)) {
            glEnable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(96.0f/255.0f, 96.0f/255.0f, 96.0f/255.0f, 1.0f);
            
            shader->Init();
            programID = shader->GetShaderID();
            glUseProgram(programID);
            
            glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            glm::mat4 view          = glm::mat4(1.0f);
            glm::mat4 projection    = glm::mat4(1.0f);
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
            //view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
            float radius = 10.0f;
            float camX = sin(glfwGetTime()) * radius;
            float camZ = cos(glfwGetTime()) * radius;
            view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
            projection = glm::perspective(glm::radians(45.0f), (float)windowsWidth / (float)windowsHeigth, 0.1f, 100.0f);
            
            shader->EditMatrix4("model", model);
            shader->EditMatrix4("view", view);
            shader->EditMatrix4("projection", projection);
            
            cube->Draw();
            glUseProgram(0);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        
        delete cube;
        delete shader;
        
        glfwTerminate( );
    }


private:
    int windowsHeigth = 1080;
    int windowsWidth = 1920;
    GLFWwindow *window;
    Shaders *shader;
    GLuint programID;
};

#endif /* MainWindow_h */
