#pragma once

#include "file_set.h"

#include <QStringList>

#include <memory>

namespace app::managers::file_collector
{

class FileSetLoader
{
public:
    explicit FileSetLoader();

    QStringList ExistSetList() const;
    FileSetSPtr LoadSet(const QString& setName);

private:
    QString m_rootPath;
};

using FileSetLoaderSPtr = std::shared_ptr<FileSetLoader>;

} // namespace app::managers::file_collector
