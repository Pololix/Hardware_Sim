#include "graphics/shader_program.h"

#include <glad/glad.h>
#include <fstream>

#include "debug_utils/logger.h"

namespace graphics
{
ShaderProgram::ShaderProgram(ProgramType type, const std::filesystem::path& sourceDir)
	: m_ID(glCreateProgram()), m_type(type)
{
	loadShadersFromDir(sourceDir);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_ID);
}

void ShaderProgram::use() const
{
	glUseProgram(m_ID);
}

void ShaderProgram::loadShadersFromDir(const std::filesystem::path& sourceDir) 
{
	debug_utils::Logger& graphicsLogger = debug_utils::getLogger("graphics");

	for (auto& entry : std::filesystem::directory_iterator(sourceDir))
	{
		if ((m_type == ProgramType::Compute && entry.path().extension() == ".comp") ||
			(m_type == ProgramType::Graphics && (entry.path().extension() == ".vert" || entry.path().extension() == ".frag")))
		{
			std::ifstream inFile(entry.path());
			if (!inFile)
			{
				graphicsLogger.log(debug_utils::LogLevel::ERROR, [&entry]() { return "Unable to load shader from " + entry.path().string(); });
			}
			else
			{
				graphicsLogger.log(debug_utils::LogLevel::INFO, [&entry]() { return "Loaded shader from " + entry.path().string(); });
			}

			std::stringstream buffer;
			buffer << inFile.rdbuf();

			std::string stringSource = buffer.str();
			const char* cStringSource = stringSource.c_str();

			shaderHandle shader = glCreateShader(
				entry.path().extension() == ".comp" ? GL_COMPUTE_SHADER :
				entry.path().extension() == ".vert" ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

			glShaderSource(shader, 1, &cStringSource, nullptr);
			glCompileShader(shader);

			int compileOutcome = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compileOutcome);
			if (compileOutcome == GL_FALSE)
			{
				int logLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

				std::string msg(logLength, '\n');
				glGetShaderInfoLog(shader, logLength, nullptr, msg.data());
				graphicsLogger.log(debug_utils::LogLevel::ERROR, [&msg]() { return "Unable to compile shader: " + msg; });

				glDeleteShader(shader);
				continue;
			}
			else
			{
				graphicsLogger.log(debug_utils::LogLevel::ERROR, []() { return "Shader compiled successfully"; });

				glAttachShader(m_ID, shader);
				glDeleteShader(shader);
			}
		}
	}

	glLinkProgram(m_ID);

	int linkOutcome = 0;
	glGetProgramiv(m_ID, GL_LINK_STATUS, &linkOutcome);
	if (linkOutcome == GL_FALSE)
	{
		int logLength = 0;
		glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &logLength);
		std::string message(logLength, '\n');

		glGetProgramInfoLog(m_ID, logLength, nullptr, message.data());
		graphicsLogger.log(debug_utils::LogLevel::ERROR, [&message]() { return message; });
	}
	else
	{
		graphicsLogger.log(debug_utils::LogLevel::INFO, []() { return "Shader program linked successfully"; });
	}
}
}