namespace ShaderManager
{
    void Init();

    /// <summary>
    /// This loads in the shader and return you the shader index
    /// </summary>
    /// <param name="name">the name what you will use to find it in the map</param>
    /// <param name="path">the path where this is stored in</param>
    /// <param name="type">the type of shader vertex, fragment, compute or etc shader</param>
    /// <returns>return the shader index</returns>
    GLuint LoadShader(const std::string& name, const std::string& path, GLenum type);

    // Get shader by path
    GLuint GetShader(const std::string& name);

    // Link the shaders to a program index
    GLuint LinkShader(const std::string& vertexShader, const std::string& fragmentShader);

    // Map of shaders
    std::unordered_map<std::string, GLuint> m_shaders;
}
