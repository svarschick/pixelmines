#pragma once

namespace app::managers
{

class IUpdateInteractor
{
public:
    virtual ~IUpdateInteractor() = default;
    virtual void OnUpdateInteractor() = 0;
};

} // namespace app::managers
