#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <cmath>

// Libraries for progress bar
#include <chrono>
#include <thread>

// Libraries for PDF processing
#include "pdfparser/PDFParser.h"

using namespace std;

int main(int argc, char* argv[]) {

    // Colors
    string Red = "\033[;31;m";
    string White = "\033[;37;m";
    string Green = "\033[;32;m";
    string Line_below_text = "\033[;4;m";
    string Line_not_below_text = "\033[;0;m";

    // Check if the command-line arguments are correct
    if (argc < 2) {
        cerr << Red << "Error!: " << Line_below_text << "Invalid command-line arguments" << Line_not_below_text << endl;
        cerr << endl << White << "Use: " << Green << Line_below_text << "pdf_to_txt 'Your file pdf'" << Line_not_below_text << endl;
        return 1;
    }

    // Import File PDF
    string Local_file = argv[1];
    if (Local_file.substr(Local_file.size()-4) != ".pdf") {
        cerr << Red << "Error!: " << Line_below_text << "Invalid file format" << Line_not_below_text << endl;
        cerr << endl << White << "Use: " << Green << Line_below_text << "pdf_to_txt 'Your file pdf'" << Line_not_below_text << endl;
        return 1;
    }

    // Extract the file name for file.txt
    string save_as;
    if (Local_file.find('/') != string::npos) {
        save_as = Local_file.substr(Local_file.find_last_of('/') + 1, Local_file.find_last_of('.') - Local_file.find_last_of('/') - 1) + ".txt";
    }
    else {
        save_as = Local_file.substr(0, Local_file.size() - 4) + ".txt";
    }

    // Convert coordination to file.txt
    try {
        PDF::Parser parser(Local_file);
        parser.parse();

        ofstream file_txt(save_as.c_str());

        int num_all_pages = parser.getNumPages();
        for (int num_page = 0; num_page < num_all_pages; num_page++) {
            file_txt << parser.getPage(num_page)->getText() << endl;
        }
        file_txt.close();
    }
    catch (exception& e) {
        cerr << Red << "Error!: " << Line_below_text << e.what() << Line_not_below_text << endl;
        return 1;
    }

    return 0;
}
