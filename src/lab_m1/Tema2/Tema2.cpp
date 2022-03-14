#include "lab_m1/Tema2/Tema2.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
using namespace m1;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices,
    const std::vector<unsigned int>& indices) {

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

    if (GetOpenGLError() == GL_INVALID_OPERATION) {
        cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
        cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
    }

    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
}

void Tema2::Init() {

    ifstream file;
    int r = rand() % 3 + 1;
    string filename3 = to_string(r);
    string filename = "C:\\Users\\maria\\Downloads\\gfx-framework-master\\gfx-framework-master\\src\\lab_m1\\Tema2\\labirint";
    string filename2 = filename.append(filename3);
    string filename4 = filename2.append(".txt");
    file.open(filename4, ios::in);
    camera = new implemented::camera();
    translateX = 0;
    translateY = 0;
    translateZ = 0;
    translateZsph = 0;
    mode = 0;
    var = 0;
    angle = 0;
    x = 0;
    z = 0;
    param1 = 0;
    param2 = 0;
    for (int i = 0; i < 576; i++) {
        initialPositions[i] = glm::vec3(0, 0, 0);
    }
    if (file.is_open() == true) {
        char myChar;
        int array[576];
        int aux = 0, aux1 = 0;
        while (file) {
            myChar = file.get();
            if (myChar == '1') {
                array[aux] = 1;
                aux++;
            }
            else if (myChar == '2') {
                array[aux] = 2;
                aux++;
            }
            else if (myChar == '0') {
                array[aux] = 0;
                aux++;
            }
        }
        file.close();
        for (int i = 0; i < 24; i++) {
            for (int j = 0; j < 24; j++) {
                maze[i][j] = array[aux1];
                 cout << maze[i][j] << " ";
                aux1++;
            }
        }
    }
    else {
        cout << "Eroare la deschiderea fisierului!" << endl;
    }
    cout << endl; 

    int b = 0;
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 24; j++) {
            if (maze[i][j] == 0) {
                // pozitie valida initiala pentru personaj
                initialPositions[b] = glm::vec3(i, j, 1);
                b++; 
            }
        }
    }

    a = 0;
    for (int i = 0; i < 576; i++) {
        if (initialPositions[i].z == 1) {
            a++;
        }
    }
    i = rand() % a;
   


    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    vector<VertexFormat> vertices_cub1 {
        VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0, 0, 0), glm::vec3(0.9, 0.7, 0.5)),
        VertexFormat(glm::vec3(1, 0,  1), glm::vec3(0, 0, 0), glm::vec3(0.9, 0.7, 0.5)),
        VertexFormat(glm::vec3(0, 1,  1), glm::vec3(0, 0, 0), glm::vec3(0.9, 0.7, 0.5)),
        VertexFormat(glm::vec3(1, 1,  1), glm::vec3(0, 0, 0), glm::vec3(0.9, 0.7, 0.5)),
        VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 0, 0), glm::vec3(0.9, 0.7, 0.5)),
        VertexFormat(glm::vec3(1, 0,  0), glm::vec3(0, 0, 0), glm::vec3(0.9, 0.7, 0.5)),
        VertexFormat(glm::vec3(0, 1,  0), glm::vec3(0, 0, 0), glm::vec3(0.9, 0.7, 0.5)),
        VertexFormat(glm::vec3(1, 1,  0), glm::vec3(0, 0, 0), glm::vec3(0.9, 0.7, 0.5)),
    };

    vector<unsigned int> indices_cub1 = {
        0, 1, 2,    
        1, 3, 2,    
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

    CreateMesh("cub1", vertices_cub1, indices_cub1);
    
    vector<VertexFormat> vertices_cub2{
        VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.7, 0.3)),
        VertexFormat(glm::vec3(1, 0,  1), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.7, 0.3)),
        VertexFormat(glm::vec3(0, 1,  1), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.7, 0.3)),
        VertexFormat(glm::vec3(1, 1,  1), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.7, 0.3)),
        VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.7, 0.3)),
        VertexFormat(glm::vec3(1, 0,  0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.7, 0.3)),
        VertexFormat(glm::vec3(0, 1,  0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.7, 0.3)),
        VertexFormat(glm::vec3(1, 1,  0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.7, 0.3)),
    };

    CreateMesh("cub2", vertices_cub2, indices_cub1);

    vector<VertexFormat> vertices_cub3{
        VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0, 0, 0), glm::vec3(0.3, 0.1, 1)),
        VertexFormat(glm::vec3(1, 0,  1), glm::vec3(0, 0, 0), glm::vec3(0.3, 0.1, 1)),
        VertexFormat(glm::vec3(0, 1,  1), glm::vec3(0, 0, 0), glm::vec3(0.3, 0.1, 1)),
        VertexFormat(glm::vec3(1, 1,  1), glm::vec3(0, 0, 0), glm::vec3(0.3, 0.1, 1)),
        VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 0, 0), glm::vec3(0.3, 0.1, 1)),
        VertexFormat(glm::vec3(1, 0,  0), glm::vec3(0, 0, 0), glm::vec3(0.3, 0.1, 1)),
        VertexFormat(glm::vec3(0, 1,  0), glm::vec3(0, 0, 0), glm::vec3(0.3, 0.1, 1)),
        VertexFormat(glm::vec3(1, 1,  0), glm::vec3(0, 0, 0), glm::vec3(0.3, 0.1, 1)),
    };

    CreateMesh("cub3", vertices_cub3, indices_cub1);

    vector<VertexFormat> vertices_cub4{
        VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0.9)),
        VertexFormat(glm::vec3(1, 0,  1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0.9)),
        VertexFormat(glm::vec3(0, 1,  1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0.9)),
        VertexFormat(glm::vec3(1, 1,  1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0.9)),
        VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0.9)),
        VertexFormat(glm::vec3(1, 0,  0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0.9)),
        VertexFormat(glm::vec3(0, 1,  0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0.9)),
        VertexFormat(glm::vec3(1, 1,  0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0.9)),
    };

    CreateMesh("cub4", vertices_cub4, indices_cub1);

    vector<VertexFormat> vertices_cub5{
        VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0, 0, 0), glm::vec3(0.9, 0.1, 0.7)),
        VertexFormat(glm::vec3(1, 0,  1), glm::vec3(0, 0, 0), glm::vec3(0.9, 0.1, 0.7)),
        VertexFormat(glm::vec3(0, 1,  1), glm::vec3(0, 0, 0), glm::vec3(0.9, 0.1, 0.7)),
        VertexFormat(glm::vec3(1, 1,  1), glm::vec3(0, 0, 0), glm::vec3(0.9, 0.1, 0.7)),
        VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 0, 0), glm::vec3(0.9, 0.1, 0.7)),
        VertexFormat(glm::vec3(1, 0,  0), glm::vec3(0, 0, 0), glm::vec3(0.9, 0.1, 0.7)),
        VertexFormat(glm::vec3(0, 1,  0), glm::vec3(0, 0, 0), glm::vec3(0.9, 0.1, 0.7)),
        VertexFormat(glm::vec3(1, 1,  0), glm::vec3(0, 0, 0), glm::vec3(0.9, 0.1, 0.7)),
    };

    CreateMesh("cub5", vertices_cub5, indices_cub1);

    camera->Set(glm::vec3(initialPositions[i].x, 4, initialPositions[i].y), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    camera->TranslateForward(-5);

    {
        Mesh* mesh = new Mesh("oildrum");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "props"), "oildrum.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    angle1 = 0; 
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
  
}

