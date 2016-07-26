#include <stdio.h>
#include <boost/format.hpp>

#include "sqlite/sqlite3.h"
#include "sqlite/sqlite3_injector.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    printf("\t");
    for(int i=0; i < argc; i++)
    {
        printf("%s = %s | ", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main(int argc, const char * argv[]) {

    const char * db_name        = "encrypted.db";
    const char * sql_create     = "CREATE TABLE hardened_table(_id INTEGER PRIMARY KEY, _text TEXT);";
    const char * sql_insert     = "INSERT INTO hardened_table VALUES(%1%, 'Test string #%2%');";
    const char * sql_select     = "SELECT * FROM hardened_table;";
    char       * error_text;
    const unsigned char key[]   = "X";
    
    sqlite3 *db;
    int result;
    printf("SQLite injecting encryption PoC...\n");
    
    remove(db_name);
    
    printf("sqlite3_open %d\n", result = sqlite3_open_v2(db_name, &db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL));
    if (SQLITE_OK == result)
    {
        printf("sqlite3_key %d\n", result =  sqlite3_key(db, key, 1));
        if (SQLITE_OK == result)
        {
            printf("sqlite3_exec CREATE %d %s\n", result = sqlite3_exec(db, sql_create, 0, 0, &error_text),
             error_text ? error_text : "");
            if (SQLITE_OK == result)
            {
                for (int i=0; i < 10; i++)
                {
                    printf("sqlite3_exec INSERT %d %s\n",
                        result =  sqlite3_exec(db, boost::str(boost::format(sql_insert) % i % i).c_str(), callback,
                        0, &error_text), error_text ? error_text : "");
                }
            }
        }
        sqlite3_close(db);
    }
    else
    {
        printf("can't open %s\n", db_name);
    }
    
    printf("sqlite3_open %d\n", result = sqlite3_open_v2(db_name, &db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL));
    if (SQLITE_OK == result)
    {
        // comment line below to see an error 26 (file is encrypted or is not a database)
        printf("sqlite3_key %d\n", result =  sqlite3_key(db, key, 1));
        if (SQLITE_OK == result)
        {
            printf("sqlite3_exec SELECT %d %s\n", result = sqlite3_exec(db, sql_select, callback, 0, &error_text), 
                error_text ? error_text : "");
        }
        sqlite3_close(db);
    }
    else
    {
        printf("can't open %s\n", db_name);
    }
}
