#include "lab_m1/Tema3/Tema3.h"
#include <vector>
#include <string>
#include <iostream>
#include <time.h>

using namespace std;
using namespace m1;

Tema3::Tema3()
{
}

Tema3::~Tema3()
{
}

Mesh* Tema3::CreateCircle(const std::string& name, glm::vec3 center, float raza, glm::vec3 color) {

    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    float angle, x, y;
    int i = 0;

    for (angle = 0.0f; angle <= (2.0f * 3.14); angle += 0.01f) {
        x = raza * cos(angle);
        y = raza * sin(angle);
        vertices.push_back(VertexFormat(center + glm::vec3(x, 0, y), color));
        vertices.push_back(VertexFormat(center + glm::vec3(0, 2, 0)));
        indices.push_back(i);
        indices.push_back(i + 1);
        i += 2;
    }

    Mesh* circle = new Mesh(name);
    circle->SetDrawMode(GL_LINE_LOOP);
    circle->InitFromData(vertices, indices);

    return circle;
}

void Tema3::Init()
{
    srand(100000);
    for (int i = 0; i < 64; i++) {
        colorA[i] = (double)rand() / (RAND_MAX);
        colorB[i] = (double)rand() / (RAND_MAX);
        colorC[i] = (double)rand() / (RAND_MAX);
    }

    for (int i = 0; i < 64; i++) {
        colors[i] = glm::vec3(colorA[i], colorB[i], colorC[i]);
    }

    dir1 = rand() % 360 + 1;
    dir2 = rand() % 360 + 1;

    {
        Mesh* circle = Tema3::CreateCircle("cone", glm::vec3(0, 0, 0), 1, glm::vec3(1, 0, 0));
        AddMeshToList(circle);
    }  

    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

   {
        Mesh* mesh = new Mesh("dog");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "animals"), "dog.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("bunny");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "animals"), "bunny.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("whale");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "animals"), "whale.obj");
        meshes[mesh->GetMeshID()] = mesh;
    } 
    
    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        int aux = 0; 
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 4; i++) {
                lightPosition[aux] = glm::vec3(-i, 1, j);
                aux++;
            }
            for (int i = 0; i < 4; i++) {
                lightPosition[aux] = glm::vec3(i + 1, 1, j);
                aux++;
            }
        }
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 4; i++) {
                lightPosition[aux] = glm::vec3(-i, 1, -j - 1);
                aux++;
            }
            for (int i = 0; i < 4; i++) {
                lightPosition[aux] = glm::vec3(i + 1, 1, -j - 1);
                aux++;
            }
        }
        cout << lightPosition[0] << endl;
        lightDirection = glm::vec3(0, -1, 0);
        materialShininess = 30;
        materialKd = 0.5;
        materialKs = 0.5;
        cut_off = glm::radians(30.0f);
        angularStep1 = 0;
        angularStep2 = 0;
        angularStep3 = 0;
        angularStep4 = 0;
        translateX1 = 0;
        translateZ1 = 0;
        translateX2 = 0;
        translateZ2 = 0;
        timer = 0;
        angle = 0;
        angle2 = 0;
        angle3 = 0; 
        lIntensity = 1;
        whale1 = 0;
        whale2 = 0;
        whale3 = 0;
        whale4 = 0; 
        whale5 = 0;
        whale6 = 0;
        position_spotlight[0] = glm::vec3(1, 2, 2);
        position_spotlight[1] = glm::vec3(-2, 2, 2);
        position_spotlight[2] = glm::vec3(-0.5f, 2, -3);
        position_spotlight[3] = glm::vec3(3, 2, -3);
        position_spotlight[4] = glm::vec3(-2, 2, -1);
        position_spotlight[5] = glm::vec3(3, 2, -0.2f);
        color_spotlight[0] = glm::vec3(0, 1, 0.8f);
        color_spotlight[1] = glm::vec3(0.5f, 0.2f, 1);
        color_spotlight[2] = glm::vec3(0.7f, 0, 0.4f);
        color_spotlight[3] = glm::vec3(0.9f, 1, 0);
        color_spotlight[4] = glm::vec3(1, 0.2f, 0);
        color_spotlight[5] = glm::vec3(1, 1, 0.8f);
        param = 0; 
    }
}

