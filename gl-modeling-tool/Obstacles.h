//
//  Obstacles.h
//  gl-modeling-tool
//
//  Created by Melih Mete on 24.04.2019.
//  Copyright © 2019 Melih Mete. All rights reserved.
//

#ifndef Obstacles_h
#define Obstacles_h

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Obstacles {

public:
    Obstacles() {
        VAO_ = 0;
        VBO_ = 0;
    }

    ~Obstacles() {
        VAO_ = 0;
        VBO_ = 0;
    }
    
    void Init() {
        glGenVertexArrays(1, &VAO_);
        glBindVertexArray(VAO_);
        
        glGenBuffers(1, &VBO_);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        glBindVertexArray(0);
        
    }
    
    void Draw() {
        glBindVertexArray(VAO_);
        glDrawArrays(GL_POINTS, 0, 3);
        glBindVertexArray(0);
    }

private:
    
    glm::vec3 obstaclePositions[3];
    GLfloat vertices[9] = {
        -1.0f, -2.0f, 0.0f,
        -2.0f, -5.0f, 0.0f,
        -4.0f, -3.0f, 0.0f
        
    };
    
    unsigned int VAO_;
    unsigned int VBO_;
    
};


#endif /* Obstacles_h */
