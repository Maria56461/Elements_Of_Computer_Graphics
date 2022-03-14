#include "object2D.h"

#include <vector>
#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateHexagon(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color),
        VertexFormat(corner + glm::vec3(length * 3 / 2, length / 2, 0), color),
        VertexFormat(corner + glm::vec3(- length * 3 / 2, length / 2, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 4, 2, 3, 5};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        indices.push_back(0);
        indices.push_back(5);
        indices.push_back(2);
        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(4);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangular(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length * 2, 0), color),
        VertexFormat(corner + glm::vec3(0, length * 2, 0), color),
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color),
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateProiectil(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(2 * length, 0, 0), color),
        VertexFormat(corner + glm::vec3(2 * length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color),
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateInamic(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float l,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(l / 2, -l, 0), color),
        VertexFormat(corner + glm::vec3(l, 0, 0), color),
        VertexFormat(corner + glm::vec3(2 * l, l / 2, 0), color),
        VertexFormat(corner + glm::vec3(l, l, 0), color),
        VertexFormat(corner + glm::vec3(l * 9 / 12, l / 5 + l, 0), color),
        VertexFormat(corner + glm::vec3(2 * l / 3, l / 3 + l, 0), color),
        VertexFormat(corner + glm::vec3(l / 2, l / 2 + l, 0), color),
        VertexFormat(corner + glm::vec3(l / 3 + l / 12, l / 3 + l, 0), color),
        VertexFormat(corner + glm::vec3(l / 3, l + l / 5, 0), color),
        VertexFormat(corner + glm::vec3(0, l, 0), color),
        VertexFormat(corner + glm::vec3(-l, l / 2, 0), color)
      //  VertexFormat(corner + glm::vec3(2 * l, - l / 2, 0), color),
       // VertexFormat(corner + glm::vec3(2 * l, l / 2, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 11};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(0);
        indices.push_back(9);
        indices.push_back(5);
        indices.push_back(2);
        indices.push_back(4);
        indices.push_back(5);
        indices.push_back(2);
        indices.push_back(0);
        indices.push_back(5);
        indices.push_back(5);
        indices.push_back(6);
        indices.push_back(7);
        indices.push_back(7);
        indices.push_back(5);
        indices.push_back(9);
        indices.push_back(9);
        indices.push_back(10);
        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(3);
        indices.push_back(4);
        indices.push_back(9);
        indices.push_back(10);
        indices.push_back(8);

    }
   
    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateCircle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float raza,
    glm::vec3 color) {

    glm::vec3 corner = leftBottomCorner;
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    float angle, x, y; 
    int i = 0;

    for (angle = 0.0f; angle <= (2.0f * 3.14); angle += 0.01f) {
        x = raza * cos(angle);
        y = raza * sin(angle);
        vertices.push_back(VertexFormat(corner + glm::vec3(x, y, 0), color));
        indices.push_back(i);
        i++;
    }

    Mesh* circle = new Mesh(name);
    circle->SetDrawMode(GL_LINE_LOOP);
    circle->InitFromData(vertices, indices);

    return circle;
}