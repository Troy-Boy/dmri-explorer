#pragma once

#include <glm/glm.hpp>
#include <data.h>
#include <memory>
#include <spherical_coordinates.h>
#include <coordinate_system.h>

class Camera
{
public:
    Camera() = default;
    Camera(const glm::vec3& position,
           const glm::vec3& upVector,
           const glm::vec3& lookat,
           const float& fov, const float& aspect,
           const float& near, const float& far);
    void Resize(const float& aspect);
    void TranslateZ(double delta);
    void TranslateXY(double dx, double dy);
    void Update();
private:

    glm::vec3 mPosition;
    glm::vec3 mLookAt;
    glm::vec3 mUpVector;
    float mFov;
    float mNear;
    float mFar;
    float mAspect;
    glm::mat4 mProjectionMatrix;
    glm::mat4 mViewMatrix;

    GPUData::CamParams mCamParams;
    GPUData::ShaderData mCamParamsData;
};
