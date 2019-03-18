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
    Cube() {length = 5;}
    ~Cube() {}
    
    void Init() {
        
        
    }
    
private:
    int length;
    GLuint VAO;
    GLuint VBO;
    GLuint IBO;
    
};
#endif /* Cube_h */
