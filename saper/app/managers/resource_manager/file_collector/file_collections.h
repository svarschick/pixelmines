#pragma once

#include <QMap>
#include <QString>

namespace app::managers::file_collector::collection
{

QMap<QString, QString> TextureCollection = {
    { "textureButtonLeftBorder",  "button_left_border.png" },
    { "textureButtonPlashBorder", "button_plash.png" },
    { "textureButtonRightBorder", "button_right_border.png" }
};

QMap<QString, QString> AudioCollection = {
};

} // namespace app::managers::file_collector
