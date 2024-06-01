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
     
    bool inputPolling(GLFWwindow* window, float deltaTime)
    {
        auto app = reinterpret_cast<dzg*>(glfwGetWindowUserPointer(window));
        float cameraSpeed = app->camera->speed;
        float playerSpeed = 1000000.0f;

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


     //   app->m_scene->
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            app->m_scene->Player->offsetPosition(glm::vec3(0.0f, -playerSpeed * deltaTime, 0.0f));
        }
        else
        {
            app->m_scene->Player->offsetPosition(glm::vec3(0.0f, playerSpeed * deltaTime, 0.0f));
       //     app->m_scene->m_Partic

        }

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            return false;
        }
        return true;
    }
}