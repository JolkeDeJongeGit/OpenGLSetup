#pragma once

struct Vertex {
    Vertex(const glm::vec3& inPosition, const glm::vec3& inNormal, const glm::vec2& inTexCoord)
        : position(inPosition), normal(inNormal), texCoord(inTexCoord)
    {}

    Vertex(const float inPositionX, const float inPositionY, const float inPositionZ,
        const float inNormalX, const float inNormalY, const float inNormalZ,
        const float inTexCoordX, const float inTexCoordY)
        : position(glm::vec3(inPositionX, inPositionY, inPositionZ)), normal(glm::vec3(inNormalX, inNormalY, inNormalZ)), texCoord(glm::vec2(inTexCoordX, inTexCoordY))
    {}

    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

class Mesh {
public:
    Mesh() = default;
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const GLenum drawMode = GL_STATIC_DRAW, const GLenum primativeType = GL_TRIANGLES);
    ~Mesh();
    void Draw(const GLuint shaderProgram, const glm::mat4& modelMatrix);
private:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    GLenum m_drawMode;
    GLenum m_primitiveType;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ibo;
};
