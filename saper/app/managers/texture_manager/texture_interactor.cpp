#include "texture_interactor.h"

namespace app::managers
{

TextureInteractor::TextureInteractor(QObject* obj) : QObject(obj) {}

void TextureInteractor::OnUpdateInteractor()
{
    emit bg01Changed();
    emit buttonLeftChanged();
    emit buttonPlashChanged();
    emit buttonRightChanged();
    emit leftButtonChanged();
    emit leftSliderBorderChanged();
    emit logoChanged();
    emit rightButtonChanged();
    emit rightSliderBorderChanged();
    emit selectedCheckboxChanged();
    emit selectedCornerChanged();
    emit selectedProfileChanged();
    emit sliderChanged();
    emit sliderPlashChanged();
    emit unselectedButtonLeftBorderChanged();
    emit unselectedButtonPlashChanged();
    emit unselectedButtonRightBorderChanged();
    emit unselectedCheckboxChanged();
    emit unselectedCornerChanged();
    emit unselectedProfileChanged();
}

} // namespace app::managers
