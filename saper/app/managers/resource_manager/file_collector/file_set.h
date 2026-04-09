#pragma once

#include <QString>
#include <QMap>

#include <memory>

namespace app::managers::file_collector
{

struct FileSet
{
    QString directoryName;
    QMap<QString, QString> files;

    QString FilePath(const QString& key) const;
};

using FileSetSPtr = std::shared_ptr<FileSet>;

} // namespace app::managers::file_collector
