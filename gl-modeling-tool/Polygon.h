//
//  Polygon.h
//  gl-modeling-tool
//
//  Created by Melih Mete on 26.04.2019.
//  Copyright © 2019 Melih Mete. All rights reserved.
//

#ifndef Polygon_h
#define Polygon_h
#include <vector>

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
        LoadFromOBJ("/Users/unibodydesignn/Desktop/new_aircraft.obj", vertices, normals);
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
        glBindVertexArray(0);
    }
    
    void Draw() {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, (int)vertices.size());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    void CalculateTranslation(int mode, glm::mat4& modelMatrix, float delta_time) {
        // Mesh controls
        unit = movementSpeed * delta_time;
        
        if(mode == 1) {
            modelMatrix = glm::translate(modelMatrix, glm::vec3(unit, 0.0f, 0.0f));
            movementSpeed += 0.3f;
            if(movementSpeed >= 9.0f)
                movementSpeed = 9.0f;
        }
        
        if(mode == 2) {
            modelMatrix = glm::translate(modelMatrix, glm::vec3(unit, 0.0f, 0.0f));
            movementSpeed -= 0.4f;
            if(movementSpeed <= 0.0f) {
                movementSpeed = 0.0f;
            }
        }
        
        if(mode == 3) {
            modelMatrix = glm::rotate(modelMatrix, glm::radians(0.5f), glm::vec3(-1.0f, 0.0f, 0.0f));
        }
        
        if(mode == 4) {
            modelMatrix = glm::rotate(modelMatrix, glm::radians(0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
        }
        
        if(mode == 5) {
            //modelMatrix = glm::rotate(modelMatrix, glm::radians(0.5f), glm::vec3(-modelMatrix[0][0], 0.0f, 0.0f));
        }
    }
    
    bool LoadFromOBJ(const char * path,
                     std::vector < glm::vec3 > & out_vertices,
                     std::vector < glm::vec3 > & out_normals)
    {
        std::vector< unsigned int > vertexIndices, normalIndices;
        std::vector< glm::vec3 > temp_vertices;
        std::vector< glm::vec3 > temp_normals;
        
        FILE * file = fopen(path, "r");
        
        if( file == NULL ){
            printf("Impossible to open the file !\n");
            return false;
        } else {
            printf("Opened the file. Processing data!\n" );
            
            while(1) {
                char lineHeader[128];
                // read the first word of the line
                int res = fscanf(file, "%s", lineHeader);
                if (res == EOF)
                    break; // EOF = End Of File. Quit the loop.
                else {
                    if ( strcmp( lineHeader, "v" ) == 0 ){
                        glm::vec3 vertex;
                        fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
                        temp_vertices.push_back(vertex);
                    } else if ( strcmp( lineHeader, "vn" ) == 0 ){
                        glm::vec3 normal;
                        fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
                        temp_normals.push_back(normal);
                    } else if ( strcmp( lineHeader, "f" ) == 0 ){
                        std::string vertex1, vertex2, vertex3;
                        unsigned int vertexIndex[3], normalIndex[3];
                        fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2] );
                        
                        vertexIndices.push_back(vertexIndex[0]);
                        vertexIndices.push_back(vertexIndex[1]);
                        vertexIndices.push_back(vertexIndex[2]);
                
                        normalIndices.push_back(normalIndex[0]);
                        normalIndices.push_back(normalIndex[1]);
                        normalIndices.push_back(normalIndex[2]);
                    }
                }
            }
            
            for( unsigned int i=0; i<vertexIndices.size(); i++ ) {
                unsigned int vertexIndex = vertexIndices[i];
                glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
                out_vertices.push_back(vertex);
            }
            return true;
        }
    }
    
private:
    GLuint VAO;
    GLuint VBO;
    
    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec3 > normals; // Won't be used at the moment.
    
    float unit = 0.0f;
    float movementSpeed = 3.0f;
    
};

#endif /* Polygon_h */
