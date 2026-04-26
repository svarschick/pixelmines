#include "settings_interactor.h"
#include "utility.h"

#include <algorithm>

namespace app::managers
{

SettingsInteractor::SettingsInteractor(QObject* parent) : QObject(parent) {}

void SettingsInteractor::OnUpdateInteractor()
{
    emit guiMultiplyChanged();
    emit musicVolumeChanged();
    emit soundVolumeChanged();
    emit audioVolumeChanged();
}

void SettingsInteractor::setGuiMultiply(qint32 value)
{
    m_guiMultiply = utility::ValueRange(value, 0, 100);
    m_updateFileCall();
    emit guiMultiplyChanged();
}
void SettingsInteractor::setMusicVolume(qint32 value)
{
    m_musicVolume = utility::ValueRange(value, 0, 100);
    m_updateFileCall();
    emit musicVolumeChanged();
}
void SettingsInteractor::setSoundVolume(qint32 value)
{
    m_soundVolume = utility::ValueRange(value, 0, 100);
    m_updateFileCall();
    emit soundVolumeChanged();
}
void SettingsInteractor::setAudioVolume(qint32 value)
{
    m_audioVolume = utility::ValueRange(value, 0, 100);
    m_updateFileCall();
    emit audioVolumeChanged();
}
void SettingsInteractor::setSettingsFile(QFileSPtr file)
{
    m_fileSPtr = file;
}
void SettingsInteractor::SetUpdateFileCall(std::function<void()> updateFileCall)
{
    m_updateFileCall = updateFileCall;
}

qint32 SettingsInteractor::guiMultiply() const
{
    return m_guiMultiply;
}
qint32 SettingsInteractor::musicVolume() const
{
    return m_musicVolume;
}
qint32 SettingsInteractor::soundVolume() const
{
    return m_soundVolume;
}
qint32 SettingsInteractor::audioVolume() const
{
    return m_audioVolume;
}
QFileSPtr SettingsInteractor::settingsFile() const
{
    return m_fileSPtr;
}

} // namespace app::managers
