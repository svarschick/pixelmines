#pragma once

#include "texture_interactor.h"
#include "resource_manager/resource_manager.h"

#include <QObject>
#include <QString>
#include <QQmlApplicationEngine>

#include <memory>

namespace app::managers
{

class TextureManager
{
public:
    TextureManager(ResourceManagerSPtr resourceManager,
                   const QQmlApplicationEngine& engine,
                   const QString& contextPropertyName
                   );

    void SetTexturePack(QString packName);

private:
    ResourceManagerSPtr m_resourceManagerSPtr;
    TextureInteractorSPtr m_textureInteractorSPtr;
};

using TextureManagerSPtr = std::shared_ptr<TextureManager>;

} // namespace app::managers
