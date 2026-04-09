#pragma once

#include "file_hierarchy.h"

namespace app::managers::file_collector
{

QString operator/(const QString& rootPath, const QString& childPath)
{
    return rootPath + "/" + childPath;
}

} // namespace app::managers::file_collector
