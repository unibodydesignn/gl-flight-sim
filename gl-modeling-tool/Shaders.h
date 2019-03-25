//
//  Shaders.h
//  gl-modeling-tool
//
//  Created by Melih Mete on 24.03.2019.
//  Copyright © 2019 Melih Mete. All rights reserved.
//

#ifndef Shaders_h
#define Shaders_h

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

class Shaders {
 
public:
    Shaders() {
        VertexShaderCode =R"glsl(
                        #version 120
                        attribute vec2 position;
        
                        uniform mat4 model;
                        uniform mat4 view;
                        uniform mat4 projection;
        
                        void main() {
                            gl_Position = projection * view * model * vec4(position, 0.2f, 1.0f);
                            //gl_Position = vec4(position, 0.2f, 1.0f);
                        }
                        )glsl";
        
        
        FragmentShaderCode =
                        "#version 120\n"
                        "uniform vec4 ourColor;\n"
                        "void main()\n"
                        "{\n"
                        "   gl_FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n" // can be outcolor value rather than vec4 value
                        "}\n\0";
    }
    
    ~Shaders() {
        VertexShaderCode = "";
        FragmentShaderCode = "";
    }

public:
    void Init() {
        // Create the shaders
        GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        
        GLint Result = GL_FALSE;
        int InfoLogLength;
        
        // Compile Vertex Shader
        printf("Compiling shader...\n");
        char const * VertexSourcePointer = VertexShaderCode.c_str();
        glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
        glCompileShader(VertexShaderID);
        
        // Check Vertex Shader
        glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            printf("%s\n", &VertexShaderErrorMessage[0]);
        }
        
        // Compile Fragment Shader
        printf("Compiling shader...\n");
        char const * FragmentSourcePointer = FragmentShaderCode.c_str();
        glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
        glCompileShader(FragmentShaderID);
        
        // Check Fragment Shader
        glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
            printf("%s\n", &FragmentShaderErrorMessage[0]);
        }
        
        // Link the program
        printf("Linking program\n");
        ProgramID = glCreateProgram();
        glAttachShader(ProgramID, VertexShaderID);
        glAttachShader(ProgramID, FragmentShaderID);
        glLinkProgram(ProgramID);
        
        // Check the program
        glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
        glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> ProgramErrorMessage(InfoLogLength+1);
            glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            printf("%s\n", &ProgramErrorMessage[0]);
        }
        
        glDetachShader(ProgramID, VertexShaderID);
        glDetachShader(ProgramID, FragmentShaderID);
        
        glDeleteShader(VertexShaderID);
        glDeleteShader(FragmentShaderID);
    }
    
    GLuint GetShaderID() {
        return ProgramID;
    }
    
    void EditMatrix4(std::string m_name, glm::mat4 matrix) {
        if(m_name == "model") {
            int modelLoc = glGetUniformLocation(ProgramID, m_name.c_str());
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix));
        } else if(m_name == "view"){
            int modelLoc = glGetUniformLocation(ProgramID, m_name.c_str());
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &matrix[0][0]);
        } else {
            int modelLoc = glGetUniformLocation(ProgramID, m_name.c_str());
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix));
        }
    }
    
private:
    std::string VertexShaderCode;
    std::string FragmentShaderCode;
    GLuint ProgramID;
    
};



#endif /* Shaders_h */
