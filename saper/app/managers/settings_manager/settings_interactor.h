#pragma once

#include "resource_manager/i_update_interactor.h"

#include <QObject>
#include <QFile>
#include <QtTypes>

#include <memory>
#include <functional>

namespace app::managers
{

using QFileSPtr = std::shared_ptr<QFile>;

class SettingsInteractor : public QObject, IUpdateInteractor
{
    Q_OBJECT
public:

    Q_PROPERTY(qint32 guiMultiply READ guiMultiply WRITE setGuiMultiply NOTIFY guiMultiplyChanged)
    Q_PROPERTY(qint32 musicVolume READ musicVolume WRITE setMusicVolume NOTIFY musicVolumeChanged)
    Q_PROPERTY(qint32 soundVolume READ soundVolume WRITE setSoundVolume NOTIFY soundVolumeChanged)
    Q_PROPERTY(qint32 audioVolume READ audioVolume WRITE setAudioVolume NOTIFY audioVolumeChanged)

public:
    SettingsInteractor(QObject* parent = nullptr);

    void OnUpdateInteractor() override;

    void setGuiMultiply(qint32 value);
    void setMusicVolume(qint32 value);
    void setSoundVolume(qint32 value);
    void setAudioVolume(qint32 value);
    void setSettingsFile(QFileSPtr file);

    qint32 guiMultiply() const;
    qint32 musicVolume() const;
    qint32 soundVolume() const;
    qint32 audioVolume() const;
    QFileSPtr settingsFile() const;

    void SetUpdateFileCall(std::function<void()> updateFileCall);

signals:
    void guiMultiplyChanged();
    void musicVolumeChanged();
    void soundVolumeChanged();
    void audioVolumeChanged();

private:
    qint32 m_guiMultiply = 0;
    qint32 m_musicVolume = 0;
    qint32 m_soundVolume = 0;
    qint32 m_audioVolume = 0;
    QFileSPtr m_fileSPtr;
    std::function<void()> m_updateFileCall;
};

using SettingsInteractorSPtr = std::shared_ptr<SettingsInteractor>;

} // namespace app::managers
