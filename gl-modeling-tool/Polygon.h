//
//  Polygon.h
//  gl-modeling-tool
//
//  Created by Melih Mete on 26.04.2019.
//  Copyright © 2019 Melih Mete. All rights reserved.
//

#ifndef Polygon_h
#define Polygon_h

class Polygon {
    
public:
    Polygon() {
        VAO = 0;
        VBO = 0;
    }
    
    ~Polygon() {
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
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * 36, vertices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
        glBindVertexArray(0);
    }
    
    void Draw() {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
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
    GLuint VAO;
    GLuint VBO;
    
    GLfloat vertices[36] = {
        
        0.0f, 1.0f, -1.0f,
        -1.0f, 0.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        
        -1.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, -1.0f, 
        
        -1.0f, 0.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 0.0f, -2.0f,
        
        -1.0f, 1.0f, -1.0f,
        -1.0f, 0.0f, -2.0f,
        -1.0f, 1.0f, -2.0f
        
    };
    
    float unit = 0.0f;
    float movementSpeed = 2.0f;
    
};

#endif /* Polygon_h */
