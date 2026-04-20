#pragma once

#include <sqlite3.h>

#include <QDebug>
#include <QString>

#include <string>
#include <memory>

namespace app::managers
{

class SqlHandler
{
public:
    SqlHandler(const std::string dbName)
    {
        auto rc = sqlite3_open(dbName.c_str(), m_db);
        if (rc != SQLITE_OK)
        {
            qDebug() << "[ERROR][SqlHandler] cannot open data base.";
            sqlite3_close(m_db);
        }
    }
    bool ExecuteSql(const std::string& sql)
    {
        char* errMsg = nullptr;
        const auto rc = sqlite3_exec(m_db, sql.c_str(), nullptr, nullptr, errMsg);

        if (rc != SQLITE_OK)
        {
            qDebug() << "[ERROR][SqlHandler] failed execute sql query. error message:" << errMsg ? QString(errMsg) : "unknown";
            sqlite3_free(errMsg);
            return false;
        }

        return true;
    }

private:
    sqlite3* m_db;
};

using SqlHandlerUPtr = std::unique_ptr<SqlHandler>;

} // namespace app::managers
