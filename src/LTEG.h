#pragma once
#include <GLFW/glfw3.h>
#include <memory>
class LTEG
{
private:
    GLFWwindow *window;
    int camerPos[3];
    float c_X = 1.0f;
    float c_Y = 1.0f;
    float c_Z = 1.0f;

public:
    int engineCycle(GLFWwindow *window);
    void generateChunk();
    void deleteChunk();
    void addObject();
    void cameraposition(int XYZ[3], float cameraX, float cameraY, float cameraZ, GLFWwindow *window)
    {
        XYZ[3] = camerPos;
        cameraX = c_X;
        cameraY = c_Y;
        cameraZ = c_Z;
    };
};
