#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <iostream>
#include <string>

class Database {

    public:
        Database();
        ~Database();
        int show();
        static int callback(void *NotUsed, int argc, char **argv, char **azColName);

        sqlite3 *ppDb = nullptr;
        char *errmsg;

    private:
        const char *filename = "saves.db";

        int createDatabase();
        int dropDatabase();

        int createGameModesTable();
        int createGameSubModesTable();
        int createStandartNetworkSessionTable();
};

#endif