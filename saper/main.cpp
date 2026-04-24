#include "managers/texture_manager/texture_manager.h"
#include "managers/resource_manager/resource_manager.h"
#include "managers/settings_manager/settings_manager.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
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
    textureManagerSPtr->SetTexturePack("prismarin");

    engine.loadFromModule("gui", "Main");

    return app.exec();
}
