#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Shader.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"

#define MAX_BONE_INFLUENCE 4

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
};

class Mesh {
public:
    // mesh data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    glm::vec3 colors;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, glm::vec3 colors);
    void Draw(const Shader& shader);
    VAO vao;
    VBO vbo;
    EBO ebo;
    void setupMesh();
private:
    //  render data


};