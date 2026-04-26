#pragma once

#include "game/minefield_interactor.h"
#include "session_interactor.h"

#include <QQmlApplicationEngine>
#include <QString>

#include <memory>

namespace app::managers
{

class SessionManager
{
public:
    SessionManager(core::MinefieldInteractorSPtr minefieldInteractorSPtr,
                   const QQmlApplicationEngine& engine,
                   const QString& contextPropertyName);

private:
    SessionInteractorSPtr m_sessionInteractorSPtr;
};

using SessionManagerSPtr = std::shared_ptr<SessionManager>;

} // namespace app::managers
