#include "field.h"

namespace core
{

void Field::Reset()
{
    m_value = FIELD_VOID_VALUE;
    m_textureIndex = 0;
    m_isOpen = false;
    m_isFlagged = false;
}

void Field::SetAsMine()
{
    m_value = FIELD_MINE_VALUE;
}

void Field::SetAsVoid()
{
    m_value = FIELD_VOID_VALUE;
}

bool Field::IsMine() const
{
    return FIELD_MINE_VALUE == m_value;
}

bool Field::IsVoid() const
{
    return FIELD_VOID_VALUE == m_value;
}

bool Field::IsOpen() const
{
    return m_isOpen;
}

bool Field::IsFlagged() const
{
    return m_isFlagged;
}

void Field::SetValue(std::uint8_t value)
{
    m_value = value;
}

void Field::Open()
{
    m_isFlagged = true;
}

void Field::ToggleFlag()
{
    m_isFlagged = !m_isFlagged;
}

} // namespace core
