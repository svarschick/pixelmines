#pragma once

#include "minefield_interactor.h"
#include "minefield_storage.h"

namespace core
{

enum class GameState
{
    FirstMove,
    InProgress,
    Won,
    Lost,
};

enum class OpenCellResult
{
    NoOp,
    Opened,
    Exploded,
    Won,
};

class Minefield
{
public:
    explicit Minefield(MinefieldInteractorSPtr minefieldInteractor,
                       MinefieldStorageSPtr minefieldStorageSPtr);

    void Reset();
    void GenerateField();

    void ToggleFlag(const std::size_t index);
    OpenCellResult OpenCell(const std::size_t index);

private:
    bool IsGameFinished() const;
    bool IsWon() const;
    void RevealAllMines();
    void PlaceMines();
    void ShuffleFields();
    void RebuildHints();
    void FloodOpen(const std::size_t index);
    void EnsureFirstMoveSafe(const std::size_t index);

private:
    GameState m_state;
    MinefieldInteractorSPtr m_minefieldInteractorSPtr;
    MinefieldStorageSPtr m_minefieldStorageSPtr;
    std::size_t m_openedCells{0};
    std::size_t m_setFlags{0};
};

} // namespace core
