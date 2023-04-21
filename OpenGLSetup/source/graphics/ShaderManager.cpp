#include "Pch.h"
#include "GL/glew.h"
#include "graphics/ShaderManager.h"
namespace ShaderManager::internal
{
    std::unordered_map<std::string, GLuint> m_shaders;
}


namespace ShaderManager
{
    GLuint LoadShader(const std::string& name, const std::string& path, GLenum type)
    {
        // Read file
        std::ifstream shaderFile(path);
        if (!shaderFile)
        {
            std::cerr << "Failed to open shader file: " << path << std::endl;
            return 0;
        }

        std::stringstream shaderSourceStream;
        shaderSourceStream << shaderFile.rdbuf();
        std::string shaderSource = shaderSourceStream.str();

        // Compile shader
        const char* shaderSourcePtr = shaderSource.c_str();
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &shaderSourcePtr, NULL);
        glCompileShader(shader);

        // Check for compilation errors
        GLint success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[512];
            glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
            std::cerr << "Failed to compile shader: " << path << std::endl << infoLog << std::endl;
            glDeleteShader(shader);
            return 0;
        }

        // Add shader to map
        internal::m_shaders[name] = shader;

        return shader;
    }

    GLuint GetShader(const std::string& name)
    {
        auto shader = internal::m_shaders.find(name);
        if (shader == internal::m_shaders.end())
        {
            std::cerr << "Shader not found: " << name << std::endl;
            return 0;
        }

        return shader->second;
    }
}

