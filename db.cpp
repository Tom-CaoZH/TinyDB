#include<iostream>
#include<string.h>

class DB
{
    public :
    void start();
    void print_promot();

    bool parse_meta_command(std::string command);
};

void DB::print_promot() {
    std::cout << "db > ";
}

bool DB::parse_meta_command(std::string command) {
    if(command == ".exit") {
        std::cout << "Bye!" << std::endl;
        exit(EXIT_SUCCESS);
    }
    else {
        std::cout << "Unrecognized command: " << command << std::endl;
        return true;
    }
    return false;
}

void DB::start() {
    while(true) {
        print_promot();

        std::string command;
        std::getline(std::cin, command);
        if(parse_meta_command(command)) {
            continue;
        }
    }
}

int main(void) {
    DB db;
    db.start();
    return 0;
}