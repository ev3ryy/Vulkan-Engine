#include "Window.h"

#include <stdexcept>

namespace Engine {
	Window::Window(int w, int h, std::string name) : width{ w }, height{ h }, windowName{ name } {
		InitWindow();
	}

	Window::~Window() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Window::InitWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
	}

	void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
		auto MainWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		MainWindow->frameBufferResized = true;
		MainWindow->width = width;
		MainWindow->height = height;

	}

	void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
	}
}