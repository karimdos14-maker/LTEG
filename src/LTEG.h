#pragma once
#include <GLFW/glfw3.h>
#include <memory>
class LTEG
{
private:
    GLFWwindow *window;

    float c_X = 0.0f;
    float c_Y = 0.0f;
    float c_Z = 0.0f;
    float cameraPos[3] = {c_X, c_Y, c_Z};

public:
    int engineCycle(GLFWwindow *window);
    void generateChunk();
    void deleteChunk();
    void addObject();
    void cameraposition(float (&XYZ)[3], float &cameraX, float &cameraY, float &cameraZ, GLFWwindow *window);
};
