#pragma once
#include "export.h"

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

namespace kod {

template <typename T>
class ResourceHandler
{
	std::unordered_map<std::string_view, T> m_resourceList;

public:
	ResourceHandler() = default;
	~ResourceHandler() = default;
	void add(std::string_view name, T resource);
	T* get(std::string_view name);
	void clean();
};

template <typename T>
inline void ResourceHandler<T>::add(std::string_view name, T resource)
{
	if (m_resourceList.find(name) != m_resourceList.end()) {
		return;
	}

	m_resourceList[name] = std::move(resource);
}

template <typename T>
inline T* ResourceHandler<T>::get(std::string_view name)
{
	auto findResoult = m_resourceList.find(name);
	if (findResoult == m_resourceList.end()) {
		return nullptr;
	}
	return &findResoult->second;
}

template <typename T>
inline void ResourceHandler<T>::clean()
{
	m_resourceList.clear();
}

} // namespace kod
