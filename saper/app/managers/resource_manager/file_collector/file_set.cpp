#include "file_set.h"

namespace app::managers::file_collector
{

QString FileSet::FilePath(const QString& key) const
{
    return files.value(key);
}

} // namespace app::managers::file_collector
