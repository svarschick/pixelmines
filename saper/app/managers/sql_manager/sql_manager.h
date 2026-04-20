#pragma once

#include "sql_handler.h"
#include "sql_query.h"

#include <memory>

namespace app::managers
{

class SqlManager
{
public:
    SqlManager(const std::string& dbName) : m_dbName{dbName}
    {
        m_handler = std::make_shared<SqlHandler>(m_dbName);

    }

private:
    const std::string m_dbName;
    SqlHandlerUPtr m_handler;
};

} // namespace app::managers
