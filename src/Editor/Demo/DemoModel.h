//
//  ModelTest.h
//  TmingEngine
//
//  Created by blue on 2018/9/2.
//

#ifndef ModelTest_h
#define ModelTest_h

#include "DemoTest.h"

class DemoModel :public DemoTest
{
public:
    DemoModel()
    {
    }
    
    ~DemoModel()
    {
    }
    
    void Initlization() override;
    void Render_SceneObject() override;
    
    
    float vertices[9] ={
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f,  0.5f, 0.0f  // top
        
    };
    
    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";
    
    unsigned int VBO, VAO;
    int shaderProgram;
    
   void SetupShader();
    
private:
    
};


#endif /* ModelTest_h */
