#include "minefield_storage.h"

namespace core
{

MinefieldStorage::MinefieldStorage(MinefieldInteractorSPtr minefieldInteractor)
    : m_minefieldInteractorSPtr{ std::move(minefieldInteractor )} {}

void MinefieldStorage::Reset()
{
    m_storage.resize(Size());
    for (auto iter = m_storage.begin(); iter != m_storage.end(); ++iter)
    {
        iter->Reset();
    }
}

bool MinefieldStorage::IsValid(Pos x, Pos y) const
{
    return 0 < x
        && 0 < y
        && x < m_minefieldInteractorSPtr->Width()
        && y < m_minefieldInteractorSPtr->Height();
}

std::size_t MinefieldStorage::Size() const
{
    return m_minefieldInteractorSPtr->Width() * m_minefieldInteractorSPtr->Height();
}

std::size_t MinefieldStorage::Index(Pos x, Pos y) const
{
    return x + y * m_minefieldInteractorSPtr->Width();
}

Field& MinefieldStorage::At(Pos x, Pos y)
{
    return m_storage[Index(x, y)];
}

Field& MinefieldStorage::At(std::size_t index)
{
    return m_storage[index];
}

} // namespace core
