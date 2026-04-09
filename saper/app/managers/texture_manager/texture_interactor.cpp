#include "texture_interactor.h"

namespace app::managers
{

TextureInteractor::TextureInteractor(QObject* obj) : QObject(obj) {}

void TextureInteractor::OnUpdateInteractor()
{
    emit textureButtonLeftBorderChanged();
    emit textureButtonPlashBorderChanged();
    emit textureButtonRightBorderChanged();
}

} // namespace app::managers
