#include "game_manager.h"

#include <QQmlContext>

namespace app::managers
{

GameManager::GameManager(
    SettingsInteractorSPtr settingsInteractorSPtr,
    const QQmlApplicationEngine& engine,
    const QString& contextPropertyName,
    const QString& contextMinefieldModelName) :
    m_settingsInteractorSPtr { std::move(settingsInteractorSPtr) }
{
    m_minefieldInteractorSPtr = std::make_shared<core::MinefieldInteractor>();
    m_minefieldStorageSPtr = std::make_shared<core::MinefieldStorage>(m_minefieldInteractorSPtr);
    m_minefieldSPtr = std::make_shared<core::Minefield>(m_minefieldInteractorSPtr, m_minefieldStorageSPtr);
    m_gameInteractorSPtr = std::make_shared<GameInteractor>(
        [this](std::size_t cellIndex)
        {
            this->LeftClickHandle(cellIndex);
        },
        [this](std::size_t cellIndex)
        {
            this->RightClickHandle(cellIndex);
        },
        [this]()
        {
            this->StartGameHandle();
        }
    );
    m_minefieldModelSPtr = std::make_shared<core::MinefieldModel>(
        m_minefieldInteractorSPtr,
        m_minefieldStorageSPtr,
        m_gameInteractorSPtr,
        m_settingsInteractorSPtr);

    engine.rootContext()->setContextProperty(contextPropertyName, m_gameInteractorSPtr.get());
    engine.rootContext()->setContextProperty(contextMinefieldModelName, m_minefieldModelSPtr.get());

    qInfo() << "[GameManager]: init successful!";

    m_minefieldInteractorSPtr->Init(10, 10, 10);
    m_gameInteractorSPtr->start();
}

core::MinefieldInteractorSPtr GameManager::GetMinefieldInteractor()
{
    return m_minefieldInteractorSPtr;
}

core::MinefieldStorageSPtr GameManager::GetMinefieldStorage()
{
    return m_minefieldStorageSPtr;
}

void GameManager::LeftClickHandle(std::size_t cellIndex)
{
    qDebug() << "[GameManager]: index" << cellIndex << "clicked";
}

void GameManager::RightClickHandle(std::size_t cellIndex)
{
    qDebug() << "[GameManager]: index" << cellIndex << "clicked";
}

void GameManager::StartGameHandle()
{
    m_minefieldSPtr->GenerateField();
    m_minefieldModelSPtr->RefreshModel();
}

} // namespace app::managers