void Tema2::FrameStart() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds) {

    angle1 += deltaTimeSeconds * 1.2f;
    if ((param1 <= 0.2f) && (param1 >= -0.2f)) {
        param1 += deltaTimeSeconds * 1.1f;
    }
    else if ((param2 <= 0.2f) && (param2 >= -0.2f)) {
        param2 += deltaTimeSeconds * 1.1f;
    }
    else {
        param1 = 0;
        param2 = 0;
    }

    {
        for (int i = 0; i < 24; i++) {
            for (int j = 0; j < 24; j++) {
                if (maze[i][j] == 1) {
                    // perete
                    glm::mat4 modelMatrix = glm::mat4(1);
                    modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 0, j));
                    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1.5f, 1));
                    RenderMesh(meshes["cub4"], shaders["VertexNormal"], modelMatrix);
                }
                else if ((maze[i][j] == 2) || (maze[j][i] == 2)) {
                    // inamic 
                    glm::mat4 modelMatrix1 = glm::mat4(1);
                    modelMatrix1 = glm::translate(modelMatrix1, glm::vec3(i, 0, j));
                    modelMatrix1 = glm::scale(modelMatrix1, glm::vec3(1, 0, 1));
                    RenderMesh(meshes["cub5"], shaders["VertexNormal"], modelMatrix1);
                    glm::mat4 modelMatrix = glm::mat4(1);
                    modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 0, j));
                    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f, 0, -0.5f));
                    modelMatrix = glm::translate(modelMatrix, glm::vec3(param1, 0, 0));
                    modelMatrix = glm::translate(modelMatrix, glm::vec3(-param2, 0, 0));
                    modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2, 1.2, 1.2));
                    modelMatrix = glm::rotate(modelMatrix, angle1, glm::vec3(0, 1, 0));
                    RenderMesh(meshes["oildrum"], shaders["VertexNormal"], modelMatrix);
                }
                else {
                    glm::mat4 modelMatrix = glm::mat4(1);
                    modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 0, j));
                    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0, 1));
                    RenderMesh(meshes["cub5"], shaders["VertexNormal"], modelMatrix);
                }
                
            }
        }
    }

    for (int i = 0; i < proiectile.size(); i++) {
        Proiectil2* proiectil = proiectile.at(i);
        proiectil->translateZ += 5 * deltaTimeSeconds;;
        glm::mat4 modelMatrix = glm::mat4(1);
        proiectil->pos = camera->position;
        modelMatrix = glm::translate(modelMatrix, proiectil->pos);
        modelMatrix = glm::translate(modelMatrix, proiectil->dir * proiectil->translateZ);
        RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.4f + translateX, 1 + translateY, translateZ));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(initialPositions[i].x, 0, initialPositions[i].y));
        if (var % 2 == 1) {
            modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.05f, 0, 0.4f));  
        }
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.35f, 0.3f, 0.7f));
        RenderMesh(meshes["cub1"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.75f + translateX, 1 + translateY, translateZ));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(initialPositions[i].x, 0, initialPositions[i].y));
        if (var % 2 == 1) {
            modelMatrix = glm::rotate(modelMatrix, RADIANS(-90.0f), glm::vec3(0, 1, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.75f, 0, 0.05f));
        }
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.35f, 0.3f, 0.7f));
        RenderMesh(meshes["cub1"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.75f + translateX, 1.3f + translateY, translateZ));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(initialPositions[i].x, 0, initialPositions[i].y));
        if (var % 2 == 1) {
            modelMatrix = glm::rotate(modelMatrix, RADIANS(-90.0f), glm::vec3(0, 1, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.75f, 0, 0.05f));
        }
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.35f, 0.7f, 0.7f));
        RenderMesh(meshes["cub2"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.4f + translateX, 1.3f + translateY, translateZ));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(initialPositions[i].x, 0, initialPositions[i].y));
        if (var % 2 == 1) {
            modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.05f, 0, 0.4f));
        }
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.35f, 0.7f, 0.7f));
        RenderMesh(meshes["cub2"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.4 + translateX, translateY, translateZ));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(initialPositions[i].x, 0, initialPositions[i].y));
        if (var % 2 == 1) {
            modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 0.4f, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.7f, 0, -0.4f));
        }
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f, 1, 0.7f));
        RenderMesh(meshes["cub3"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(translateX, translateY, translateZ));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(initialPositions[i].x, 0, initialPositions[i].y));
        if (var % 2 == 1) {
            modelMatrix = glm::rotate(modelMatrix, RADIANS(-90.0f), glm::vec3(0, 1, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -0.7f));
        }
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f, 1, 0.7f));
        RenderMesh(meshes["cub3"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(translateX, 1 + translateY, translateZ));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(initialPositions[i].x, 0, initialPositions[i].y));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.7f, 1, 0.7f));
        RenderMesh(meshes["cub2"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.1f + translateX, 2 + translateY, 0.1f + translateZ));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(initialPositions[i].x, 0, initialPositions[i].y));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
        RenderMesh(meshes["cub1"], shaders["VertexNormal"], modelMatrix);
    }

  
    
}

