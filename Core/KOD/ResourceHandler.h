#pragma once
#include "KOD_export.h"
#include "Settings.h"

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
namespace KOD {
template <typename T>
class ResourceHandler
{
	std::unordered_map<std::string, std::shared_ptr<T>> m_resourceList;

public:
	ResourceHandler() = default;
	~ResourceHandler() = default;
	void addResource(std::string name, std::shared_ptr<T> resource);
	std::shared_ptr<T> getResourceByName(std::string name);
	void clean();
};

template <typename T>
inline void ResourceHandler<T>::addResource(std::string name, std::shared_ptr<T> resource)
{
	if (m_resourceList.find(name) != m_resourceList.end()) {
		return;
	}

	m_resourceList.insert(std::make_pair(name, resource));
}

template <typename T>
inline std::shared_ptr<T> ResourceHandler<T>::getResourceByName(std::string name)
{
	auto findResoult = m_resourceList.find(name);
	if (findResoult == m_resourceList.end()) {
		return std::shared_ptr<T>();
	} else {
		return findResoult->second;
	}
}
template <typename T>
inline void ResourceHandler<T>::clean()
{
	m_resourceList.clear();
}
} // namespace KOD
