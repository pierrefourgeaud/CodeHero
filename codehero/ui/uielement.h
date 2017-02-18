// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_UI_UIELEMENT_H_
#define CODEHERO_UI_UIELEMENT_H_ 

#include <vector>
#include "ui/uibatch.h"

namespace CodeHero {

class UIElement {
public:
    virtual ~UIElement() {}
    void AddChild();

    virtual void GetBatches(std::vector<UIBatch>& oBatches) {
        (void)oBatches;
    }

    std::vector<UIElement*>& GetChildren() { return m_Elements; }

private:
    std::vector<UIElement*> m_Elements;
};

} // namespace CodeHero

#endif // CODEHERO_UI_UIELEMENT_H_
