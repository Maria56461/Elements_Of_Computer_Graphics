#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Inamic 
    {
    public:
        glm::mat3 matrix;
        // float unghi;
         float translateX, translateY, angle, translatex1, translatey1;

        Inamic(float x, float y) {
            translateX = x;
            translateY = y;
            angle = atan2(-translateX, -translateY);
        }

        ~Inamic() {
        };
    };

    class Proiectil 
    {
    public:
        glm::mat3 matrix;
        float unghi;
        float translateX, translateY;

        Proiectil(float unghi, float x, float y) {
            this->unghi = unghi;
            this->matrix = glm::mat3(1); 
            this->translateX = x;
            this->translateY = y;
        }

        void coordSetter(float x, float y) {
            this->translateX += x;
            this->translateY += y;
        }

        ~Proiectil() {
        };

    };

    class Tema1 : public gfxc::SimpleScene
    {
    public:
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear);
        void DrawScene(glm::mat3 visMatrix);
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        glm::vec3 corner, corner1;
        float cx, cy;
        glm::mat3 modelMatrix, visMatrix;
        std::vector<glm::mat3> matrixArray;
        std::vector<Proiectil> proiectile;
        std::vector<Inamic*> inamici;
        float translateX, translateY, translateX1, translateY1, translateXi, translateYi;
        float scaleX, scaleY;
        float angle, angle1, angle2;
        int i;
        ViewportSpace viewSpace;
        LogicSpace logicSpace, logicSpace1;

        float timer;
    };
}   
