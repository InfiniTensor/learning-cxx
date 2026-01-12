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
class SQLiteConnection : public DBConnection { //SQLite数据库连接
public:
    ConnectionType connect() override {
        return ConnectionType::SQLite_CONN;
    }
};


class ConnectionFactory{ // 抽象工厂类: 创建数据库连接
public: 
    virtual DBConnection* createConnection() = 0;
};

class MySQLConnectionFactory : public ConnectionFactory{
public:
    DBConnection* createConnection() override { 
        return new MySQLConnection();
    }
};

class PostgreSQLConnectionFactory : public ConnectionFactory{ 
public:
    DBConnection* createConnection() override {
        return new PostgreSQLConnection();
    }
};
// TODO: 实现 SQLiteConnectionFactory 类
class SQLiteConnectionFactory : public ConnectionFactory{
public:
    DBConnection* createConnection() override {
        return new SQLiteConnection();
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
class SQLiteCommand : public DBCommand { //SQLite数据库命令
public:
    CommandType execute() override {   
        return CommandType::SQLite_CMD;
    }
};

class CommandFactory{ // 抽象工厂类: 创建数据库命令
public:
    virtual DBCommand* createCommand() = 0;
};

class MySQLCommandFactory : public CommandFactory{
public:
    DBCommand* createCommand() override { 
        return new MySQLCommand();  
    }
};

class PostgreSQLCommandFactory : public CommandFactory{
public:
    DBCommand* createCommand() override { 
        return new PostgreSQLCommand();
    }
};

// TODO: 实现 SQLiteCommandFactory 类
class SQLiteCommandFactory : public CommandFactory{
public:
    DBCommand* createCommand() override { 
        return new SQLiteCommand();  
    }
};




// ---- 不要修改以下代码 ---- 
class DB{ //数据库类: 使用工厂创建连接和命令
private:
    std::string dbType;

    ConnectionFactory* connectionFactory;
    CommandFactory* commandFactory;
    DBConnection* connection;
    DBCommand* command;
public:
    DB(const std::string& type) : dbType(type) {
        if(dbType=="MySQL") {
            connectionFactory = new MySQLConnectionFactory();
            commandFactory = new MySQLCommandFactory();
            connection = connectionFactory->createConnection();
            command = commandFactory->createCommand();
        } else if(dbType=="PostgreSQL") {
            connectionFactory = new PostgreSQLConnectionFactory();
            commandFactory = new PostgreSQLCommandFactory();
            connection = connectionFactory->createConnection();
            command = commandFactory->createCommand();
        } else if(dbType=="SQLite") {
            connectionFactory = new SQLiteConnectionFactory();
            commandFactory = new SQLiteCommandFactory();
            connection = connectionFactory->createConnection();
            command = commandFactory->createCommand();
        }
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
