#include "IObject.h"

size_t kod::IObject::sm_uid = 0;

kod::IObject::IObject() : m_uid(sm_uid++) {}

const size_t kod::IObject::getUid() const { return m_uid; }
