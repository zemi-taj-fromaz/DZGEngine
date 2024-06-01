#pragma once


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

#include "app.h"
#include "Camera.h"

namespace glfw
{
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto app = reinterpret_cast<dzg*>(glfwGetWindowUserPointer(window));
        app->framebufferResized = true;
    }

    GLFWwindow* initWindowGLFW(int WIDTH, int HEIGHT, std::string appName = "Vulkan")
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        return glfwCreateWindow(WIDTH, HEIGHT, appName.c_str(), nullptr, nullptr);
    }

    void setWindowCallbacks(GLFWwindow* window, dzg* app)
    {
        glfwSetWindowUserPointer(window, app);
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    }

    void inputPolling(GLFWwindow* window, std::unique_ptr<Camera>& camera, float deltaTime)
    {
        float cameraSpeed = camera->speed;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            camera->movePosition( glm::vec3(0.0f, -cameraSpeed * deltaTime, 0.0f));
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            camera->movePosition(glm::vec3(-cameraSpeed * deltaTime, 0.0f, 0.0f));
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            camera->movePosition(glm::vec3(0.0f, cameraSpeed * deltaTime, 0.0f));

        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            camera->movePosition(glm::vec3(cameraSpeed * deltaTime, 0.0f, 0.0f));
        }
    }
}