// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "ui/text.h"
#include "graphics/vertexbuffer.h"
#include "ui/font.h"
#include "ui/fontface.h"
#include "core/enginecontext.h"
#include "graphics/rendersystem.h"

namespace CodeHero {

Text::Text(std::shared_ptr<EngineContext>& iContext)
    : UIElement(iContext) {}

void Text::SetFont(const std::string& iFontName) {
    (void)iFontName;
}

void Text::SetFont(std::shared_ptr<Font> iFont) {
    m_pFont = iFont;
}

void Text::SetSize(uint32_t iSize) {
    m_Size = iSize;
}

void Text::SetText(const std::string& iText) {
    m_Text = iText;
}

void Text::SetColor(const Color& iColor) {
    m_Color = iColor;
}

void Text::GetBatches(std::vector<UIBatch>& oBatches) {
    if (!m_Text.empty() && m_pFont.get() && m_Size != 0) {
        std::shared_ptr<FontFace> fa = m_pFont->GetFace(m_Size);
        std::string::size_type size = m_Text.size();
        std::shared_ptr<VertexBuffer> buffer(m_pContext->GetSubsystem<RenderSystem>()->CreateVertexBuffer());
        buffer->SetData(nullptr, 6 * size, VertexBuffer::MASK_Position | VertexBuffer::MASK_Color | VertexBuffer::MASK_TexCoord, true);
        float x = m_Position.x();
        float r = m_Color.r();
        float g = m_Color.g();
        float b = m_Color.b();
        float a = m_Color.a();
        for (std::string::size_type i = 0; i < size; ++i) {
            FontFaceGlyph& ch = fa->GetGlyph(m_Text[i]);

            float xpos = x + ch.left;
            float ypos = m_Position.y() - (ch.height - ch.top);

            float w = ch.width;
            float h = ch.height;
            // Update VBO for each character
            float vertices[6][9] = {
                { xpos,     ypos + h, 0.0, r, g, b, a, 0.0, 0.0 },
                { xpos + w, ypos,     0.0, r, g, b, a, 1.0, 1.0 },
                { xpos,     ypos,     0.0, r, g, b, a, 0.0, 1.0 },

                { xpos,     ypos + h, 0.0, r, g, b, a, 0.0, 0.0 },
                { xpos + w, ypos + h, 0.0, r, g, b, a, 1.0, 0.0 },
                { xpos + w, ypos,     0.0, r, g, b, a, 1.0, 1.0 }
            };

            buffer->SetSubData(vertices, i * 6, 6);
            buffer->Unuse();
            // Batch
            UIBatch batch;
            batch.SetVertexBuffer(buffer, i * 6, 6);
            batch.SetTexture(ch.texture);
            oBatches.push_back(batch);

            x += (ch.advanceX >> 6); // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }
    }
}

} // namespace CodeHero