void Tema2::FrameEnd() {
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) {
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}

void Tema2::OnInputUpdate(float deltaTime, int mods) {
   
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
        // camera controlata din mouse independent de miscarea personajului  

        float cameraSpeed = 2.0f;

        if (window->KeyHold(GLFW_KEY_W)) {
            camera->MoveForward(cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            camera->TranslateRight(-cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            camera->MoveForward(-cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            camera->TranslateRight(cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            camera->TranslateUpward(cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_E)) {
            camera->TranslateUpward(-cameraSpeed * deltaTime);
        }
    }
    else {

        float cameraSpeed = 2.0f;

        if (window->KeyHold(GLFW_KEY_W)) {
            camera->MoveForward(cameraSpeed * deltaTime);
            translateZ -= deltaTime * cameraSpeed;
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            camera->TranslateRight(-cameraSpeed * deltaTime);
            translateX -= deltaTime * cameraSpeed;
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            camera->MoveForward(-cameraSpeed * deltaTime);
            translateZ += deltaTime * cameraSpeed;
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            camera->TranslateRight(cameraSpeed * deltaTime);
            translateX += deltaTime * cameraSpeed;
        }

    }
}

void Tema2::OnKeyPress(int key, int mods) {

    if ((key == GLFW_KEY_A || key == GLFW_KEY_D) && !(window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))) {
        if (var % 2 == 0) {
            var = var + 1;
        }
    }
    if ((key == GLFW_KEY_W || key == GLFW_KEY_S) && !(window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))) {
        if (var % 2 == 1) {
            var = var + 1;
        }
    }
    if ((key == GLFW_KEY_LEFT_CONTROL) || (key == GLFW_KEY_RIGHT_CONTROL)) {
        if (mode == 0) {
            mode = 1;
            camera->prevForward = camera->forward;
           // camera->position += glm::vec3(0, 0, -1) * camera->distanceToTarget;
            camera->TranslateForward(camera->distanceToTarget);
        }
        else {
            mode = 0; 
           // camera->position -= glm::vec3(0, 0, -1) * camera->distanceToTarget;
            camera->forward = camera->prevForward;
            camera->TranslateForward(- camera->distanceToTarget);
        }
    }
    if (key == GLFW_KEY_SPACE) {
        float x = camera->forward.x;
        float z = camera->forward.z;
        Proiectil2* proiectil = new Proiectil2(translateZsph);
        proiectil->dir = glm::vec3(x, camera->forward.y, z);
        proiectile.push_back(proiectil);
    }
}

void Tema2::OnKeyRelease(int key, int mods)
{
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {

    angle = -deltaX * 0.001f;

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (mode == 1) {
            camera->RotateFirstPerson_OX(-deltaY * sensivityOY);
            camera->RotateFirstPerson_OY(-deltaX * sensivityOX);
        }

        if (mode == 0) {
            camera->RotateThirdPerson_OX(-deltaY * sensivityOY);
            camera->RotateThirdPerson_OY(-deltaX * sensivityOX);
        }
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        Proiectil2* proiectil = new Proiectil2(translateZsph);
        float x = camera->forward.x;
        float z = camera->forward.z;
        proiectil->dir = glm::normalize(glm::vec3(camera->forward.x, 0, camera->forward.z));
        proiectile.push_back(proiectil);
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}