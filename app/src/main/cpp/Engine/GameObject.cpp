//
// Created by tts on 4/19/2024.
//

#include "GameObject.h"

namespace Engine {
    const std::string &GameObject::GetName() const {
        return _name;
    }

    void GameObject::SetName(const std::string &name) {
        _name = name;
    }

    const std::weak_ptr<GameObject> &GameObject::GetParent() const {
        return _parent;
    }

    void GameObject::SetParent(const std::weak_ptr<GameObject>& parent) {
        _parent = parent;
    }
}

