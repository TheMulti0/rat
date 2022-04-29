#pragma once

#include <thread>

class __declspec(dllexport) ThreadGuard
{
public:
    explicit ThreadGuard(std::thread&& input);

    ThreadGuard(ThreadGuard const& t) = delete;

    ThreadGuard(ThreadGuard&&) noexcept = default;

    ThreadGuard& operator=(ThreadGuard const&) = delete;

    ThreadGuard& operator=(ThreadGuard&&) noexcept = default;

    void Join();

    ~ThreadGuard();

private:
    std::thread _thread;
};