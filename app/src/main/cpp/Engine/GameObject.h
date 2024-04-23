//
// Created by tts on 4/19/2024.
//

#ifndef VTMAPS_GAMEOBJECT_H
#define VTMAPS_GAMEOBJECT_H

#include <unordered_map>
#include <vector>
#include <string>
#include <type_traits>
#include <typeindex>
#include <memory>

#include "Component/Component.h"
#include "Core.h"

namespace Engine {
    class GameObject {
    private:
        std::unordered_map<std::type_index, std::shared_ptr<Component>> _componentMap;
        std::string _name;
        std::vector<std::shared_ptr<GameObject>> _children;
        std::weak_ptr<GameObject> _parent;

    public:
        GameObject();

        template<typename T, typename... Args>
        void AddComponent(bool override, Args&& ... args) {
            std::type_index typeIndex = std::type_index(typeid(T));
            if (override || (_componentMap.find(typeIndex) == _componentMap.end())) {
                std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);
                _componentMap.insert({typeIndex, std::move(component)});
                return;
            }
            LOG_WARN("Component", "Component %s exist, not override", typeIndex.name());
        }

        template<typename T>
        std::shared_ptr<T> GetComponent() {
            auto it = _componentMap.find(std::type_index(typeid(T)));
            if(it != _componentMap.end()) {
                return std::static_pointer_cast<T>(it->second);
            }
            return nullptr;
        }

        template<typename T>
        std::vector<std::shared_ptr<T>> GetComponents() {
            std::vector<std::shared_ptr<T>> res;
            auto findKey = std::type_index(typeid(T));
            for (auto& [key, component] : _componentMap) {
                if (findKey == key) {
                    res.push_back(static_pointer_cast<T>(component));
                }
            }
            return res;
        }

        template<typename T>
        bool TryGetComponent(std::shared_ptr<T>& component) {
            std::type_index findKey = std::type_index(typeid(T));
            for (auto& [key, component] : _componentMap) {
                if (findKey == key) {
                    component = static_pointer_cast<T>(component);
                    return true;
                }
            }
            return false;
        }

        template<typename T>
        void RemoveComponent() {
            std::type_index key = std::type_index(typeid(T));
            _componentMap.erase(key);
        }
    };
}

#endif //VTMAPS_GAMEOBJECT_H
