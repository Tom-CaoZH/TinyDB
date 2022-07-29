#include<iostream>
#include<string.h>


enum MetaCommandResult
{
    META_COMMAND_SUCCESS,
    META_UNRECOGNIZED_COMMAND
};

enum PrepareResult
{
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
};

enum StatementType 
{
    STATEMENT_INSERT,
    STATEMENT_SELECT
};

class Statement
{
    public:
        StatementType type;
};

class DB
{
    public :
    void start();
    void print_promot();

    bool parse_meta_command(std::string &command);
    MetaCommandResult commit_meta_command(std::string &command);

    PrepareResult prepare_statement(std::string &input, Statement &statement);
    bool parse_statement(std::string &input, Statement &statement);
    void execute_statement(Statement &statement);
};

void DB::print_promot() {
    std::cout << "db > ";
}

bool DB::parse_meta_command(std::string &command) {
    if(command[0] == '.') {
        switch(commit_meta_command(command)){
            case META_COMMAND_SUCCESS:
                return true;
            case META_UNRECOGNIZED_COMMAND:
                std::cout << "Unrecognized command: " << command << std::endl;
                return true;
        }
    }
    return false;
}

MetaCommandResult DB::commit_meta_command(std::string &command) {
    if(command == ".exit") {
        std::cout << "Bye!" << std::endl;
        exit(EXIT_SUCCESS);
    }
    else {
        return META_UNRECOGNIZED_COMMAND;
    }
}

PrepareResult DB::prepare_statement(std::string &command, Statement &statement) {
    if(!command.compare(0,6,"insert")) {
        statement.type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    else if(!command.compare(0,6,"select")) {
        statement.type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    else {
        return PREPARE_UNRECOGNIZED_STATEMENT;
    }
}

bool DB::parse_statement(std::string &input, Statement &statement) {
    switch(prepare_statement(input, statement)) {
        case PREPARE_SUCCESS:
            return false;
        case PREPARE_UNRECOGNIZED_STATEMENT:
            std::cout << "Unrecognized keyword at start of '" << input << "'." << std::endl;
            return true;
    }
    return false;
}

void DB::execute_statement(Statement &statement) {
    switch(statement.type) {
        case STATEMENT_INSERT:
            std::cout << "Executing insert statement" << std::endl; 
            break;
        case STATEMENT_SELECT:
            std::cout << "Executing select statement" << std::endl; 
            break;
    }
}

void DB::start() {
    while(true) {
        print_promot();

        std::string command;
        std::getline(std::cin, command);
        if(parse_meta_command(command)) {
            continue;
        }

        Statement statement;

        if(parse_statement(command, statement)) {
            continue;
        }

        execute_statement(statement);
    }
}

int main(void) {
    DB db;
    db.start();
    return 0;
}