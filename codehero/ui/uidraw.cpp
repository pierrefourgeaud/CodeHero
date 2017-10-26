
#include "ui/uidraw.h"
#include <algorithm>
#include "core/enginecontext.h"
#include "core/math/vector2.h"
#include "graphics/indexbuffer.h"
#include "graphics/rendersystem.h"
#include "graphics/vertexbuffer.h"
#include "ui/uibatch.h"

namespace CodeHero {

void UIDraw::Path(const std::shared_ptr<EngineContext>& iContext,
                  std::vector<UIBatch>& oBatches,
                  const std::vector<Vector2>& iPoints) {
    // Get normals
    size_t numPoints = iPoints.size();
    std::vector<Vector2> normals(numPoints);
    for (size_t i = 0; i < numPoints; ++i) {
        size_t i2 = (i + 1 == numPoints) ? 0 : (i + 1);
        normals[i] = (iPoints[i2] - iPoints[i]).Normalize();
        normals[i] = Vector2(normals[i].y(), -normals[i].x());
    }

    std::vector<uint32_t> indices(numPoints * 12);
    std::vector<Vector2> tempVtx(numPoints * 2);
    size_t j = 0;
    size_t ids = 0;
    for (size_t i = 0; i < numPoints; ++i) {
        size_t i2 = (i + 1 == numPoints) ? 0 : (i + 1);
        size_t j2 = (i + 1 == numPoints) ? 0 : (j + 3);

        auto dm = (normals[i] + normals[i2]) * 0.5f;
        auto dmr2 = dm.x() * dm.x() + dm.y() * dm.y();
        if (dmr2 > 0.000001f) {
            float scale = 1.0f / dmr2;
            scale = (std::min)(100.0f, scale);
            dm = dm * scale;
        }
        tempVtx[i2 * 2 + 0] = iPoints[i2] + dm;
        tempVtx[i2 * 2 + 1] = iPoints[i2] - dm;

        indices[ids + 0] = (j2 + 0); indices[ids + 1] = (j + 0);
        indices[ids + 2] = (j + 2);  indices[ids + 3] = (j + 2);
        indices[ids + 4] = (j2 + 2); indices[ids + 5] = (j2 + 0);
        indices[ids + 6] = (j2 + 1); indices[ids + 7] = (j + 1);
        indices[ids + 8] = (j + 0);  indices[ids + 9] = (j + 0);
        indices[ids + 10] = (j2 + 0); indices[ids + 11] = (j2 + 1);
        ids += 12;
        j = j2;
    }

    const size_t numVertex = numPoints * 3;
    std::shared_ptr<VertexBuffer> buffer(iContext->GetSubsystem<RenderSystem>()->CreateVertexBuffer());
    buffer->SetData(nullptr, numVertex, VertexBuffer::MASK_Position | VertexBuffer::MASK_TexCoord, true);

    for (size_t i = 0; i < numPoints; ++i) {
        float vertices[3][5] = {
            { iPoints[i].x(), iPoints[i].y(),                 0.0f, 0.5f, 0.5f },
            { tempVtx[i * 2 + 0].x(), tempVtx[i * 2 + 0].y(), 0.0f, 0.5f, 0.5f },
            { tempVtx[i * 2 + 1].x(), tempVtx[i * 2 + 1].y(), 0.0f, 0.5f, 0.5f },
        };
        buffer->SetSubData(vertices, i * 3, 3);
    }
    buffer->Unuse();

    std::shared_ptr<IndexBuffer> indexBuffer(iContext->GetSubsystem<RenderSystem>()->CreateIndexBuffer());
    indexBuffer->SetData(&indices[0], indices.size());

    UIBatch batch;
    batch.SetVertexBuffer(buffer, 0, numVertex);
    batch.SetIndexBuffer(indexBuffer);
    oBatches.push_back(batch);
}

} // namespace CodeHero