#pragma once
#include "KOD_export.h"
#include "Settings.h"
#include <map>
#include <memory>
#include <string>
#include <iostream>
namespace KOD
{
  template <typename T>
  class KOD_API ResourceHandler
  {
    std::map<std::string, std::shared_ptr<T>> m_resourceList;
  public:
    ResourceHandler() = default;
    ~ResourceHandler() = default;
    void addResource(std::string name, std::shared_ptr<T> resource);
    std::shared_ptr<T> getResourceByName(std::string name);
  };

  template<typename T>
  inline void ResourceHandler<T>::addResource(std::string name, std::shared_ptr<T> resource)
  {
    if (m_resourceList.find(name) != m_resourceList.end())
    {
      //sendDebugInformation("resource named:" + name + " exist on the list!");
      return;
    }

    m_resourceList.insert(std::make_pair(name, resource));
  }

  template<typename T>
  inline std::shared_ptr<T> ResourceHandler<T>::getResourceByName(std::string name)
  {
    auto findResoult = resourceList.find(name);
    if (findResoult == resourceList.end())
    {
      //sendDebugInformation("resource named:" + name + " don't exist on the list!")
        return std::shared_ptr<T>();
    }
    else
    {
      return findResoult->second;
    }
  }
}
