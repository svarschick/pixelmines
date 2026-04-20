#pragma once

namespace app::managers
{

class IUpdateInteractor
{
public:
    virtual void ~IUpdateInteractor() = default;
    virtual void OnUpdateInteractor() = 0;
};

} // namespace app::managers
