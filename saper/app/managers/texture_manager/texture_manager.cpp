#include "texture_manager.h"

#include <QQmlContext>

namespace app::managers
{

TextureManager::TextureManager(ResourceManagerSPtr resourceManager, const QQmlApplicationEngine& engine, const QString& contextPropertyName)
    : m_resourceManagerSPtr{std::move(resourceManager)}
{
    m_textureInteractorSPtr = std::make_shared<TextureInteractor>();
    m_resourceManagerSPtr->SetTextureInteractor(m_textureInteractorSPtr);
    engine.rootContext()->setContextProperty(contextPropertyName, m_textureInteractorSPtr.get());
}
void TextureManager::SetTexturePack(QString packName)
{
    m_resourceManagerSPtr->SelectTextureSet("prismarin");
}

} // namespace app::managers
