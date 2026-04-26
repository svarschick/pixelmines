#include "game_interactor.h"

namespace app::managers
{

GameInteractor::GameInteractor(
    ClickHandle leftClickHandle,
    ClickHandle rightClickHandle,
    Handle startGameHandle,
    QObject* parent
) :
    QObject(parent),
    m_leftClickHandle{ std::move(leftClickHandle) },
    m_rightClickHandle{ std::move(rightClickHandle) },
    m_startGameHandle{ std::move(startGameHandle) } {}

void GameInteractor::LeftClick(std::size_t cellIndex)
{
    m_leftClickHandle(cellIndex);
}

void GameInteractor::RightClick(std::size_t cellIndex)
{
    m_rightClickHandle(cellIndex);
}

void GameInteractor::start()
{
    m_startGameHandle();
}

} // namespace app::managers

