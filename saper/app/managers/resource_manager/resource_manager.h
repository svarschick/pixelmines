#pragma once

#include "file_collector/file_set_loader.h"
#include "file_collector/file_set.h"
#include "texture_manager/texture_interactor.h"
#include "settings_manager/settings_interactor.h"

#include <QObject>

#include <memory>

namespace app::managers
{

class ResourceManager
{
public:
    explicit ResourceManager();

    void SetTextureInteractor(TextureInteractorSPtr textureInteractor);
    void SetSettingsInteractor(SettingsInteractorSPtr settingsInteractor);

    void SelectTextureSet(QString setName);

private:
    TextureInteractorSPtr m_textureInteractor;
    SettingsInteractorSPtr m_settingsInteractor;
    file_collector::FileSetLoaderSPtr m_fileSetLoader;
};

using ResourceManagerSPtr = std::shared_ptr<ResourceManager>;

} // namespace app::managers
