#pragma once

#include <windows.h>
#include <shellapi.h>

#include <vector>
#include "domain/domain.h"
#include "repo/repo.h"
#include <iostream>
#include <string>
#include <cstring>
#include <winuser.h>


using namespace std;

class CSVRepo : public EventRepo {
public:
    CSVRepo(char file_name[]) : EventRepo(file_name) {};
    void write_to_file(const std::string& file_name) override;
    void open_link() override;
};

class HTMLRepo : public EventRepo {
public:
    HTMLRepo(char file_name[]) : EventRepo(file_name) {};
    void write_to_file(const std::string& file_name) override;
    void open_link() override;
};