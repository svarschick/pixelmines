#include "resource_manager.h"

#include <QDebug>
#include <QByteArray>
#include <QVariant>

namespace app::managers
{

template<typename T>
void UpdateInteractor(T interactor, file_collector::FileSetSPtr fileSet)
{
    if (!interactor)
    {
        qWarning() << "[ResourceManager]: undefined texture interactor";
        return;
    }

    for (auto it = fileSet->files.begin(); it != fileSet->files.end(); ++it)
    {
        const QByteArray propertyName = it.key().toUtf8();
        const QVariant value = it.value();

        if (!static_cast<QObject*>(interactor.get())->setProperty(propertyName.constData(), value))
        {
            qWarning() << "[ResourceManager]: failed to set property" << propertyName;
        }
    }

    interactor->OnUpdateInteractor();
    qDebug() << interactor->m_textureButtonLeftBorder;
}

ResourceManager::ResourceManager()
{
    m_fileSetLoader = std::make_shared<file_collector::FileSetLoader>();
}

void ResourceManager::SetTextureInteractor(TextureInteractorSPtr textureInteractor)
{
    m_textureInteractor = textureInteractor;
}

void ResourceManager::SelectTextureSet(QString setName)
{
    auto fileSet = m_fileSetLoader->LoadSet(setName);
    if (!fileSet)
    {
        qWarning() << "[ResourceManager]: undefined set" << setName;
        return;
    }

    UpdateInteractor(m_textureInteractor, std::move(fileSet));
}

} // namespace app::managers
