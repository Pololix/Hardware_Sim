#pragma once

//TODO: add resource loading system -> fstream

#include <filesystem>

namespace graphics
{
using shaderHandle = uint32_t;

enum class ProgramType : uint8_t
{
	Graphics, 
	Compute
};

class ShaderProgram
{
public:
	ShaderProgram(ProgramType type, const std::filesystem::path& sourceDir);
	~ShaderProgram();

	void use() const;
private:
	uint32_t m_ID;
	ProgramType m_type;

	void loadShadersFromDir(const std::filesystem::path& sourceDir);
};
}