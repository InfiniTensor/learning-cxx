#include"../exercise.h"
#include <iostream>



enum class ConnectionType : int {
    MySQL_CONN = 0,
    PostgreSQL_CONN,
    SQLite_CONN
};

enum class CommandType : int {
    MySQL_CMD = 0,
    PostgreSQL_CMD,
    SQLite_CMD
};

class DBConnection { //抽象类: 数据库连接
public: 
    virtual ConnectionType connect() = 0;
    virtual ~DBConnection() = default;
};  

class MySQLConnection : public DBConnection { //MySQL数据库连接
public:
    ConnectionType connect() override {   
        return ConnectionType::MySQL_CONN;
    }
};


class PostgreSQLConnection : public DBConnection { //PostgreSQL数据库连接
public:
    ConnectionType connect() override {
        return ConnectionType::PostgreSQL_CONN;
    }       
};
// TODO: 添加SQLiteConnection类
class SQLiteConnection : public DBConnection { };





class DBConnectionFactory { //工厂类: 创建数据库连接
public:
    // TODO: 扩展工厂方法以支持SQLite
    static DBConnection* createConnection(const std::string& dbType) {
        if (dbType == "MySQL") {
            return new MySQLConnection();
        } else if (dbType == "PostgreSQL") {
            return new PostgreSQLConnection();
        } else {
            return nullptr;
        }
    }
};





class DBCommand { //抽象类: 数据库命令
public:
    virtual CommandType execute() = 0;     
    virtual ~DBCommand() = default;
};

class MySQLCommand : public DBCommand { //MySQL数据库命令
public:
    CommandType execute() override {   
        return CommandType::MySQL_CMD;     
    }
};

class PostgreSQLCommand : public DBCommand { //PostgreSQL数据库命令
public:
    CommandType execute() override {        
        return CommandType::PostgreSQL_CMD;
    }
};
// TODO: 添加SQLiteCommand类
class SQLiteCommand : public DBCommand { };

class DBCommandFactory { //工厂类: 创建数据库命令
public:
    // TODO: 扩展工厂方法以支持SQLite
    static DBCommand* createCommand(const std::string& dbType) {
        if (dbType == "MySQL") {
            return new MySQLCommand();
        } else if (dbType == "PostgreSQL") {
            return new PostgreSQLCommand();
        } else {
            return nullptr; 
        }
    }
};




// ---- 不要修改以下代码 ---- 

class DB{ //数据库类: 使用工厂创建连接和命令
private:
    std::string dbType;
    DBConnection* connection;
    DBCommand* command;
public:
    DB(const std::string& type) : dbType(type) {
        connection = DBConnectionFactory::createConnection(dbType);
        command = DBCommandFactory::createCommand(dbType);
    }
    ConnectionType getConnectionT() {
        return connection->connect();
    }
    CommandType getCommandT() {
        return command->execute();
    }
};

int main() {

    DB mysqlDB("MySQL");
    ASSERT(mysqlDB.getConnectionT() == ConnectionType::MySQL_CONN, "MySQL 连接类型错误");
    ASSERT(mysqlDB.getCommandT() == CommandType::MySQL_CMD, "MySQL 命令类型错误");

    DB pgsqlDB("PostgreSQL");
    ASSERT(pgsqlDB.getConnectionT() == ConnectionType::PostgreSQL_CONN, "PostgreSQL 连接类型错误");
    ASSERT(pgsqlDB.getCommandT() == CommandType::PostgreSQL_CMD, "PostgreSQL 命令类型错误");
    
    DB sqliteDB("SQLite");
    ASSERT(sqliteDB.getConnectionT() == ConnectionType::SQLite_CONN, "SQLite 连接类型错误");
    ASSERT(sqliteDB.getCommandT() == CommandType::SQLite_CMD, "SQLite 命令类型错误");
    
    return 0;
}   
