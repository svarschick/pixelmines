#pragma once

#include "game/minefield_interactor.h"
#include "game/minefield_storage.h"
#include "game/minefield.h"
#include "playground/minefield_model.h"

#include "settings_manager/settings_interactor.h"
#include "game_interactor.h"

#include <QQmlApplicationEngine>
#include <QString>

#include <memory>

namespace app::managers
{

class GameManager
{
public:
    GameManager(SettingsInteractorSPtr settingsInteractorSPtr,
                const QQmlApplicationEngine& engine,
                const QString& contextPropertyName,
                const QString& contextMinefieldModelName);

    core::MinefieldInteractorSPtr GetMinefieldInteractor();
    core::MinefieldStorageSPtr GetMinefieldStorage();

private:
    void LeftClickHandle(std::size_t cellIndex);
    void RightClickHandle(std::size_t cellIndex);
    void StartGameHandle();

private:
    core::MinefieldInteractorSPtr m_minefieldInteractorSPtr;
    core::MinefieldStorageSPtr m_minefieldStorageSPtr;
    core::MinefieldSPtr m_minefieldSPtr;
    core::MinefieldModelSPtr m_minefieldModelSPtr;

    GameInteractorSPtr m_gameInteractorSPtr;
    SettingsInteractorSPtr m_settingsInteractorSPtr;
};

using GameManagerSPtr = std::shared_ptr<GameManager>;

} // namespace app::managers
