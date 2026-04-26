#include "minefield.h"

#include <algorithm>
#include <random>
#include <queue>
#include <utility>

namespace core
{

Minefield::Minefield(MinefieldInteractorSPtr minefieldInteractor,
                     MinefieldStorageSPtr minefieldStorageSPtr) :
    m_minefieldInteractorSPtr{ std::move(minefieldInteractor) },
    m_minefieldStorageSPtr{ std::move(minefieldStorageSPtr) } {}

void Minefield::Reset()
{
    m_state = GameState::FirstMove;
    m_minefieldStorageSPtr->Reset();
    m_openedCells = 0;
    m_setFlags = 0;
}

void Minefield::GenerateField()
{
    Reset();
    PlaceMines();
    ShuffleFields();
    RebuildHints();
}

OpenCellResult Minefield::OpenCell(const std::size_t index)
{
    auto& cell = m_minefieldStorageSPtr->At(index);

    if (cell.IsOpen() || cell.IsFlagged() || IsGameFinished())
    {
        return OpenCellResult::NoOp;
    }

    if (GameState::FirstMove == m_state)
    {
        EnsureFirstMoveSafe(index);
        m_state = GameState::InProgress;
    }

    if (cell.IsMine())
    {
        RevealAllMines();
        m_state = GameState::Lost;
        return OpenCellResult::Exploded;
    }

    FloodOpen(index);
    if (IsWon())
    {
        m_state = GameState::Won;
        return OpenCellResult::Won;
    }

    return OpenCellResult::Opened;
}

void Minefield::ToggleFlag(const std::size_t index)
{
    auto& cell = m_minefieldStorageSPtr->At(index);

    if (IsGameFinished() || cell.IsOpen())
    {
        return;
    }

    cell.ToggleFlag();
    if (cell.IsFlagged())
    {
        ++m_setFlags;
    }
    else
    {
        --m_setFlags;
    }

    if (GameState::FirstMove == m_state)
    {
        m_state = GameState::InProgress;
    }
}

bool Minefield::IsGameFinished() const
{
    return GameState::Won == m_state || GameState::Lost == m_state;
}

bool Minefield::IsWon() const
{
    return m_openedCells == m_minefieldStorageSPtr->Size() - m_minefieldInteractorSPtr->Mines();
}

void Minefield::RevealAllMines()
{
    for (std::size_t i = 0; i < m_minefieldStorageSPtr->Size(); ++i)
    {
        if (m_minefieldStorageSPtr->At(i).IsMine())
        {
            m_minefieldStorageSPtr->At(i).Open();
        }
    }
}

void Minefield::PlaceMines()
{
    const auto maxMineCount = m_minefieldStorageSPtr->Size() - 1;
    const auto mineCount = std::min(m_minefieldInteractorSPtr->Mines(), maxMineCount);

    for (std::size_t i = 0; i < mineCount; ++i)
    {
        m_minefieldStorageSPtr->At(i).SetAsMine();
    }
}

void Minefield::ShuffleFields()
{
    static thread_local std::mt19937 rng {std::random_device{}()};

    for (std::size_t i = m_minefieldStorageSPtr->Size(); i > 1; --i)
    {
        std::uniform_int_distribution<std::size_t> dist{0, i - 1};
        const auto j = dist(rng);
        std::swap(m_minefieldStorageSPtr->At(i - 1), m_minefieldStorageSPtr->At(j));
    }
}

void Minefield::RebuildHints()
{
    for (std::size_t i = 0; i < m_minefieldStorageSPtr->Size(); ++i)
    {
        if (m_minefieldStorageSPtr->At(i).IsMine())
        {
            continue;
        }

        std::uint8_t minesCount = 0;
        m_minefieldStorageSPtr->ForEachNeighbour(i,
            [&minesCount]([[maybe_unused]] std::size_t, Field& cell)
            {
                if (cell.IsMine())
                {
                    ++minesCount;
                }
            }
        );

        m_minefieldStorageSPtr->At(i).SetValue(minesCount);
    }
}

void Minefield::FloodOpen(const std::size_t index)
{
    std::queue<std::size_t> pending;
    pending.push(index);

    while (!pending.empty())
    {
        const auto currentIndex = pending.front();
        pending.pop();

        auto& cell = m_minefieldStorageSPtr->At(currentIndex);
        if (cell.IsOpen() || cell.IsFlagged() || cell.IsMine())
        {
            continue;
        }

        cell.Open();
        ++m_openedCells;
        if (!cell.IsVoid())
        {
            continue;
        }

        m_minefieldStorageSPtr->ForEachNeighbour(currentIndex,
            [&pending](std::size_t index, Field& cell)
            {
                if (!cell.IsOpen() && !cell.IsFlagged())
                {
                    pending.push(index);
                }
            }
        );
    }
}

void Minefield::EnsureFirstMoveSafe(const std::size_t index)
{
    if (!m_minefieldStorageSPtr->At(index).IsMine())
    {
        return;
    }

    for (std::size_t i = 0; i < m_minefieldStorageSPtr->Size(); ++i)
    {
        if (index == i || m_minefieldStorageSPtr->At(i).IsMine())
        {
            continue;
        }

        m_minefieldStorageSPtr->At(i).IsMine();
        m_minefieldStorageSPtr->At(index).SetAsVoid();
        RebuildHints();
        return;
    }
}

} // namespace core