void Tema3::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::Update(float deltaTimeSeconds) {

    
        angle3 += deltaTimeSeconds;
       /* {
            glm::mat4 matrix = glm::mat4(1);
            matrix = glm::rotate(matrix, angle3, glm::vec3(0, 0, 1));
            lightDirection = normalize(matrix * glm::vec4(lightDirection, 0));
        }  */

    if ((translateX1 <= 1) && (translateX1 >= -1)) {
        translateX1 += deltaTimeSeconds * 1.1f;
    }
    else if ((translateZ1 <= 2) && (translateZ1 >= -2)) {
        translateZ1 += deltaTimeSeconds * 1.1f;
    }
        
    else if ((translateX2 <= 1) && (translateX2 >= -1)) {
        translateX2 -= deltaTimeSeconds * 1.1f;
    }
    else if ((translateZ2 <= 2) && (translateZ2 >= -2)){
        translateZ2 -= deltaTimeSeconds * 1.1f;
    }
    else {
        translateX1 = 0;
        translateX2 = 0;
        translateZ1 = 0;
        translateZ2 = 0;
    }
    
    if (angle < 3) {
        angle += 1.1 * deltaTimeSeconds;
    }
    else if (angle2 > -3){
        angle2 -= 1.1 * deltaTimeSeconds;
    }
    else {
        angle = 0;
        angle2 = 0;
    }

    if ((whale1 <= 1) && (whale1 >= -1) && (whale2 >= -1) && (whale2 < 1)) {
        whale1 += deltaTimeSeconds * 1.1f;
        whale2 += deltaTimeSeconds * 1.1f;
    }
    else if ((whale3 <= 1) && (whale3 >= -1)) {
        whale3 += deltaTimeSeconds * 1.1f;
    }
    else if ((whale4 <= 1) && (whale4 >= -1) && (whale5 >= -1) && (whale5 < 1)) {
        whale4 += deltaTimeSeconds * 1.1f;
        whale5 += deltaTimeSeconds * 1.1f;
    }
    else if ((whale6 <= 1) && (whale6 >= -1)) {
        whale6 += deltaTimeSeconds * 1.1f;
    }
    else {
        whale1 = 0;
        whale2 = 0;
        whale3 = 0;
        whale4 = 0;
        whale5 = 0;
        whale6 = 0;
    } 


    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.5f, 0, -0.5f));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(-90), glm::vec3(1, 0, 0));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(-90), glm::vec3(0, 0, 1));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.165f, 0, 0.1f));
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, 1, param, glm::vec3(1, 0, 0));
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(4.5f, 0, -0.5f));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(-90), glm::vec3(1, 0, 0));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(-90), glm::vec3(0, 0, 1));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.165f, 0, 0.1f));
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, 1, param, glm::vec3(1, 0, 0));
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f, 0, -4.5f));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(-90), glm::vec3(1, 0, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.165f, 0, 0.1f));
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, 1, param, glm::vec3(1, 0, 0));
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, 0.4f, 1.5f));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-whale1, 0, whale2));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(whale3, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-whale4, 0, -whale5));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(whale6, 0, 0)); 
        modelMatrix = glm::rotate(modelMatrix, RADIANS(-90), glm::vec3(1, 0, 0)); 
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.001f));
        RenderSimpleMesh(meshes["whale"], shaders["LabShader"], modelMatrix, 1, param, glm::vec3(0, 0, 0));
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(translateX1, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, translateZ1));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(translateX2, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, translateZ2));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(-90), glm::vec3(1, 0, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.065f));
        RenderSimpleMesh(meshes["dog"], shaders["LabShader"], modelMatrix, 1, param, glm::vec3(0, 0, 0));
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.7f, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -3));
        modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix, angle2, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.04f));
        RenderSimpleMesh(meshes["bunny"], shaders["LabShader"], modelMatrix, 1, param, glm::vec3(0, 0, 0));
    }
    
    int aux = 0;
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(-i, 0, j));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1f, 1));
                RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, 0, param, glm::vec3(colorA[aux], colorB[aux], colorC[aux]));
                aux++;
            }
        }
        for (int i = 0; i < 4; i++) {
            {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(i + 1, 0, j));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1f, 1));
                RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, 0, param, glm::vec3(colorA[aux], colorB[aux], colorC[aux]));
                aux++;
            }
        }
    }
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(-i, 0, -j - 1));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1f, 1));
                RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, 0, param, glm::vec3(colorA[aux], colorB[aux], colorC[aux]));
                aux++;
            }
        }
        for (int i = 0; i < 4; i++) {
            {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(i + 1, 0, -j - 1));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1f, 1));
                RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, 0, param, glm::vec3(colorA[aux], colorB[aux], colorC[aux]));
                aux++;
            }
        }
    }
    
 /*   for (int k = 0; k < 64; k++) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, lightPosition[k]);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix, 0, glm::vec3(0, 0, 0));
    } */ 

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    cout << angularStep1 << "  " << endl;

    if (param == 0) {
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0, 2));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(tan(cut_off), 1, tan(cut_off) * 2));
            modelMatrix = glm::rotate(modelMatrix, angularStep1, glm::vec3(1, 0, 0));
            modelMatrix = glm::rotate(modelMatrix, -angularStep2, glm::vec3(1, 0, 0));
            modelMatrix = glm::rotate(modelMatrix, -angularStep3, glm::vec3(0, 0, 1));
            modelMatrix = glm::rotate(modelMatrix, angularStep4, glm::vec3(0, 0, 1));
            RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix, 1, param, glm::vec3(0, 0, 0));
        }

        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(1, 0, 2));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(tan(cut_off), 1, tan(cut_off) * 2));
            modelMatrix = glm::rotate(modelMatrix, angularStep1, glm::vec3(1, 0, 0));
            modelMatrix = glm::rotate(modelMatrix, -angularStep2, glm::vec3(1, 0, 0));
            modelMatrix = glm::rotate(modelMatrix, -angularStep3, glm::vec3(0, 0, 1));
            modelMatrix = glm::rotate(modelMatrix, angularStep4, glm::vec3(0, 0, 1));
            RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix, 1, param, glm::vec3(0, 0, 0));
        }

        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f, 0, -3));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(tan(cut_off), 1, tan(cut_off) * 2));
            modelMatrix = glm::rotate(modelMatrix, angularStep1, glm::vec3(1, 0, 0));
            modelMatrix = glm::rotate(modelMatrix, -angularStep2, glm::vec3(1, 0, 0));
            modelMatrix = glm::rotate(modelMatrix, -angularStep3, glm::vec3(0, 0, 1));
            modelMatrix = glm::rotate(modelMatrix, angularStep4, glm::vec3(0, 0, 1));
            RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix, 1, param, glm::vec3(0, 0, 0));
        }

        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(3, 0, -3));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(tan(cut_off), 1, tan(cut_off) * 2));
            modelMatrix = glm::rotate(modelMatrix, angularStep1, glm::vec3(1, 0, 0));
            modelMatrix = glm::rotate(modelMatrix, -angularStep2, glm::vec3(1, 0, 0));
            modelMatrix = glm::rotate(modelMatrix, -angularStep3, glm::vec3(0, 0, 1));
            modelMatrix = glm::rotate(modelMatrix, angularStep4, glm::vec3(0, 0, 1));
            RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix, 1, param, glm::vec3(0, 0, 0));
        }

        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0, -1));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(tan(cut_off), 1, tan(cut_off) * 2));
            modelMatrix = glm::rotate(modelMatrix, angularStep1, glm::vec3(1, 0, 0));
            modelMatrix = glm::rotate(modelMatrix, -angularStep2, glm::vec3(1, 0, 0));
            modelMatrix = glm::rotate(modelMatrix, -angularStep3, glm::vec3(0, 0, 1));
            modelMatrix = glm::rotate(modelMatrix, angularStep4, glm::vec3(0, 0, 1));
            RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix, 1, param, glm::vec3(0, 0, 0));
        }

        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(3, 0, -0.2f));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(tan(cut_off), 1, tan(cut_off) * 2));
            modelMatrix = glm::rotate(modelMatrix, angularStep1, glm::vec3(1, 0, 0));
            modelMatrix = glm::rotate(modelMatrix, -angularStep2, glm::vec3(1, 0, 0));
            modelMatrix = glm::rotate(modelMatrix, -angularStep3, glm::vec3(0, 0, 1));
            modelMatrix = glm::rotate(modelMatrix, angularStep4, glm::vec3(0, 0, 1));
            RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix, 1, param, glm::vec3(0, 0, 0));
        }
    }
      glDepthMask(GL_TRUE);
      glDisable(GL_BLEND);
      glDisable(GL_CULL_FACE);
    
}


