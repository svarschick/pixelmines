#pragma once

#include <cstdint>
#include <memory>

namespace core
{

class MinefieldInteractor
{
public:
    void Init(std::uint16_t height, std::uint16_t width, std::uint64_t mines);

    std::uint16_t Height() const;
    std::uint16_t Width() const;
    std::uint64_t Mines() const;

private:
    std::uint16_t m_height {0};
    std::uint16_t m_width {0};
    std::uint64_t m_mines {0};
};

using MinefieldInteractorSPtr = std::shared_ptr<MinefieldInteractor>;

} // namespace core
