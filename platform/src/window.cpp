#include "platform/window.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "debug_utils/logger.h"

namespace platform 
{
Window::Window(int width, int height, const char* name)
{
	Window(width, height, name, false);
}
Window::Window(int width, int height, const char* name, bool fullscreen) 
{
	debug_utils::Logger& platformLogger = debug_utils::getLogger("platform");

	if (!m_hasInitGLFW) {
		if (!glfwInit())
		{
			platformLogger.log(debug_utils::LogLevel::ERROR, []() { return "Unable to init GLFW"; });
			return;
		}
		m_hasInitGLFW = true;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); for macOS

	m_window = glfwCreateWindow(width, height, name, fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
	if (!m_window) {
		platformLogger.log(debug_utils::LogLevel::ERROR, []() { return "Unable to create GLFW window"; });
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_window);
	
	if (!m_hasInitGLAD)
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			platformLogger.log(debug_utils::LogLevel::ERROR, []() { return "Unable to init GLAD"; });
			return;
		}
		m_hasInitGLAD = true;
	}		
}

Window::~Window() 
{
	if (m_window) 
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}
}

bool Window::isValid() const
{
	return m_window;
}

void Window::swapBuffers() const 
{
	glfwSwapBuffers(m_window);
}

void Window::pollEvents() const 
{
	glfwPollEvents();
}

bool Window::shouldClose() const 
{
	return glfwWindowShouldClose(m_window);
}
}