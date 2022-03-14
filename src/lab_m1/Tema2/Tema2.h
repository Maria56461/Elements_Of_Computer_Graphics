#pragma once
#include "components/simple_scene.h"
#include "lab_m1/Tema2/camera.h"

namespace m1 {
    class Proiectil2
    {
    public:
        float translateZ;
        glm::vec3 dir;
        glm::vec3 pos; 

        Proiectil2(float translateZ) {
            this->translateZ = translateZ;
        }

        ~Proiectil2() {
        };

    };
    
    class Tema2 : public gfxc::SimpleScene {
    public:
        Tema2();
        ~Tema2();
        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);


    protected:
        implemented::camera* camera;
        glm::mat4 projectionMatrix;
        std::vector<Proiectil2*> proiectile;
        int maze[24][24];
        float translateX, translateY, translateZ, translateZsph, angle, angle1;
        int var; 
        float mode;
        float x, z;
        int i, a; 
        float param1, param2; 
        glm::vec3 initialPositions[576];
    };
}