void Tema3::FrameEnd()
{
    DrawCoordinateSystem();
}


void Tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, int param, int param2, const glm::vec3& color) {
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    int parameter = glGetUniformLocation(shader->program, "param");
    glUniform1i(parameter, param);

    int parameter2 = glGetUniformLocation(shader->program, "param2");
    glUniform1i(parameter2, param2);

    for (int i = 0; i < 64; i++) {
        // Set shader uniforms for light properties
        int light_position = glGetUniformLocation(shader->program, "light_position");
        glUniform3fv(light_position, 64, glm::value_ptr(lightPosition[0]));
        int color_loc = glGetUniformLocation(shader->program, "color");
        glUniform3fv(color_loc, 64, glm::value_ptr(colors[0]));
    }

    int light_direction = glGetUniformLocation(shader->program, "light_direction");
    glUniform3f(light_direction, lightDirection.x, lightDirection.y, lightDirection.z);

    for (int i = 0; i < 6; i++) {
        int spotlightPos = glGetUniformLocation(shader->program, "spotLightPosition");
        glUniform3fv(spotlightPos, 6, glm::value_ptr(position_spotlight[0]));
        int spotlightColor = glGetUniformLocation(shader->program, "spotLightColor");
        glUniform3fv(spotlightColor, 6, glm::value_ptr(color_spotlight[0]));
    }

    // Set eye position (camera position) uniform
    glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();
    int eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

    // Set material property uniforms (shininess, kd, ks, object color) 
    int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(material_shininess, materialShininess);

    int material_kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(material_kd, materialKd);

    int material_ks = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(material_ks, materialKs);

    int object_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3f(object_color, color.r, color.g, color.b);

    int cut_off_loc = glGetUniformLocation(shader->program, "CutOff");
    glUniform1f(cut_off_loc, cut_off);

    int intensitate = glGetUniformLocation(shader->program, "intensity");
    glUniform1f(intensitate, lIntensity);

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


void Tema3::OnInputUpdate(float deltaTime, int mods)
{
    float speed = 2;

    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 right = GetSceneCamera()->m_transform->GetLocalOXVector();
        glm::vec3 forward = GetSceneCamera()->m_transform->GetLocalOZVector();
        forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));

        // Control light position using on W, A, S, D, E, Q
        if (window->KeyHold(GLFW_KEY_W)) {
            for (int i = 0; i < 64; i++) {
                lightPosition[i] -= forward * deltaTime * speed;
            }
        }
        if (window->KeyHold(GLFW_KEY_A)) {
            for (int i = 0; i < 64; i++) {
                lightPosition[i] -= right * deltaTime * speed;
            }
        }
        if (window->KeyHold(GLFW_KEY_S)) {
            for (int i = 0; i < 64; i++) {
                lightPosition[i] += forward * deltaTime * speed;
            }
        }
        if (window->KeyHold(GLFW_KEY_D)) {
            for (int i = 0; i < 64; i++) {
                lightPosition[i] += right * deltaTime * speed;
            }
        }
        if (window->KeyHold(GLFW_KEY_E)) {
            for (int i = 0; i < 64; i++) {
                lightPosition[i] += up * deltaTime * speed;
            }
        }
        if (window->KeyHold(GLFW_KEY_Q)) {
            for (int i = 0; i < 64; i++) {
                lightPosition[i] -= up * deltaTime * speed;
            }
        }

    }

    if (window->KeyHold(GLFW_KEY_UP)) {
        if (glm::radians(180.0f) > cut_off) {
            cut_off += deltaTime * 3;
        }
    }
    if (window->KeyHold(GLFW_KEY_DOWN)) {
        if (glm::radians(0.0f) < cut_off) {
            cut_off -= deltaTime * 3;
        }
    }

    if (window->KeyHold(GLFW_KEY_H)) {
        // rotatie spotlight-uri 
        angularStep1 += deltaTime * 0.005f;
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= glm::rotate(modelMatrix, angularStep1, glm::vec3(1, 0, 0));
        lightDirection = glm::normalize(glm::vec3(modelMatrix * glm::vec4(lightDirection, 0.0)));
    }
    if (window->KeyHold(GLFW_KEY_J)) {
        // rotatie spotlight-uri 
        angularStep2 += deltaTime * 0.005f;
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= glm::rotate(modelMatrix, -angularStep2, glm::vec3(1, 0, 0));
        lightDirection = glm::normalize(glm::vec3(modelMatrix * glm::vec4(lightDirection, 0.0)));
    }
    if (window->KeyHold(GLFW_KEY_K)) {
        // rotatie spotlight-uri 
        angularStep3 += deltaTime * 0.005f;
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= glm::rotate(modelMatrix, -angularStep3, glm::vec3(0, 0, 1));
        lightDirection = glm::normalize(glm::vec3(modelMatrix * glm::vec4(lightDirection, 0.0)));
    }
    if (window->KeyHold(GLFW_KEY_L)) {
        // rotatie spotlight-uri 
        angularStep4 += deltaTime * 0.005f;
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= glm::rotate(modelMatrix, angularStep4, glm::vec3(0, 0, 1));
        lightDirection = glm::normalize(glm::vec3(modelMatrix * glm::vec4(lightDirection, 0.0)));
    }
}


void Tema3::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_O) {
        param = 1;
    }
    if (key == GLFW_KEY_P) {
        param = 0; 
    }

}


void Tema3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema3::OnWindowResize(int width, int height)
{
}
