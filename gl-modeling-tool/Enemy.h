//
//  Enemy.h
//  gl-modeling-tool
//
//  Created by Melih Mete on 24.04.2019.
//  Copyright © 2019 Melih Mete. All rights reserved.
//

#ifndef Enemy_h
#define Enemy_h

class Enemy {
    
public:
    Enemy() {
        enemyVAO = 0;
        enemyVBO = 0;
        enemyIBO = 0;
    }
    ~Enemy() {
        
    }
    
    void Init() {
        glGenVertexArrays(1, &enemyVAO);
        glBindVertexArray(enemyVAO);
        
        glGenBuffers(1, &enemyVBO);
        glBindBuffer(GL_ARRAY_BUFFER, enemyVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * 30, vertices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
        glBindVertexArray(0);
    }
    
    void Draw() {
        glBindVertexArray(enemyVAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, enemyIBO);
        glDrawArrays(GL_TRIANGLES, 0, 30);
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
    
    GLuint enemyVAO;
    GLuint enemyVBO;
    GLuint enemyIBO;
    
    GLfloat vertices[30] = {
        16.031, 30.204, 0.0f,
        19.28,  33.172, 0.0f,
        192.8,  39.439, 0.0f,
        21.089, 42.192, 0.0f,
        17.45, 42.192, 0.0f,
        16.03, 39.439, 0.0f,
        14.64, 42.192, 0.0f,
        11.83, 42.192, 0.0f,
        12.71, 39.43, 0.0f,
        
    };
    
    float unit = 0.0f;
    float movementSpeed = 2.0f;
};


#endif /* Enemy_h */
