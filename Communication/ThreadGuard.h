#pragma once
#include "IThreadGuard.h"

class ThreadGuard : public IThreadGuard
{
public:
    explicit ThreadGuard(std::thread&& input);

    ThreadGuard(ThreadGuard const& t) = delete;
    ThreadGuard(ThreadGuard&&) noexcept = default;

    ThreadGuard& operator=(ThreadGuard const&) = delete;
    ThreadGuard& operator=(ThreadGuard&&) noexcept = default;

    ~ThreadGuard() override;

    void Join() override;

private:
    std::thread _thread;
};
