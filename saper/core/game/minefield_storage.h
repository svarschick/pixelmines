#pragma once

#include "field.h"
#include "minefield_interactor.h"

#include <array>
#include <vector>
#include <memory>
#include <cstdint>
#include <functional>

namespace core
{

using Pos = std::int16_t;

class MinefieldStorage
{
public:
    using Storage = std::vector<Field>;
    static const Pos NeighbourCount = 8;

    MinefieldStorage(MinefieldInteractorSPtr minefieldInteractor);

    void Reset();
    bool IsValid(Pos x, Pos y) const;
    std::size_t Size() const;
    std::size_t Index(Pos x, Pos y) const;
    Field& At(Pos x, Pos y);
    Field& At(std::size_t index);

    template<typename Func>
    void ForEachNeighbour(std::size_t index, Func&& fn)
    {
        std::array<Pos, NeighbourCount> dx {-1, 0, 1, -1, 1, -1, 0, 1};
        std::array<Pos, NeighbourCount> dy {-1, -1, -1, 0, 0, 1, 1, 1};

        auto x = index % m_minefieldInteractorSPtr->Width();
        auto y = index / m_minefieldInteractorSPtr->Width();

        for (int i = 0; i < NeighbourCount; ++i)
        {
            auto onX = x + dx[i];
            auto onY = y + dy[i];

            if (!IsValid(onX, onY))
            {
                continue;
            }

            std::invoke(std::forward<Func>(fn), Index(onX, onY), At(onX, onY));
        }
    }

private:
    MinefieldInteractorSPtr m_minefieldInteractorSPtr;
    Storage m_storage;
};

using MinefieldStorageSPtr = std::shared_ptr<MinefieldStorage>;

} // namespace core
