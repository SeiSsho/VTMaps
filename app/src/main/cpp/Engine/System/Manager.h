//
// Created by tts on 4/19/2024.
//

#ifndef VTMAPS_MANAGER_H
#define VTMAPS_MANAGER_H

#include <string>
#include <unordered_map>
#include <typeinfo>

#include "../../Utilities/Logger.h"

namespace Engine::System {
    template<typename T>
    class Manager {
    private:
        std::unordered_map<std::string, std::shared_ptr<T>> _objects;

    public:
        void Add(const std::string& object_name, const std::shared_ptr<T>& object) {
            if (_objects.find(object_name) != _objects.end()) {
                std::string class_name = typeid(T).name();
                class_name += " MANAGER";
                LOG_WARN(class_name.c_str(), "Add: Object name %s existed", object_name.c_str());
                return;
            }
            _objects.insert({object_name, object});
        }

        std::shared_ptr<T> Get(const std::string& object_name) {
            auto it = _objects.find(object_name);
            if (it == _objects.end()) {
                std::string class_name = typeid(T).name();
                class_name += " MANAGER";
                LOG_WARN(class_name.c_str(), "Add: Object name %s not existed", object_name.c_str());
                return nullptr;
            }
            return _objects.at(it);
        }

        std::shared_ptr<T> Remove(const std::string& object_name) {
            auto it = _objects.find(object_name);
            if (it == _objects.end()) {
                std::string class_name = typeid(T).name();
                class_name += " MANAGER";
                LOG_WARN(class_name.c_str(), "Add: Object name %s existed", object_name.c_str());
                return nullptr;
            }
            auto object = _objects.at(object_name);
            _objects.erase(object_name);
            return object;
        }
    };
}

#endif //VTMAPS_MANAGER_H
