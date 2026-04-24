#pragma once

#include "resource_manager/resource_manager.h"
#include "settings_interactor.h"

#include <QQmlApplicationEngine>
#include <QJsonObject>
#include <QString>

namespace app::managers
{

class SettingsManager
{
public:
    SettingsManager(ResourceManagerSPtr resourceManager,
                    const QQmlApplicationEngine& engine,
                    const QString& contextPropertyName
                    );

private:
    void InitJson();
    void UpdateJson();
    void SaveJson(QJsonDocument doc);

private:
    SettingsInteractorSPtr m_settingsInteractor;
    ResourceManagerSPtr m_resourceManagerSPtr;
};

} // namespace app::managers
