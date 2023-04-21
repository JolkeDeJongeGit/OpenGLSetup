#pragma once

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

class Mesh {
public:
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
    GLuint m_ebo;
};
