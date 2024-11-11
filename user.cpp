#include "user.h"
#include "service.h"
//#include "ui.h"

#include <utility>
#include <cstring>



void CSVRepo::write_to_file(const string& file_name) {
    ofstream outfile(file_name);
    if (outfile.is_open()) {
        for (auto event : this->events)
        {
            outfile << event.getTitle() << "," << event.getDescription() << "," << event.getDate() << ","
                << event.getTime() << "," << event.getPeople() << "," << event.getLink() << endl;
        }
        outfile.close();
    }
    else {
        std::cout << "Unable to open file for writing!" << std::endl;
    }
}

void CSVRepo::open_link() {
    string aux;
    aux = "\"" + std::string(file_name) + "\"";
    ShellExecuteA(NULL, NULL, "excel.exe", aux.c_str(), NULL, SW_SHOWMAXIMIZED);
}

void HTMLRepo::write_to_file(const string& file_name) {
    ofstream outfile(file_name);
    if (outfile.is_open()) {
        outfile << "<!DOCTYPE html>\n";
        outfile << "<html>\n";
        outfile << "<head>\n";
        outfile << "   <title>Events</title>\n";
        outfile << "</head>\n";
        outfile << "<body>\n";
        outfile << "<table border=\"1\">";
        outfile << "   <tr>\n";
        outfile << "       <td>Title</td>\n";
        outfile << "       <td>Description</td>\n";
        outfile << "       <td>Date</td>\n";
        outfile << "       <td>Time</td>\n";
        outfile << "       <td>People</td>\n";
        outfile << "       <td>Link</td>\n";
        outfile << "   </tr>\n";
        for (auto event : this->events)
        {
            outfile << "   <tr>\n";
            outfile << "       <td>" << event.getTitle() << "</td>\n";
            outfile << "       <td>" << event.getDescription() << "</td>\n";
            outfile << "       <td>" << event.getDate() << "</td>\n";
            outfile << "       <td>" << event.getTime() << "</td>\n";
            outfile << "       <td>" << event.getPeople() << "</td>\n";
            outfile << "       <td><a href=\"" << event.getLink() << "\">Link</a></td>\n";
            outfile << "   </tr>\n";
        }
        outfile << "</table>\n";
        outfile << "</body>\n";
        outfile << "</html>\n";
        outfile.close();
    }
    else {
        std::cout << "Unable to open file for writing!" << std::endl;
    }
}

void HTMLRepo::open_link() {
    std::wstring wideFileName(file_name[0], file_name[strlen(file_name) - 1]);
    LPCWSTR helpFile = wideFileName.c_str();
    ShellExecute(NULL, L"open", helpFile, NULL, NULL, SW_SHOWNORMAL);
}
