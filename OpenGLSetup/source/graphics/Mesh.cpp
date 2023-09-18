#include "Pch.h"
#include "GL/glew.h"
#include <gtc/type_ptr.hpp>
#include "graphics/Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const GLenum drawMode, const GLenum primativeType)
	: m_vertices(vertices), m_indices(indices), m_drawMode(drawMode), m_primitiveType(primativeType)
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ibo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

    // Create index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vertices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), reinterpret_cast<void*>(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));

    glBindVertexArray(0);
}

void Mesh::Draw(const GLuint shaderProgram, const glm::mat4& modelMatrix)
{
    // Bind the vertex array object
    glBindVertexArray(m_vao);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    // Ready to draw
    glDrawElements(m_primitiveType, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
    // Unbind the vertex array (although this isn't entirely necessary)
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    m_vertices.clear();
    m_indices.clear();

    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
}
