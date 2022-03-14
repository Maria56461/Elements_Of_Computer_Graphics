#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "core/engine.h"
#include "components/simple_scene.h"

using namespace std;
#if defined(WITH_LAB_M1)
#   include "lab_m1/lab_list.h"

#endif

#if defined(WITH_LAB_M2)
#   include "lab_m2/lab_list.h"
#endif

#if defined(WITH_LAB_EXTRA)
#   include "lab_extra/lab_list.h"
#endif

#ifdef _WIN32
    PREFER_DISCRETE_GPU_NVIDIA;
    PREFER_DISCRETE_GPU_AMD;
#endif

std::string GetParentDir(const std::string &filePath) {
    size_t pos = filePath.find_last_of("\\/");
    return (std::string::npos == pos) ? "." : filePath.substr(0, pos);
}

int main(int argc, char **argv) {

    srand((unsigned int)time(NULL));
    WindowProperties wp;
    wp.resolution = glm::ivec2(1280, 720);
    wp.vSync = true;
    wp.selfDir = GetParentDir(std::string(argv[0]));

    (void)Engine::Init(wp);

    World *world = new m1::Tema3();

    world->Init();
    world->Run();

    Engine::Exit();

    return 0;
}
