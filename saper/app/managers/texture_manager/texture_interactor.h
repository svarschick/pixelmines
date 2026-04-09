#pragma once

#include "resource_manager/i_update_interactor.h"

#include <QString>
#include <QObject>

#include <memory>

namespace app::managers
{

class TextureInteractor : public QObject, IUpdateInteractor
{
    Q_OBJECT
public:

    Q_PROPERTY(QString textureButtonLeftBorder MEMBER m_textureButtonLeftBorder NOTIFY textureButtonLeftBorderChanged)
    Q_PROPERTY(QString textureButtonPlashBorder MEMBER m_textureButtonPlashBorder NOTIFY textureButtonPlashBorderChanged)
    Q_PROPERTY(QString textureButtonRightBorder MEMBER m_textureButtonRightBorder NOTIFY textureButtonRightBorderChanged)

public:
    TextureInteractor(QObject* obj = nullptr);

    void OnUpdateInteractor() override;

signals:
    void textureButtonLeftBorderChanged();
    void textureButtonPlashBorderChanged();
    void textureButtonRightBorderChanged();

public:
    QString m_textureButtonLeftBorder;
    QString m_textureButtonPlashBorder;
    QString m_textureButtonRightBorder;
};

using TextureInteractorSPtr = std::shared_ptr<TextureInteractor>;

} // namespace app::managers
