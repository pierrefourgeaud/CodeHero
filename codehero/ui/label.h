// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_UI_LABEL_H_
#define CODEHERO_UI_LABEL_H_ 

#include <memory>
#include <string>
#include "core/color.h"
#include "ui/uielement.h"

namespace CodeHero {

// Forward declaration
class EngineContext;
class Font;
class UIBatch;

class Label : public UIElement {
public:
    explicit Label(std::shared_ptr<EngineContext>& iContext);

    void SetText(const std::string& iText);

    void GetBatches(std::vector<UIBatch>& oBatches) override;

private:
    std::string m_Text;
};

} // namespace CodeHero

#endif // CODEHERO_UI_LABEL_H_
