#pragma once

#include <cstdint>

namespace core
{

constexpr const std::uint8_t FIELD_VOID_VALUE = 0;
constexpr const std::uint8_t FIELD_MINE_VALUE = 9;

class Field
{
public:
    void Reset();

    void SetAsMine();
    void SetAsVoid();
    void SetValue(std::uint8_t value);
    void SetTextureIndex(std::uint8_t value);

    bool IsMine() const;
    bool IsVoid() const;
    bool IsOpen() const;
    bool IsFlagged() const;
    std::uint8_t TextureIndex() const;

    void Open();
    void ToggleFlag();
    std::uint8_t Value() const;

private:
    std::uint8_t m_value;
    std::uint8_t m_textureIndex{0};
    bool m_isOpen{false};
    bool m_isFlagged{false};
};

} // namespace core
