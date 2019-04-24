//
//  Cube.h
//  gl-modeling-tool
//
//  Created by Melih Mete on 17.02.2019.
//  Copyright © 2019 Melih Mete. All rights reserved.
//

#ifndef Cube_h
#define Cube_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cube {

public:
    Cube() {
        length = 5;
        VAO = 0;
        VBO = 0;
    }
    
    ~Cube() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
    
    void Init() {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        glBindVertexArray(0);
        
    }
    
    void Draw() {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
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
            model_ = glm::translate(model_, glm::vec3(-unit, 0.0f, 0.0f));
        }
        
        if(mode == 4) {
            model_ = glm::translate(model_, glm::vec3(unit, 0.0f, 0.0f));
        }
    }
    
    
private:
    
    // use with Perspective Projection
    float vertices[180] = {
        -1.0, -1.0,  1.0,
        1.0, -1.0,  1.0,
        1.0,  1.0,  1.0,
        -1.0,  1.0,  1.0,
        // back
        -1.0, -1.0, -1.0,
        1.0, -1.0, -1.0,
        1.0,  1.0, -1.0,
        -1.0,  1.0, -1.0
    };
    
    unsigned int length;
    unsigned int VAO;
    unsigned int VBO;
    float unit = 0.0f;
    float movementSpeed = 2.0f;
};

#endif /* Cube_h */
