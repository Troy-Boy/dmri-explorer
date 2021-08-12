#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include <binding.h>
#include <data.h>
#include <image.h>
#include <sphere.h>
#include <shader.h>
#include <mutex>
#include <model.h>

namespace Slicer
{
struct DrawElementsIndirectCommand
{
    DrawElementsIndirectCommand()
        :count(0)
        ,instanceCount(0)
        ,firstIndex(0)
        ,baseVertex(0)
        ,baseInstance(0)
    {
    };

    DrawElementsIndirectCommand(uint count,
                                uint instanceCount,
                                uint firstIndex,
                                uint baseVertex,
                                uint baseInstance)
        :count(count)
        ,instanceCount(instanceCount)
        ,firstIndex(firstIndex)
        ,baseVertex(baseVertex)
        ,baseInstance(baseInstance)
    {
    };

    /// Number of elements to be rendered
    uint count;
    /// Number of instances of the indexed geometry to draw
    uint instanceCount;
    /// Offset to the beginning of elements
    uint firstIndex;
    /// Constant that should be added to each element of indices
    uint baseVertex;
    /// Base instance for use in fetching instanced vertex attributes
    uint baseInstance;
};

class SHField : public Model
{
public:
    SHField(const std::shared_ptr<ApplicationState>& state,
            std::shared_ptr<CoordinateSystem> parent);
    ~SHField();

    // options callbacks
    void SetSliceIndex();
    void SetNormalized();
    void SetSH0Threshold();
    void SetSphereScaling();

    // Compute shader pass for scaling spheres
    void ScaleSpheres();

protected:
    void drawSpecific() override;
    void initOptions() override;
    void initOptionsCallbacks() override;
    void initProgramPipeline() override;

private:
    void initializeMembers();
    void initializeGPUData();
    void initializePerVoxelAttributes();
    void initializePerSphereAttributes();
    template<typename T> GLuint genVBO(const std::vector<T>& data) const;
    bool isAnySliceDirty() const;

    // multithreading
    std::mutex mMutex;

    // Sphere topology
    Primitive::Sphere mSphere;

    // Slicing
    GPU::GridInfo mGridInfo;
    uint mNbSpheres;

    // Rendered primitives
    std::vector<GLuint> mIndices;

    // GPU bindings
    GLuint mVAO = 0;
    GLuint mIndicesBO = 0;
    GLuint mIndirectBO = 0;

    ShaderProgram mComputeShader;

    // Shader uniforms
    std::vector<float> mSphHarmCoeffs;
    std::vector<float> mSphHarmFuncs;
    GPU::SphereInfo mSphereInfo;

    GPU::ShaderData mSphHarmCoeffsData;
    GPU::ShaderData mSphHarmFuncsData;
    GPU::ShaderData mGridInfoData;

    // Data on topology of ONE sphere
    GPU::ShaderData mSphereVerticesData;
    GPU::ShaderData mSphereIndicesData;
    GPU::ShaderData mSphereInfoData;

    // Empty arrays to fill in compute shader pass
    GPU::ShaderData mAllRadiisData;
    GPU::ShaderData mAllSpheresNormalsData;

    std::vector<DrawElementsIndirectCommand> mIndirectCmd;
};
} // namespace Slicer
