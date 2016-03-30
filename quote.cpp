/**************************************************************************
FILE          : quote.cpp
PROGRAMMER    : Peter C. Chapin
LAST REVISION : December 2001

(C) Copyright 2001 by Peter C. Chapin

This file contains a program that quotes text files as described in the associated file
EXAMPLE-01.txt and outlined in the p-code file quote.pcd.

Please send comments or bug reports to

     Peter C. Chapin
     Computer Information Systems
     Vermont Technical College
     Williston, VT 05495
     PChapin@vtc.vsc.edu
**************************************************************************/

#include <fstream>
#include <iostream>
#include <string>

//
// This function returns true of the given line contains only white space. If there is a "word"
// on that line, it will return false.
//
bool is_blank(const std::string &line)
{
    // Empty lines are blank.
    if (line.length() == 0) return true;

    // Lines containing only spaces, tabs, formfeeds, carriage returns, and new lines are also
    // blank. Here I see if there is even one character in the line that is not one of those
    // that I mentioned.
    //
    if (line.find_first_not_of(" \t\f\r\n", 0) == std::string::npos)
        return true;

    return false;
}


//
// This function takes the next white space delimited word out of line. It modifes line to
// delete the word and returns the word in "word". It returns true if it found a word and false
// otherwise.
//
bool get_next_word(std::string &line, std::string &word)
{
    // Find the first non white space character.
    int non_white = line.find_first_not_of(" \t\f\r\n", 0);

    // If there wasn't any, we have no word.
    if (non_white == std::string::npos) return false;

    // Otherwise locate the next white space. It is possible that this will return
    // std::string::npos if this is the last word on the line. That shouldn't cause a problem
    // with what follows since excessive values will be taken as "all" in these contexts. (The
    // npos value is the highest possible string index).
    //
    int white = line.find_first_of(" \t\f\r\n", non_white + 1); 
  
    word = line.substr(non_white, white - non_white);
    line.erase(0, white);
    return true;
}


//
// Main Program
//

int main(int argc, char **argv)
{
    // Good to include a usage message if necessary.
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " filename\n";
        return 1;
    }

    // Get the file names.
    std::string input_name = argv[1];
    std::string output_name = input_name;
    output_name += ".q";

    // Open the files.
    std::ifstream input_file(input_name.c_str());
    if (!input_file) {
        std::cerr << "Can't open " << input_name << " for reading.\n";
        return 1;
    }
    std::ofstream output_file(output_name.c_str());
    if (!output_file) {
        std::cerr << "Can't open " << output_name << " for writing.\n";
        return 1;
    }

    // Initialize.
    std::string input_line;
    std::string output_line = ">";

    // Read the input file a line at a time.
    while (getline(input_file, input_line)) {

        // If this is a blank like handle it. This might involve outputing a partially filled
        // output line.
        //
        if (is_blank(input_line)) {
            if (output_line.length() > 2) {
                output_file << output_line << "\n";
                output_line = ">";
            }
            output_file << ">\n";
        }

        // Otherwise the line is not blank and needs to be broken down by words.
        else {
            std::string word;
            while (get_next_word(input_line, word)) {
                if (output_line.length() + word.length() + 1 > 76) {
                    output_file << output_line << "\n";
                    output_line = ">";
                }
                output_line += ' ';
                output_line += word;
            }
        }
    }

    // If there is a partially filled line at the end, output that too.
    if (output_line.length() > 2) {
        output_file << output_line << "\n";
    }

    return 0;
}
