#include "Utils.hpp"

SimpleObject Utils::generateBox(glm::vec3 position, const char* texturePath)
{
    std::vector<glm::vec3> positions{};

    positions.push_back(glm::vec3{ -0.5f, -0.5f, -0.5f });
    positions.push_back(glm::vec3{ 0.5f, -0.5f, -0.5f });
    positions.push_back(glm::vec3{ 0.5f, 0.5f, -0.5f });
    positions.push_back(glm::vec3{ 0.5f, 0.5f, -0.5f });
    positions.push_back(glm::vec3{ -0.5f, 0.5f, -0.5f });
    positions.push_back(glm::vec3{ -0.5f, -0.5f, -0.5f });

    positions.push_back(glm::vec3{ -0.5f, -0.5f, 0.5f });
    positions.push_back(glm::vec3{ 0.5f, -0.5f, 0.5f });
    positions.push_back(glm::vec3{ 0.5f, 0.5f, 0.5f });
    positions.push_back(glm::vec3{ 0.5f, 0.5f, 0.5f });
    positions.push_back(glm::vec3{ -0.5f, 0.5f, 0.5f });
    positions.push_back(glm::vec3{ -0.5f, -0.5f, 0.5f });

    positions.push_back(glm::vec3{ -0.5f, 0.5f, 0.5f });
    positions.push_back(glm::vec3{ -0.5f, 0.5f, -0.5f });
    positions.push_back(glm::vec3{ -0.5f, -0.5f, -0.5f });
    positions.push_back(glm::vec3{ -0.5f, -0.5f, -0.5f });
    positions.push_back(glm::vec3{ -0.5f, -0.5f, 0.5f });
    positions.push_back(glm::vec3{ -0.5f, 0.5f, 0.5f, });

    positions.push_back(glm::vec3{ 0.5f, 0.5f, 0.5f });
    positions.push_back(glm::vec3{ 0.5f, 0.5f, -0.5f });
    positions.push_back(glm::vec3{ 0.5f, -0.5f, -0.5f });
    positions.push_back(glm::vec3{ 0.5f, -0.5f, -0.5f });
    positions.push_back(glm::vec3{ 0.5f, -0.5f, 0.5f });
    positions.push_back(glm::vec3{ 0.5f, 0.5f, 0.5f });

    positions.push_back(glm::vec3{ -0.5f, -0.5f, -0.5f });
    positions.push_back(glm::vec3{ 0.5f, -0.5f, -0.5f });
    positions.push_back(glm::vec3{ 0.5f, -0.5f, 0.5f });
    positions.push_back(glm::vec3{ 0.5f, -0.5f, 0.5f });
    positions.push_back(glm::vec3{ -0.5f, -0.5f, 0.5f });
    positions.push_back(glm::vec3{ -0.5f, -0.5f, -0.5f });

    positions.push_back(glm::vec3{ -0.5f, 0.5f, -0.5f });
    positions.push_back(glm::vec3{ 0.5f, 0.5f, -0.5f });
    positions.push_back(glm::vec3{ 0.5f, 0.5f, 0.5f });
    positions.push_back(glm::vec3{ 0.5f, 0.5f, 0.5f });
    positions.push_back(glm::vec3{ -0.5f, 0.5f, 0.5f });
    positions.push_back(glm::vec3{ -0.5f, 0.5f, -0.5f });

    std::vector<glm::vec3> colors{};
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 1.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 0.0f, 1.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 1.0f, 0.0f });

    colors.push_back(glm::vec3{ 0.0f, 0.0f, 1.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 1.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 0.0f, 1.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });

    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 1.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 0.0f, 1.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 1.0f, 0.0f });

    colors.push_back(glm::vec3{ 0.0f, 0.0f, 1.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 1.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 0.0f, 1.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });

    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 1.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 0.0f, 1.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 1.0f, 0.0f });

    colors.push_back(glm::vec3{ 0.0f, 0.0f, 1.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 1.0f, 0.0f });
    colors.push_back(glm::vec3{ 0.0f, 0.0f, 1.0f });
    colors.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });

    std::vector<glm::vec2> textureCoordinates;
    textureCoordinates.push_back(glm::vec2{ 0.0f, 0.0f });
    textureCoordinates.push_back(glm::vec2{ 1.0f, 0.0f });
    textureCoordinates.push_back(glm::vec2{ 1.0f, 1.0f });
    textureCoordinates.push_back(glm::vec2{ 1.0f, 1.0f });
    textureCoordinates.push_back(glm::vec2{ 0.0f, 1.0f });
    textureCoordinates.push_back(glm::vec2{ 0.0f, 0.0f });

    textureCoordinates.push_back(glm::vec2{ 0.0f, 0.0f });
    textureCoordinates.push_back(glm::vec2{ 1.0f, 0.0f });
    textureCoordinates.push_back(glm::vec2{ 1.0f, 1.0f });
    textureCoordinates.push_back(glm::vec2{ 1.0f, 1.0f });
    textureCoordinates.push_back(glm::vec2{ 0.0f, 1.0f });
    textureCoordinates.push_back(glm::vec2{ 0.0f, 0.0f });

    textureCoordinates.push_back(glm::vec2{ 1.0f, 0.0f });
    textureCoordinates.push_back(glm::vec2{ 1.0f, 1.0f });
    textureCoordinates.push_back(glm::vec2{ 0.0f, 1.0f });
    textureCoordinates.push_back(glm::vec2{ 0.0f, 1.0f });
    textureCoordinates.push_back(glm::vec2{ 0.0f, 0.0f });
    textureCoordinates.push_back(glm::vec2{ 1.0f, 0.0f });

    textureCoordinates.push_back(glm::vec2{ 1.0f, 0.0f });
    textureCoordinates.push_back(glm::vec2{ 1.0f, 1.0f });
    textureCoordinates.push_back(glm::vec2{ 0.0f, 1.0f });
    textureCoordinates.push_back(glm::vec2{ 0.0f, 1.0f });
    textureCoordinates.push_back(glm::vec2{ 0.0f, 0.0f });
    textureCoordinates.push_back(glm::vec2{ 1.0f, 0.0f });

    textureCoordinates.push_back(glm::vec2{ 0.0f, 1.0f });
    textureCoordinates.push_back(glm::vec2{ 1.0f, 1.0f });
    textureCoordinates.push_back(glm::vec2{ 1.0f, 0.0f });
    textureCoordinates.push_back(glm::vec2{ 1.0f, 0.0f });
    textureCoordinates.push_back(glm::vec2{ 0.0f, 0.0f });
    textureCoordinates.push_back(glm::vec2{ 0.0f, 1.0f });

    textureCoordinates.push_back(glm::vec2{ 0.0f, 1.0f });
    textureCoordinates.push_back(glm::vec2{ 1.0f, 1.0f });
    textureCoordinates.push_back(glm::vec2{ 1.0f, 0.0f });
    textureCoordinates.push_back(glm::vec2{ 1.0f, 0.0f });
    textureCoordinates.push_back(glm::vec2{ 0.0f, 0.0f });
    textureCoordinates.push_back(glm::vec2{ 0.0f, 1.0f });

    return SimpleObject{ positions, colors, textureCoordinates, position, texturePath };
}

SmoothObject Utils::generateBezier(glm::vec3 position, const char* texturePath, int triangles)
{
    return SmoothObject(triangles, triangles, triangles, triangles, position, texturePath);
}
