#pragma once
#include <camera.h>
#include <model.h>
#include <vector>
#include <coordinate_system.h>
#include <options.h>

namespace Slicer
{
class Scene
{
public:
    Scene(unsigned int width, unsigned int height,
          const std::shared_ptr<ApplicationState>& state);
    ~Scene();
    void Render();
    Camera* GetCameraPtr() { return &mCamera; };
    void RotateCS(const glm::vec2& v);
private:
    std::shared_ptr<CoordinateSystem> mCoordinateSystem;
    std::shared_ptr<ApplicationState> mState;

    // scene contains camera and models
    Camera mCamera;
    std::vector<Model*> mModels;
};
} // namespace Slicer
