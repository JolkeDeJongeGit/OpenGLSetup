#include "Pch.h"
#include "GL/glew.h"
#include <gtc/type_ptr.hpp>
#include "graphics/Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const GLenum drawMode, const GLenum primativeType)
	: m_vertices(vertices), m_indices(indices), m_drawMode(drawMode), m_primitiveType(primativeType)
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

    // Create index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}


Mesh::~Mesh()
{
    m_vertices.clear();
    m_indices.clear();

    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}

void Mesh::Draw(const GLuint shaderProgram, const glm::mat4& modelMatrix)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    // Bind the vertex array object
    glBindVertexArray(m_vao);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Ready to draw
    glDrawElements(m_primitiveType, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, 0);
    // Unbind the vertex array (although this isn't entirely necessary)
    glBindVertexArray(0);
}

