#include "IObject.h"

size_t KOD::IObject::m_st_uid = 0;

KOD::IObject::IObject() : m_uid(m_st_uid++) {}

const size_t KOD::IObject::getUid() const { return m_uid; }
