#include "managers/texture_manager/texture_manager.h"
#include "managers/resource_manager/resource_manager.h"
#include "managers/settings_manager/settings_manager.h"
#include "managers/session_manager/session_manager.h"
#include "managers/game_manager/game_manager.h"

#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QtQml/QQmlExtensionPlugin>

#include <memory>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.addImportPath(":/uikit/qml");
    engine.addImportPath(":/gui/qml");

    auto resourceManagerSPtr = std::make_shared<app::managers::ResourceManager>();
    auto textureManagerSPtr = std::make_shared<app::managers::TextureManager>(resourceManagerSPtr, engine, "textureInteractor");
    auto settingsManagerSPtr = std::make_shared<app::managers::SettingsManager>(resourceManagerSPtr, engine, "settingsInteractor");
    auto gameManagerSPtr = std::make_shared<app::managers::GameManager>(
        settingsManagerSPtr->GetSettingsInteractor(),
        engine,
        "gameInteractor",
        "minefieldModel");
    auto sessionManagerSPtr = std::make_shared<app::managers::SessionManager>(
        gameManagerSPtr->GetMinefieldInteractor(),
        engine,
        "sessionInteractor"
        );
    textureManagerSPtr->SetTexturePack("prismarin");

    engine.loadFromModule("gui", "Main");

    return app.exec();
}
