#pragma once
#include <memory>

class Camera;
class Cube;
class Chicken;
class Ground;
struct PointLight;

class ChickenAnim;

namespace Scene
{
    extern std::unique_ptr<Camera> camera;
    extern std::unique_ptr<Cube> cube;
    extern std::unique_ptr<Chicken> chicken;
    extern std::unique_ptr<PointLight> pLight;
    extern std::unique_ptr<Ground> ground;
    
    extern std::unique_ptr<ChickenAnim> chicken_anim;

    void Setup();
    void Dealloc();

    void Update(bool rotX, bool rotY, bool rotZ);
    void Draw();
}