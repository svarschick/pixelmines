#pragma once

namespace app::managers::sql
{

namespace create_table
{

const char* gameHistory = R"(
    CREATE TABLE IF NOT EXIST game_history (
        game_history_id INTEGER PRIMARY KEY AUTOINCREMENT,
        difficulty_level_id INTEGER,
        profile_id INTEGER,
        time_seconds INTEGER,
        is_win BOOLEAN,
        played_at TEXT,
        FOREIGN KEY(difficulty_level_id) REFERENCE difficulty_level(difficulty_level_id),
        FOREIGN KEY(profile_id) REFERENCE profile(profile_id)
    );
)";

const char* profile = R"(
    CREATE TABLE IF NOT EXIST profile (
        profile_id INTEGER PRIMARY KEY AUTOINCREMENT,
        login TEXT,
        created_at TEXT
    );
)";

const char* difficultyLevel = R"(
    CREATE TABLE IF NOT EXIST difficulty_level (
        difficulty_level_id INTEGER PRIMARY KEY AUTOINCREMENT,
        difficulty_name TEXT,
        width INTEGER,
        height INTEGER,
        mines INTEGER
    )
)";

} // namespace create_table

namespace insert
{

const char* gameHistory = R"(
    INSERT INTO game_history(
        difficulty_level_id,
        profile_id,
        time_seconds,
        is_win,
        played_at
    ) VALUES(?, ?, ?, ?, ?);
)";

} // namespace insert

namespace select
{

const char* gameHistory = R"(
    SELECT
        difficulty_level_id,
        profile_id,
        time_seconds,
        is_win,
        played_at
    FROM game_history
)";

const char* profile = R"(
    SELECT
        profile_id,
        login,
        created_at
    FROM game_history
)";

const char* difficultyLevel = R"(
    SELECT
        difficulty_level_id,
        difficulty_name,
        width,
        height,
        mines
    FROM game_history
)";

}

} // namespace app::managers::sql
