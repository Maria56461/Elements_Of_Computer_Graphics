#include "lab_m1/Tema1/Tema1.h"
#include <vector>
#include <iostream>
 #include "lab_m1/Tema1/transform2D.h"
 #include "lab_m1/Tema1/object2D.h"
#include <time.h>       

using namespace std;
using namespace m1;
float lineSide1 = 5;    // latura obiectelor create 
float lineSide3 = 2.5;
float lineSide2 = 250;  // latura hartii

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init() {

    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    logicSpace.x = 0;
    logicSpace.y = 0;
    logicSpace.width = 128;
    logicSpace.height = 72;

    corner = glm::vec3(logicSpace.width / 2, logicSpace.height / 2, 0);
    translateX = 0;
    translateY = 0;
    translateX1 = 0;
    translateY1 = 0;
    translateXi = 0;
    translateYi = 0;
    scaleX = 1;
    scaleY = 1;

    timer = 0;

    srand(time(NULL));

    angle = 0;
    angle2 = 0;
    i = 0;

    Mesh* hexagon1 = object2D::CreateHexagon("hexagon1", corner, lineSide1, glm::vec3(1, 0, 0), true);
    AddMeshToList(hexagon1);

    Mesh* rectangular1 = object2D::CreateRectangular("rectangular1", corner, lineSide1,
        glm::vec3(0.5, 0, 0.5), true);
    AddMeshToList(rectangular1);

    Mesh* square1 = object2D::CreateSquare("square1", corner, lineSide1 / 2, glm::vec3(0, 1, 0), true);
    AddMeshToList(square1);
    // cele 3 primitive pentru jucator 

    Mesh* rectangular7 = object2D::CreateRectangular("rectangular7", corner, lineSide2,
        glm::vec3(0.4, 0.3, 1), false);
    AddMeshToList(rectangular7);
    Mesh* rectangular2 = object2D::CreateRectangular("rectangular2", corner, lineSide2,
        glm::vec3(0, 0, 1), true);
    AddMeshToList(rectangular2);
    // harta de joc 

    Mesh* rectangular6 = object2D::CreateProiectil("rectangular6", corner, lineSide3,
        glm::vec3(0, 0, 0), true);
    AddMeshToList(rectangular6);
    // proiectil 

    Mesh* square2 = object2D::CreateSquare("square2", corner, lineSide1, glm::vec3(0.8, 0.2, 0.5), true);
    AddMeshToList(square2);

    Mesh* square3 = object2D::CreateSquare("square3", corner, lineSide1, glm::vec3(0.8, 0.1, 0.6), true);
    AddMeshToList(square3);

    Mesh* square4 = object2D::CreateSquare("square4", corner, lineSide1, glm::vec3(0.9, 0.1, 0.6), true);
    AddMeshToList(square4);

    Mesh* square5 = object2D::CreateSquare("square5", corner, lineSide1, glm::vec3(1, 0.5, 0.9), false);
    AddMeshToList(square5);

    Mesh* square6 = object2D::CreateSquare("square6", corner, lineSide1, glm::vec3(1, 0, 0.4), false);
    AddMeshToList(square6);

    Mesh* square7 = object2D::CreateSquare("square7", corner, lineSide1, glm::vec3(1, 0.4, 0.6), true);
    AddMeshToList(square7);

    Mesh* square8 = object2D::CreateSquare("square8", corner, lineSide1, glm::vec3(0.9, 0.5, 1), false);
    AddMeshToList(square8);

    Mesh* inamic1 = object2D::CreateInamic("inamic1", corner, lineSide1, glm::vec3(0.9, 0.6, 0.2), true);
    AddMeshToList(inamic1);

    glLineWidth(15); 

}

