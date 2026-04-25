#include "minefield_interactor.h"

namespace core
{

void MinefieldInteractor::Init(std::uint16_t height, std::uint16_t width, std::uint64_t mines)
{
    m_height = height;
    m_width = width;
    m_mines = mines;
}

std::uint16_t MinefieldInteractor::Height() const
{
    return m_height;
}

std::uint16_t MinefieldInteractor::Width() const
{
    return m_width;
}

std::uint64_t MinefieldInteractor::Mines() const
{
    return m_mines;
}

} // namespace core
