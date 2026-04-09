#pragma once

#include <QDir>
#include <QUrl>
#include <QFileInfo>
#include <QDebug>
#include <QCoreApplication>

#include "file_set_loader.h"
#include "file_hierarchy.h"
#include "file_collections.h"

namespace app::managers::file_collector
{

FileSetLoader::FileSetLoader()
{
    m_rootPath = QCoreApplication::applicationDirPath() / path::RootResourcePath;
}

QStringList FileSetLoader::ExistSetList() const
{
    QDir rootDir(m_rootPath);

    if (!rootDir.exists())
    {
        qWarning() << "[FileSetLoader]: root set directory does not exist:" << m_rootPath;
        return {};
    }

    const QFileInfoList entries =
        rootDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    QStringList setList;
    for (const QFileInfo& dirInfo : entries)
    {
        setList.append(dirInfo.fileName());
    }

    return setList;
}

FileSetSPtr FileSetLoader::LoadSet(const QString& setName)
{
    QStringList setList = ExistSetList();

    if (setList.indexOf(setName) == -1)
    {
        qWarning() << "[FileSetLoader]: does not exist set:" << setName;
        return {};
    }

    auto fileSetPath = m_rootPath / setName;
    auto fileSetSPtr = std::make_shared<FileSet>();
    fileSetSPtr->directoryName = setName;

    auto loadCollection = [fileSetPath, setName, &fileSetSPtr](QString path, QMap<QString, QString> collection) {
        QDir collectionDir(fileSetPath / path);
        if (!collectionDir.exists())
        {
            qWarning() << "[FileSetLoader]: does not exist texture set directory";
            return;
        }

        for (auto it = collection.begin(); it != collection.end(); ++it)
        {
            const QString fullPath = collectionDir.filePath(it.value());
            if (!QFileInfo::exists(fullPath))
            {
                qWarning() << "[FileSetLoader]: skipped set" << setName << "\n\t- missing file:" << it.value();
                return;
            }

            fileSetSPtr->files.insert(it.key(), QUrl::fromLocalFile(fullPath).toString());
        }
    };

    loadCollection(path::TexturePath, collection::TextureCollection);
    loadCollection(path::AudioPath, collection::AudioCollection);

    return fileSetSPtr;
}

} // namespace app::managers::file_collector
