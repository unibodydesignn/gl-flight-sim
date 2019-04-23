//
//  Aircraft.h
//  gl-modeling-tool
//
//  Created by Melih Mete on 19.04.2019.
//  Copyright © 2019 Melih Mete. All rights reserved.
//

#ifndef Aircraft_h
#define Aircraft_h

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <stdlib.h>

class Aircraft {
    
public:
    
    Aircraft() {
        multiplier = 0;
        rollAngle = 0;
        yawAngle = 0;
        pitchAngle = 0;
        groundSpeed = 0;
        flightSpeed = 0;
        longitude = 0;
        latitude = 0;
        altitude = 0;
    }
    
    ~Aircraft() {
        
    }
    
private:
    double multiplier;
    double rollAngle;
    double yawAngle;
    double pitchAngle;
    double groundSpeed;
    double flightSpeed;
    double longitude;
    double latitude;
    int altitude;

    
};

#endif /* Aircraft_h */
