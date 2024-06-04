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

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto app = reinterpret_cast<dzg*>(glfwGetWindowUserPointer(window));
        app->m_scene->keyCallback(window, key, scancode, action, mods);
    }

    GLFWwindow* initWindowGLFW(int WIDTH, int HEIGHT, std::string appName = "Vulkan")
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        return glfwCreateWindow(WIDTH, HEIGHT, appName.c_str(), nullptr, nullptr);
    }

    void setWindowCallbacks(GLFWwindow* window, dzg* app)
    {
        glfwSetWindowUserPointer(window, app);
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
        glfwSetKeyCallback(window, keyCallback);
        /*
            Add more callback functions as needed
        */
    }
     
    bool inputPolling(GLFWwindow* window, float deltaTime)
    {
        auto app = reinterpret_cast<dzg*>(glfwGetWindowUserPointer(window));
        float cameraSpeed = app->camera->speed;
        float playerSpeed = 5.0f;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            app->camera->movePosition( glm::vec3(0.0f, -cameraSpeed * deltaTime, 0.0f));
        }
         
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            app->camera->movePosition(glm::vec3(-cameraSpeed * deltaTime, 0.0f, 0.0f));
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            app->camera->movePosition(glm::vec3(0.0f, cameraSpeed * deltaTime, 0.0f));

        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            app->camera->movePosition(glm::vec3(cameraSpeed * deltaTime, 0.0f, 0.0f));
        }


        app->m_scene->inputPolling(window, deltaTime);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            return false;
        }
        return true;
    }
}