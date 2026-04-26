#pragma once

#include <QObject>
#include <QtTypes>

#include <functional>
#include <memory>

namespace app::managers
{

class GameInteractor : public QObject
{
    Q_OBJECT
public:
    using ClickHandle = std::function<void(std::size_t)>;
    using Handle = std::function<void()>;

    GameInteractor(ClickHandle leftClickHandle,
                   ClickHandle rightClickHandle,
                   Handle startGameHandle,
                   QObject* parent = nullptr);

    void LeftClick(std::size_t cellIndex);
    void RightClick(std::size_t cellIndex);

    Q_INVOKABLE void start();

private:
    ClickHandle m_leftClickHandle;
    ClickHandle m_rightClickHandle;
    Handle m_startGameHandle;
};

using GameInteractorSPtr = std::shared_ptr<GameInteractor>;

} // namespace app::managers
