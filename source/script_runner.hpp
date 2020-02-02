#pragma once
#include <switch.h>
#include <memory>

template<class T, class... Args> void runScript(Args&&... args) {
    auto provider = std::make_shared<T>(std::forward<Args>(args)...);
    if(!provider->isGood()) return;
}
