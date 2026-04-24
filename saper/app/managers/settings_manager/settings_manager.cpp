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
    m_settingsInteractor = std::make_shared<SettingsInteractor>();
    m_settingsInteractor->SetUpdateFileCall([this](){ this->UpdateJson(); });
    m_resourceManagerSPtr->SetSettingsInteractor(m_settingsInteractor);
    engine.rootContext()->setContextProperty(contextPropertyName, m_settingsInteractor.get());
    InitJson();
    qInfo() << "[SettingsManager]: init successful!";
}

void SettingsManager::InitJson()
{
    if (!m_settingsInteractor->settingsFile()->exists())
    {
        qWarning() << "[SettingsManager]: json settings file does not exist.";
        return;
    }

    if (!m_settingsInteractor->settingsFile()->open(QIODeviceBase::ReadOnly))
    {
        qWarning() << "[SettingsManager]: cannot open json for read settings.";
        return;
    }

    auto json = QJsonDocument::fromJson(m_settingsInteractor->settingsFile()->readAll()).object();
    m_settingsInteractor->settingsFile()->close();
    if (json.isEmpty())
    {
        qWarning() << "[SettingsManager]: json is empty.";
        return;
    }

    m_settingsInteractor->setGuiMultiply(json["guiMultiply"].toInt());
    m_settingsInteractor->setMusicVolume(json["musicVolume"].toInt());
    m_settingsInteractor->setSoundVolume(json["soundVolume"].toInt());
    m_settingsInteractor->setAudioVolume(json["audioVolume"].toInt());
}

void SettingsManager::UpdateJson()
{
    QJsonObject settings
    {
        { "guiMultiply", m_settingsInteractor->guiMultiply() },
        { "musicVolume", m_settingsInteractor->musicVolume() },
        { "soundVolume", m_settingsInteractor->soundVolume() },
        { "audioVolume", m_settingsInteractor->audioVolume() }
    };

    SaveJson(QJsonDocument{settings});
}

void SettingsManager::SaveJson(QJsonDocument settings)
{
    if (!m_settingsInteractor->settingsFile()->open(QIODeviceBase::WriteOnly | QIODeviceBase::Truncate))
    {
        qWarning() << "[SettingsManager]: cannot open json for save settings.";
        return;
    }

    m_settingsInteractor->settingsFile()->write(settings.toJson(QJsonDocument::Indented));
    m_settingsInteractor->settingsFile()->close();
}

} // namespace app::managers
