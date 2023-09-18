#include "Pch.h"
#include "GL/glew.h"
#include "graphics/ShaderManager.h"
namespace ShaderManager::internal
{
    std::unordered_map<std::string, GLuint> m_shaders;
    std::unordered_map<std::string, GLuint> m_linkedShaders;
}

namespace ShaderManager
{
    void Init()
    {
        ShaderManager::LoadShader("vertex_b", "assets/shaders/basic_v.glsl", GL_VERTEX_SHADER);
        ShaderManager::LoadShader("fragment_b", "assets/shaders/basic_f.glsl", GL_FRAGMENT_SHADER);

        LinkShader("Basic", "vertex_b", "fragment_b");
    }

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
        internal::m_shaders.insert(std::pair<std::string, GLuint>(name, shader));

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
    GLuint LinkShader(const std::string& linkedName, const std::string& vertexShader, const std::string& fragmentShader)
    {
        GLuint programId = glCreateProgram(); // crate a program

        if (programId == 0)
        {
            std::cout << "Error Creating Shader Program";
            return 0;
        }
        GLuint vertexShaderId = GetShader(vertexShader);
        GLuint fragmentShaderId = GetShader(fragmentShader);
        // Attach both the shaders to it
        glAttachShader(programId, vertexShaderId);
        glAttachShader(programId, fragmentShaderId);

        // Create executable of this program
        glLinkProgram(programId);

        GLint linkStatus;

        // Get the link status for this program
        glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);

        if (!linkStatus)
        { // If the linking failed
            std::cout << "Error Linking program";
            glDetachShader(programId, vertexShaderId);
            glDetachShader(programId, fragmentShaderId);
            glDeleteProgram(programId);

            return 0;
        }

        internal::m_linkedShaders.insert(std::pair<std::string, GLuint>(linkedName, programId));

        return programId;
    }

    GLuint GetLinkedShader(const std::string& name)
    {
        auto shader = internal::m_linkedShaders.find(name);
        if (shader == internal::m_linkedShaders.end())
        {
            std::cerr << "Linked Shader not found: " << name << std::endl;
            return 0;
        }
        else
        {
            return shader->second;
        }
    }

    void UseShader(GLuint index)
    {
        glUseProgram(index);
    }
}

