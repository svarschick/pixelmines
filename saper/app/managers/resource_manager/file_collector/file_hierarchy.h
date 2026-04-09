#pragma once

#include <QString>

namespace app::managers::file_collector
{

QString operator/(const QString& rootPath, const QString& childPath);

namespace path {

const QString RootResourcePath = "resources";
const QString TexturePath = "texture";
const QString AudioPath = "audio";

} // namespace path

} // namespace app::managers::file_collector
