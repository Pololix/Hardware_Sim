#pragma once

struct GLFWwindow;

namespace platform {
class Window {
public:
	Window(int width, int height, const char* name);
	Window(int width, int height, const char* name, bool fullscreen);
	~Window();

	void swapBuffers() const;
	void pollEvents() const;
	bool shouldClose() const;

	bool isValid() const;
private:
	inline static bool m_hasInitGLFW = false;
	inline static bool m_hasInitGLAD = false;

	GLFWwindow* m_window = nullptr;
};
}