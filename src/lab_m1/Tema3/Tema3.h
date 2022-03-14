#pragma once

#include "components/simple_scene.h"
#include "components/transform.h"


namespace m1
{
    class Tema3 : public gfxc::SimpleScene
    {
    public:
        Tema3();
        ~Tema3();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, int parameter, int parameter2, const glm::vec3& color = glm::vec3(1));

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        Mesh* CreateCircle(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);

        glm::vec3 lightPosition[64];
        glm::vec3 position_spotlight[6];
        glm::vec3 color_spotlight[6];
        glm::vec3 lightDirection;
        unsigned int materialShininess;
        float lIntensity; 
        float cut_off;
        float materialKd;
        float materialKs;
        float angularStep1, angularStep2, angularStep3, angularStep4;
        double colorA[64];
        double colorB[64];
        double colorC[64];
        glm::vec3 colors[64];
        float translateX1, translateZ1, translateX2, translateZ2, angle, angle2, angle3;
        float whale1, whale2, whale3, whale4, whale5, whale6; 
        int dir1, dir2;
        float timer;
        int param;
    };
}   
