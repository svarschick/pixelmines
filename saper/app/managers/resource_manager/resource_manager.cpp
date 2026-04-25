#include "resource_manager.h"
#include "file_collector/file_hierarchy.h"

#include <QDebug>
#include <QByteArray>
#include <QVariant>
#include <QFile>

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
}

ResourceManager::ResourceManager()
{
    m_fileSetLoader = std::make_shared<file_collector::FileSetLoader>();
    qInfo() << "[ResourceManager]: init successful!";
}

void ResourceManager::SetTextureInteractor(TextureInteractorSPtr textureInteractor)
{
    m_textureInteractor = textureInteractor;
}

void ResourceManager::SetSettingsInteractor(SettingsInteractorSPtr settingsInteractor)
{
    using namespace file_collector;
    m_settingsInteractor = settingsInteractor;

    auto settingsFileSPtr = std::make_shared<QFile>(path::RootResourcePath / SettingsFile);
    m_settingsInteractor->setSettingsFile(std::move(settingsFileSPtr));
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
