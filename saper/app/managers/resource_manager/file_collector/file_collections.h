#pragma once

#include <QMap>
#include <QString>

namespace app::managers::file_collector::collection
{

QMap<QString, QString> TextureCollection = {
    { "bg01",  "bg01.png" },
    { "buttonLeft",  "button_left_border.png" },
    { "buttonPlash", "button_plash.png" },
    { "buttonRight", "button_right_border.png" },
    { "leftButton", "left_button.png" },
    { "leftSliderBorder", "left_slider_border.png" },
    { "logo", "logo.png" },
    { "rightButton", "right_button.png" },
    { "rightSliderBorder", "right_slider_border.png" },
    { "selectedCheckbox", "selected_checkbox.png" },
    { "selectedCorner", "selected_corner.png" },
    { "selectedProfile", "selected_profile.png" },
    { "slider", "slider.png" },
    { "sliderPlash", "slider_plash.png" },
    { "unselectedButtonLeftBorder", "unselected_button_left_border.png" },
    { "unselectedButtonPlash", "unselected_button_plash.png" },
    { "unselectedButtonRightBorder", "unselected_button_right_border.png" },
    { "unselectedCheckbox", "unselected_checkbox.png" },
    { "unselectedCorner", "unselected_corner.png" },
    { "unselectedProfile", "unselected_profile.png" }
};

QMap<QString, QString> AudioCollection = {
};

} // namespace app::managers::file_collector
