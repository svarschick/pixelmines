#include "session_manager.h"

#include <QQmlContext>
#include <QDebug>

namespace app::managers
{

SessionManager::SessionManager(core::MinefieldInteractorSPtr minefieldInteractorSPtr,
                               const QQmlApplicationEngine& engine,
                               const QString& contextPropertyName)
{
    m_sessionInteractorSPtr = std::make_shared<SessionInteractor>(minefieldInteractorSPtr);
    engine.rootContext()->setContextProperty(contextPropertyName, m_sessionInteractorSPtr.get());
    qInfo() << "[SessionManager]: init successful!";
}

} // namespace app::managers

