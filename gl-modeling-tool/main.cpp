//
//  main.cpp
//  gl-modeling-tool
//
//  Created by Melih Mete on 17.02.2019.
//  Copyright © 2019 Melih Mete. All rights reserved.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "MainWindow.h"

int main() {
    
    MainWindow* windows = new MainWindow();
    windows->Init();
    windows->Run();
    
}
