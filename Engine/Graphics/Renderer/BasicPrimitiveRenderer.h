#pragma once

#include "BaseRenderer.h"

namespace Engine
{
    class BasicPrimitiveRenderer final : public BaseRenderer
    {
    public:
        BasicPrimitiveRenderer();
        BasicPrimitiveRenderer(const std::shared_ptr<DrawingDevice>& pDevice, const std::shared_ptr<DrawingContext>& pContext);
        virtual ~BasicPrimitiveRenderer() {}

        void Initialize() override;
        void Shutdown() override;

        void Tick() override;

        void DefineResources(DrawingResourceTable& resTable) override;
        void SetupStages() override;
        void SetupBuffers(DrawingResourceTable& resTable) override;
        void Cleanup() override;

        void BeginFrame() override;
        void EndFrame() override;

        void UpdatePrimitive(DrawingResourceTable& resTable) override;
        void Draw(DrawingResourceTable& resTable) override;

    public:
        // Define shader resource names
        FuncResourceName(BasicPrimitiveVertexShader);
        FuncResourceName(BasicPrimitivePixelShader);
        // Define effect resource names
        FuncResourceName(BasicPrimitiveEffect);
        // Define stage resource names
        FuncResourceName(BasicPrimitiveStage);
        // Define effect resource names
        FuncResourceName(BasicPrimitiveDefaultPass);
        // Define index buffer resource names
        FuncResourceName(BasicPrimitiveIndexBuffer);

    protected:
        void DefineShaderResource(DrawingResourceTable& resTable);

    private:
        std::shared_ptr<DrawingPass> CreateDefaultPass(
            std::shared_ptr<std::string> pPassName,
            std::shared_ptr<std::string> pEffectName,
            std::shared_ptr<std::string> pIndexName);
    };
}