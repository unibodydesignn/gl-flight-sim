//
//  MainWindow.h
//  gl-modeling-tool
//
//  Created by Melih Mete on 17.02.2019.
//  Copyright © 2019 Melih Mete. All rights reserved.
//

#ifndef MainWindow_h
#define MainWindow_h

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include "Cube.h"


class MainWindow {

public:
    MainWindow() {
        windowsHeigth = 1080;
        windowsWidth  = 1920;
    }
    ~MainWindow() { }
    
    static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) {
        std::cout << "XPOS : " << xPos << " ypos : " << yPos << std::endl;
    }
    
    void cursorEnterCallback(GLFWwindow *window, int entered) {
        
    }
    
    void Init() {
        if(glfwInit()) {
            std::cout << "Could not initiate GLFW" << std::endl; }
        
        window = glfwCreateWindow(windowsWidth, windowsHeigth, "Modeling Tool", NULL, NULL);
        
        if(window == NULL) {
            std::cout << "Error creating on windows." << std::endl;
            
        }
        
        glfwSetCursorPosCallback(window, cursorPositionCallback);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwGetFramebufferSize(window, &windowsWidth, &windowsHeigth);
        glfwMakeContextCurrent( window );
        glViewport(0.0f, 0.0f, windowsWidth, windowsHeigth);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho( 0, windowsWidth, 0, windowsHeigth, 0, 1000 );
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity( );
    }

    void Run() {
        // Loop until the user closes the window
        while ( !glfwWindowShouldClose( window) )
        {
            glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
            glClearColor(0.0f/255.0f, 129.0f/255.0f, 215.0f/255.0f, 1.0f);
            glfwSwapBuffers(window);
            
            glfwPollEvents( );
        }
        
        glfwTerminate( );
    }


private:
    int windowsHeigth = 1080;
    int windowsWidth = 1920;
    GLFWwindow *window;
    


};

#endif /* MainWindow_h */
