#include "settings_manager.h"

#include <QDebug>
#include <QJsonDocument>
#include <QQmlContext>

namespace app::managers
{

SettingsManager::SettingsManager(ResourceManagerSPtr resourceManager,
                const QQmlApplicationEngine& engine,
                const QString& contextPropertyName
             ) : m_resourceManagerSPtr{resourceManager}
{
    m_settingsInteractorSPtr = std::make_shared<SettingsInteractor>();
    m_settingsInteractorSPtr->SetUpdateFileCall([this](){ this->UpdateJson(); });
    m_resourceManagerSPtr->SetSettingsInteractor(m_settingsInteractorSPtr);
    engine.rootContext()->setContextProperty(contextPropertyName, m_settingsInteractorSPtr.get());
    InitJson();
    qInfo() << "[SettingsManager]: init successful!";
}

SettingsInteractorSPtr SettingsManager::GetSettingsInteractor()
{
    return m_settingsInteractorSPtr;
}

void SettingsManager::InitJson()
{
    if (!m_settingsInteractorSPtr->settingsFile()->exists())
    {
        qWarning() << "[SettingsManager]: json settings file does not exist.";
        return;
    }

    if (!m_settingsInteractorSPtr->settingsFile()->open(QIODeviceBase::ReadOnly))
    {
        qWarning() << "[SettingsManager]: cannot open json for read settings.";
        return;
    }

    auto json = QJsonDocument::fromJson(m_settingsInteractorSPtr->settingsFile()->readAll()).object();
    m_settingsInteractorSPtr->settingsFile()->close();
    if (json.isEmpty())
    {
        qWarning() << "[SettingsManager]: json is empty.";
        return;
    }

    m_settingsInteractorSPtr->setGuiMultiply(json["guiMultiply"].toInt());
    m_settingsInteractorSPtr->setMusicVolume(json["musicVolume"].toInt());
    m_settingsInteractorSPtr->setSoundVolume(json["soundVolume"].toInt());
    m_settingsInteractorSPtr->setAudioVolume(json["audioVolume"].toInt());
}

void SettingsManager::UpdateJson()
{
    QJsonObject settings
    {
        { "guiMultiply", m_settingsInteractorSPtr->guiMultiply() },
        { "musicVolume", m_settingsInteractorSPtr->musicVolume() },
        { "soundVolume", m_settingsInteractorSPtr->soundVolume() },
        { "audioVolume", m_settingsInteractorSPtr->audioVolume() }
    };

    SaveJson(QJsonDocument{settings});
}

void SettingsManager::SaveJson(QJsonDocument settings)
{
    if (!m_settingsInteractorSPtr->settingsFile()->open(QIODeviceBase::WriteOnly | QIODeviceBase::Truncate))
    {
        qWarning() << "[SettingsManager]: cannot open json for save settings.";
        return;
    }

    m_settingsInteractorSPtr->settingsFile()->write(settings.toJson(QJsonDocument::Indented));
    m_settingsInteractorSPtr->settingsFile()->close();
}

} // namespace app::managers
