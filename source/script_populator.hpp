#pragma once
#include <memory>
#include <thread>
#include <mutex>
#include "script_provider.hpp"

void populateLoop(void* _);
void startPopulatorThread();
void pushProvider(std::shared_ptr<ScriptProvider> provider);
std::shared_ptr<ScriptProvider> pullProvider();
bool queueEmpty();