void Tema1::FrameStart() {
    
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds) {
   
    glm::ivec2 resolution = window->GetResolution();
    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0), true);
  
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);

    timer += deltaTimeSeconds;

    if (timer > 5) {
        int a = rand() % 90 + 1 - rand() % 90;
        int b = rand() % 180 + 1 - rand() % 180;
        Inamic *inamic = new Inamic(a, b);
        inamici.push_back(inamic);
       timer = 0;
    }

    for (int i = 0; i < inamici.size(); i++) {
        Inamic* inamic = inamici.at(i);
       // float x_i = inamic->translateX / sqrt(inamic->translateX * inamic->translateX + inamic->translateY * inamic->translateY);
      //  float y_i = inamic->translateY / sqrt(inamic->translateX * inamic->translateX + inamic->translateY * inamic->translateY);
       // translateXi += x_i * 7 * deltaTimeSeconds;
      //  translateYi += y_i * 7 * deltaTimeSeconds;
      //  float coordX, coordY;
      //  coordX = - inamic->translateX;
      //  coordY = - inamic->translateY;
      //  angle2 = atan2(coordY, coordX);
        translateXi += cos(inamic->angle) * 7 * deltaTimeSeconds;
        translateYi += sin(inamic->angle) * 7 * deltaTimeSeconds;
        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix * transform2D::Translate(inamic->translateX, inamic->translateY);
     //   modelMatrix *= transform2D::Translate(translateXi, translateYi);
    //    modelMatrix *= transform2D::Translate(translateXi, translateYi);
    //    modelMatrix *= transform2D::Rotate(angle2);
        RenderMesh2D(meshes["inamic1"], shaders["VertexColor"], modelMatrix);
    }
   
    for (float i = 0.1; i <= 3; i = i + 0.1) {
        float k, l;
        int j = 10 * i, m;
        if (j % 2 == 0) {
            m = 0;
            k = 0.7;
            if (j % 4 == 0) {
                l = 0.2;
            }
            else {
                l = 0;
            }
        }
        else {
            k = 0.8;
            if (j % 4 == 1) {
                m = 6;
                l = 0.1;
            }
            else {
                l = 0.3;
                m = -6;
            }
        }
        Mesh* circle = object2D::CreateCircle("circle", corner, lineSide1, glm::vec3(k, l, i / 3));
        AddMeshToList(circle);
        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix * transform2D::Translate(110, -110) * transform2D::Translate(j + 2, m) * transform2D::Scale(0.5, 0.5);
        RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix * transform2D::Translate(30, -30) * transform2D::Translate(j + 2, m) * transform2D::Scale(0.5, 0.5);
        RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix * transform2D::Translate(70, -70) * transform2D::Translate(j + 2, m) * transform2D::Scale(0.5, 0.5);
        RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix * transform2D::Translate(30, -150) * transform2D::Translate(j + 2, m) * transform2D::Scale(0.5, 0.5);
        RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix * transform2D::Translate(70, -190) * transform2D::Translate(j + 2, m) * transform2D::Scale(0.5, 0.5);
        RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix * transform2D::Translate(110, -210) * transform2D::Translate(j + 2, m) * transform2D::Scale(0.5, 0.5);
        RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix * transform2D::Translate(90, 0) * transform2D::Translate(j + 2, m) * transform2D::Scale(0.5, 0.5);
        RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix * transform2D::Translate(-30, 30) * transform2D::Translate(j + 2, m) * transform2D::Scale(0.5, 0.5);
        RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix * transform2D::Translate(-70, 70) * transform2D::Translate(j + 2, m) * transform2D::Scale(0.5, 0.5);
        RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix * transform2D::Translate(-30, 150) * transform2D::Translate(j + 2, m) * transform2D::Scale(0.5, 0.5);
        RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix * transform2D::Translate(-70, 190) * transform2D::Translate(j + 2, m) * transform2D::Scale(0.5, 0.5);
        RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

    }

    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 5; k++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= visMatrix * transform2D::Translate(40 * (i + 1), 40.9 * (k + 1)) * transform2D::Translate(-lineSide1 * 19 / 7 + lineSide1 / 2, 0) *
                transform2D::Translate(-lineSide1 / 2, -lineSide1 / 2);
            RenderMesh2D(meshes["square8"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= visMatrix * transform2D::Translate(40 * (i + 1), 40 * (k + 1)) * transform2D::Translate(-3 * lineSide1 / 2, 0) *
                transform2D::Translate(-lineSide1 / 2, -lineSide1 / 2);
            RenderMesh2D(meshes["square6"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= visMatrix * transform2D::Translate(40 * (i + 1), 40.9 * (k + 1)) * transform2D::Translate(-lineSide1 / 2, 0) *
                transform2D::Translate(-lineSide1 / 2, -lineSide1 / 2);
            RenderMesh2D(meshes["square5"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= visMatrix * transform2D::Translate(40 * (i + 1), 40 * (k + 1)) * transform2D::Translate(-lineSide1 / 2, -lineSide1 / 2);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= visMatrix * transform2D::Translate(40 * (i + 1), 40.9 * (k + 1)) * transform2D::Translate(-lineSide1 * 6 / 7, 0) *
                transform2D::Translate(-lineSide1 / 2, -lineSide1 / 2);
            RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= visMatrix * transform2D::Translate(40 * (i + 1), 40 * (k + 1)) * transform2D::Translate(-lineSide1 * 12 / 7, 0) *
                transform2D::Translate(-lineSide1 / 2, -lineSide1 / 2);
            RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= visMatrix * transform2D::Translate(40 * (i + 1), 40.9 * (k + 1)) * transform2D::Translate(-lineSide1 * 19 / 7, 0) *
                transform2D::Translate(-lineSide1 / 2, -lineSide1 / 2);
            RenderMesh2D(meshes["square7"], shaders["VertexColor"], modelMatrix);
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 5; k++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= visMatrix * transform2D::Translate(- 40 * (i + 1) + 12, - 40.9 * (k + 1)) * transform2D::Translate(-lineSide1 * 19 / 7 + lineSide1 / 2, 0) *
                transform2D::Translate(-lineSide1 / 2, -lineSide1 / 2);
            RenderMesh2D(meshes["square8"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= visMatrix * transform2D::Translate(- 40 * (i + 1) + 12, - 40 * (k + 1)) * transform2D::Translate(-3 * lineSide1 / 2, 0) *
                transform2D::Translate(-lineSide1 / 2, -lineSide1 / 2);
            RenderMesh2D(meshes["square6"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= visMatrix * transform2D::Translate(- 40 * (i + 1) + 12, - 40.9 * (k + 1)) * transform2D::Translate(-lineSide1 / 2, 0) *
                transform2D::Translate(-lineSide1 / 2, -lineSide1 / 2);
            RenderMesh2D(meshes["square5"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= visMatrix * transform2D::Translate(- 40 * (i + 1) + 12, - 40 * (k + 1)) * transform2D::Translate(-lineSide1 / 2, -lineSide1 / 2);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= visMatrix * transform2D::Translate(- 40 * (i + 1) + 12, - 40.9 * (k + 1)) * transform2D::Translate(-lineSide1 * 6 / 7, 0) *
                transform2D::Translate(-lineSide1 / 2, -lineSide1 / 2);
            RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= visMatrix * transform2D::Translate(- 40 * (i + 1) + 12, - 40 * (k + 1)) * transform2D::Translate(-lineSide1 * 12 / 7, 0) *
                transform2D::Translate(-lineSide1 / 2, -lineSide1 / 2);
            RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= visMatrix * transform2D::Translate(- 40 * (i + 1) + 12, - 40.9 * (k + 1)) * transform2D::Translate(-lineSide1 * 19 / 7, 0) *
                transform2D::Translate(-lineSide1 / 2, -lineSide1 / 2);
            RenderMesh2D(meshes["square7"], shaders["VertexColor"], modelMatrix);
        }
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= visMatrix * transform2D::Translate(-lineSide1 / 4, -lineSide1 / 4);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Translate(lineSide1 / 4, lineSide1 / 4);
    modelMatrix *= transform2D::Translate(logicSpace.width / 2, logicSpace.height / 2);
    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Translate(- logicSpace.width / 2, - logicSpace.height / 2);
    modelMatrix *= transform2D::Translate(- lineSide1 / 4, - lineSide1 / 4);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= visMatrix * transform2D::Translate(-lineSide1 / 2, - lineSide1 / 2);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Translate(logicSpace.width / 2, logicSpace.height / 2);
    modelMatrix *= transform2D::Translate(lineSide1 / 2, lineSide1 / 2);
    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Translate(- lineSide1 / 2, - lineSide1 / 2);
    modelMatrix *= transform2D::Translate( - logicSpace.width / 2, - logicSpace.height / 2);
    RenderMesh2D(meshes["hexagon1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= visMatrix *  transform2D::Translate(- lineSide1 / 2, - lineSide1);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Translate(logicSpace.width / 2, logicSpace.height / 2);
    modelMatrix *= transform2D::Translate(lineSide1 / 2, lineSide1);
    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Translate(- lineSide1 / 2, - lineSide1);
    modelMatrix *= transform2D::Translate(- logicSpace.width / 2, - logicSpace.height / 2);
    RenderMesh2D(meshes["rectangular1"], shaders["VertexColor"], modelMatrix);

    for (int i = 0; i < proiectile.size(); i++) {
        Proiectil* proiectil = &proiectile.at(i);
        proiectil->coordSetter(deltaTimeSeconds * 8 * cos(proiectil->unghi),
            deltaTimeSeconds * 5 * sin(proiectil->unghi));
        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix;
        modelMatrix *= transform2D::Translate(proiectil->translateX, proiectil->translateY);
        modelMatrix *= transform2D::Translate(logicSpace.width / 2, logicSpace.height / 2);
        modelMatrix *= transform2D::Rotate(proiectil->unghi);
        modelMatrix *= transform2D::Translate(-logicSpace.width / 2, -logicSpace.height / 2);
        modelMatrix *= transform2D::Translate(-lineSide3, -lineSide3 / 2);
        proiectile.at(i).matrix = modelMatrix;
        RenderMesh2D(meshes["rectangular6"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= visMatrix * transform2D::Translate(-lineSide2 / 2, -lineSide2);
    RenderMesh2D(meshes["rectangular7"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["rectangular2"], shaders["VertexColor"], modelMatrix);

}

glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}

void Tema1::FrameEnd()
{
}

/* These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`. */

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    if (window->KeyHold(GLFW_KEY_A)) {
        translateX -= 50 * deltaTime;
        logicSpace.x -= 50 * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_D)) {
        translateX += 50 * deltaTime;
        logicSpace.x += 50 * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_W)) {
        translateY += 50 * deltaTime;
        logicSpace.y += 50 * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        translateY -= 50 * deltaTime;
        logicSpace.y -= 50 * deltaTime;
    }

}

void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    glm::ivec2 resolution = window->GetResolution();
    float coordX, coordY;
    coordX = mouseX - resolution.x / 2 ;
    coordY = resolution.y - mouseY - resolution.y / 2 ;
    angle = atan2(coordY, coordX);
   
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
   
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        Proiectil proiectil = Proiectil(angle, translateX, translateY);
        proiectile.push_back(proiectil);
    }

}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}

void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}