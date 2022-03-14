#include "lab_m1/lab2/lab2.h"
#include <vector>
#include <iostream>
#include "core/engine.h"
#include "utils/gl_utils.h"

using namespace std;
using namespace m1;

Lab2::Lab2()
{
}

Lab2::~Lab2()
{
}

void Lab2::Init() {
    cullFace = GL_BACK;
    polygonMode = GL_FILL;

    // Load a mesh from file into GPU memory
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        vector<VertexFormat> vertices_tetraedru
        {
            VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
            // pozitie, culoare, normala
            VertexFormat(glm::vec3(1, 0,  0), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 1,  0), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
        };

        vector<unsigned int> indices_tetraedru = {
            0, 1, 2,    // indices for first triangle
            1, 3, 2,    // indices for second triangle
            0, 2, 3,
            0, 3, 1
        };

        // meshes["tetraedru"] = new Mesh("generated cube 1");
        // meshes["tetraedru"]->InitFromData(vertices, indices);
        CreateMesh("tetraedru", vertices_tetraedru, indices_tetraedru);
        
        vector<VertexFormat> vertices_cub {
            VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, 0,  1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 1,  1), glm::vec3(1, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, 1,  1), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, 0,  0), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 1,  0), glm::vec3(0, 0, 0.5), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, 1,  0), glm::vec3(0.5, 1, 0), glm::vec3(0.2, 0.8, 0.6)),
        };

        vector<unsigned int> indices_cub = {
            0, 1, 2,    // indices for first triangle
            1, 3, 2,    // indices for second triangle
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4
        };

        CreateMesh("cub", vertices_cub, indices_cub);

        vector<VertexFormat> vertices_patrat{
            VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, 0,  0), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 1,  0), glm::vec3(1, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, 1,  0), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)),
        };

        vector<unsigned int> indices_patrat = {
            0, 1, 2,    
            2, 3, 1
        };

        CreateMesh("patrat", vertices_patrat, indices_patrat);
    }

    // TODO(student): Create a square using two triangles with
    // opposing vertex orientations.

}


void Lab2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices)
{
    unsigned int VAO = 0;
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO = 0;
    glGenBuffers(1, &VBO); // generare
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // activare
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

    unsigned int IBO = 0;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
   
    if (GetOpenGLError() == GL_INVALID_OPERATION)
    {
        cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
        cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
    }

    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
}


void Lab2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab2::Update(float deltaTimeSeconds)
{
    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
    glEnable(GL_CULL_FACE);
    // fata din spate--> sensul acelor de ceas
    // fata la vedere--> sensul trigonometric

    // Render an object using face normals for color
    RenderMesh(meshes["box"], shaders["VertexNormal"], glm::vec3(0, 0.5f, -1.5f), glm::vec3(0.75f));

    // Render an object using colors from vertex
    RenderMesh(meshes["tetraedru"], shaders["VertexColor"], glm::vec3(-1.5f, 0.5f, 0), glm::vec3(0.25f));
    RenderMesh(meshes["cub"], shaders["VertexColor"], glm::vec3(-5, 5, 2), glm::vec3(0.25f));
    RenderMesh(meshes["patrat"], shaders["VertexColor"], glm::vec3(-3, 3, 1), glm::vec3(0.25f));
    // TODO(student): Disable face culling
}

void Lab2::FrameEnd()
{
    DrawCoordinateSystem();
}

/*  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`. */

void Lab2::OnInputUpdate(float deltaTime, int mods)
{
}

void Lab2::OnKeyPress(int key, int mods)
{
    // TODO(student): Switch between GL_FRONT and GL_BACK culling.
    // Save the state in `cullFace` variable and apply it in the
    // `Update()` method, NOT here!

    if (key == GLFW_KEY_F2) {
        if (cullFace == GL_BACK)
            cullFace = GL_FRONT;
        else
            cullFace = GL_BACK;

        glCullFace(cullFace);
    }

    if (key == GLFW_KEY_SPACE)
    {
        switch (polygonMode)
        {
        case GL_POINT:
            polygonMode = GL_FILL;
            break;
        case GL_LINE:
            polygonMode = GL_POINT;
            break;
        default:
            polygonMode = GL_LINE;
            break;
        }
    }
}


void Lab2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab2::OnWindowResize(int width, int height)
{
}
