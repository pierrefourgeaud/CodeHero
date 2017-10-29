// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_UI_UIDRAW_H_
#define CODEHERO_UI_UIDRAW_H_

#include <memory>
#include <vector>

namespace CodeHero {

// Forward declaration
class UIBatch;
class Vector2;
class EngineContext;
class Color;
class FontFace;

class UIDraw {
public:
    // Get batches from path
    static void PathStroke(const std::shared_ptr<EngineContext>& iContext,
                           std::vector<UIBatch>& oBatches,
                           const std::vector<Vector2>& iPoints,
                           const Color& iColor);
    static void PathFill(const std::shared_ptr<EngineContext>& iContext,
                         std::vector<UIBatch>& oBatches,
                         const std::vector<Vector2>& iPoints,
                         const Color& iColor);

    static void Text(const std::shared_ptr<EngineContext>& iContext,
                     std::vector<UIBatch>& oBatches,
                     const std::string& iText,
                     const std::shared_ptr<FontFace>& iFontFace,
                     const Vector2& iPosition,
                     const Color& iColor);

private:
    UIDraw() = delete;
    ~UIDraw() = delete;
    UIDraw(const UIDraw&) = delete;
    UIDraw(const UIDraw&&) = delete;
    UIDraw& operator=(const UIDraw&) = delete;
};

} // namespace CodeHero

#endif // CODEHERO_UI_UIDRAW_H_
