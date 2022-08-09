#pragma once
#include "common.hpp"
#include "window.hpp"

using namespace glm;

struct Camera {
    mat4 ViewMatrix;
    mat4 Projection;
    float RenderDistance;
    float FOV;
	vec3 position;
    Camera(vec3 position, float FOV = radians(45.0f), float renderDistance = 100.0f){
		this->position = position;
        Projection = perspective(FOV, Window::WindowSize.x / Window::WindowSize.y, 0.1f, renderDistance);
        ViewMatrix = mat4(1.0f);
        ViewMatrix = translate(position);
        RenderDistance = renderDistance;
        this->FOV = FOV;
    }
};

void ChangeFOV(Camera c, float value){
    c.Projection = perspective(value, Window::WindowSize.x / Window::WindowSize.y, 0.1f, c.RenderDistance);
    c.FOV = value;
}

namespace 
{
    float speed = 1.0f;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    bool firstClick = true;
    float sensitivity = 100.0f;
} 


void ControlCamera(Camera* c, GLFWwindow* window)
{   
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		c->position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		c->position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		c->position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		c->position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		c->position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		speed = 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		c->position += speed * -Up;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}


	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstClick)
		{
			glfwSetCursorPos(window, (Window::WindowSize.x / 2), (Window::WindowSize.y / 2));
			firstClick = false;
		}

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = sensitivity * (float)(mouseY - (Window::WindowSize.y / 2)) / Window::WindowSize.y;
		float rotY = sensitivity * (float)(mouseX - (Window::WindowSize.x / 2)) / Window::WindowSize.x;

		vec3 newOrientation = rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		if (abs(angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}

		Orientation = rotate(Orientation, glm::radians(-rotY), Up);

		glfwSetCursorPos(window, (Window::WindowSize.x / 2), (Window::WindowSize.y  / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}

    c->ViewMatrix = lookAt(c->position, c->position + Orientation, Up);

}
