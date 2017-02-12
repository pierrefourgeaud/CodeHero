// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_GPUOBJECT_H
#define CODEHERO_CORE_GPUOBJECT_H

namespace CodeHero {

class GPUObject {
    union Object {
        unsigned int intHandle;
        void* ptrHandle;
    };

public:
    Object GetGPUObject() const { return m_Object; }

protected:
    void _SetGPUObject(unsigned int iObject) { m_Object = {iObject}; }
    Object* _GetGPUObjectHandle() { return &m_Object; }

private:
    Object m_Object = {0};
};

} // namespace CodeHero

#endif // CODEHERO_CORE_GPUOBJECT_H
