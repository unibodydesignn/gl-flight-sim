//
//  Triangle.h
//  gl-modeling-tool
//
//  Created by Melih Mete on 7.03.2019.
//  Copyright © 2019 Melih Mete. All rights reserved.
//

#ifndef Triangle_h
#define Triangle_h

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <stdlib.h>

class Triangle {
    
public:
    
    Triangle() {
        VAO = 0;
        VBO = 0;
        IBO = 0;
        indexCount = 12;
    }
    
    ~Triangle() {
        VAO = 0;
        VBO = 0;
        IBO = 0;
        indexCount = 0;
    }
    
    void Init() {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        
        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * 9, indices, GL_STATIC_DRAW);
        
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * 9, vertices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
        glBindVertexArray(0);
    }
    
    void Draw() {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    void CalculateTranslation(int mode, glm::mat4& model_, float delta_time) {
        // Mesh controls
        unit = movementSpeed * delta_time;
        
        if(mode == 1) {
            model_ = glm::translate(model_, glm::vec3(0.0f, unit, 0.0f));
        }
        
        if(mode == 2) {
            model_ = glm::translate(model_, glm::vec3(0.0f, -unit, 0.0f));
        }
        
        if(mode == 3) {
            model_ = glm::rotate(model_, glm::radians(0.5f), glm::vec3(0.0f, 0.0f, 1.0f));
        }
        
        if(mode == 4) {
            model_ = glm::rotate(model_, glm::radians(0.5f), glm::vec3(0.0f, 0.0f, -1.0f));
        }
    }
    
    
private:
    unsigned int indices[9] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0
    };
    
    GLfloat vertices[9] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };
    
    unsigned int VAO;
    unsigned int VBO;
    unsigned int IBO;
    unsigned int indexCount;
    float unit = 0.0f;
    float movementSpeed = 2.0f;
};

#endif /* Triangle_h */
