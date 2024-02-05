#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, glm::vec3 colors): 
    colors{colors}, vertices{vertices}, indices{indices}, vao{}, vbo{}, ebo{}
{
	setupMesh();
}

void Mesh::Draw(const Shader& shader)
{
    // draw mesh
    vao.bindVAO();
    shader.setVec3("uColor", colors);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
}

void Mesh::setupMesh()
{
	vao.bindVAO();
	vbo.bindVBO();
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STREAM_DRAW);
    ebo.bindEBO();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STREAM_DRAW);

    // set the vertex attribute pointers
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
}
