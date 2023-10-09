#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;  


const int numOptions = 4;
const string options[numOptions] = {"A. Read info.txt ", "B. Analyse File", "C. Output Analyse Result", "D. Exit"};
const int MAX_LINES = 100;
//Variables for storing the score
vector<vector<string>> f_score;
double s_score[MAX_LINES][4];
//Variables for storing the information
string s_name;
string s_grade;

string s_class;
//Initialize the windows
void init()
{
    // set the title bar of the console
    system("title BC Grading Calculator, Ver a0.0.1");

    //set the size of the console
    system("mode con cols=100 lines=30");

    //set the colour of the console
    system("color 1f");

    //set the position of the console to the centre of the screen
    system("powershell (New-Object -ComObject Shell.Application).TileHorizontally()");

    //clear the console
    system("cls"); 
}

//detect the width of the console in Windows and output a centrized text in the console
void centrized_text(string text)
{
    //get the width of the console
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    //get the length of the text
    int length = text.length();
    //calculate the number of spaces needed
    int space = (width - length) / 2;
    //output the spaces
    for (int i = 0; i < space; i++)
    {
        cout << " ";
    }
    //output the text
    cout << text << endl;
}

//Function to display menu options
void displayMenu(int currentOption) {
    system("cls"); // clear the console screen
    cout<<"BC Grading Calculator, Ver a0.0.1"<<endl;
    cout<<"Powered by Eric Zhang"<<endl;
    cout<<"----------------------------------------"<<endl;
    cout << "Select an option:" << endl << endl;
    for (int i = 0; i < numOptions; i++) {
        if (i == currentOption) {
            cout << "> ";
        }
        else {
            cout << "  ";
        }
        cout << options[i] << endl;
    }
}

void print_score(vector<vector<string>> f_score, int max_course_name_length);  // function prototype

void read_score() {
    ifstream fin("info.txt");
    ifstream db("database.txt");
    string line = "";
    int line_count = 0;

    // Read info.txt
    while (getline(fin, line)) {
        if (line == "[name]") {
            getline(fin, s_name);
        } else if (line == "[grade]") {
            getline(fin, s_grade);
        } else if (line == "[class]") {
            getline(fin, s_class);
        } else if (line == "[score]") {
            while (getline(fin, line) && line_count < MAX_LINES) {
                int i = 0;
                string token;
                size_t pos;
                while ((pos = line.find(" ")) != string::npos) {
                    token = line.substr(0, pos);
                    line.erase(0, pos + 1);
                    s_score[line_count][i] = stof(token);
                    i++;
                }
                s_score[line_count][i] = stof(line);
                line_count++;
            }
        }
    }
    //get the average of [i][1] and [i][2], store it in [i][3]
    for (int i = 0; i < line_count; i++) {
        s_score[i][3] = (s_score[i][1] + s_score[i][2]) / 2;
    }

    // Read database.txt
    vector<pair<string, string>> courses;
    int max_course_name_length = 0;
    while (getline(db, line)) {
        size_t pos = line.find(" ");
        string course_id_str = line.substr(0, pos);
        string course_name = line.substr(pos + 2);
        course_name.erase(course_name.length() - 1, 1);  // remove the trailing double quote
        courses.push_back(make_pair(course_id_str, course_name));
        if (course_name.length() > max_course_name_length) {
            max_course_name_length = course_name.length();
        }
    }

    // Create f_score
    for (int i = 0; i < line_count; i++) {
        string course_id_str = to_string(static_cast<int>(s_score[i][0]));
        string real_name;
        for (auto& course : courses) {
            if (course.first == course_id_str) {
                real_name = course.second;
                break;
            }
        }
        vector<string> row;
        row.push_back(course_id_str);
        row.push_back(real_name);
        for (int j = 1; j < 4; j++) {
            string score_str;
            if (s_score[i][j] == static_cast<int>(s_score[i][j])) {
                // If the score has no decimal places, append ".00"
                score_str = to_string(static_cast<int>(s_score[i][j])) + ".00";
            } else {
                // Otherwise, output the score with two decimal places
                score_str = to_string(s_score[i][j]);
                size_t dot_pos = score_str.find(".");
                if (dot_pos != string::npos && dot_pos + 3 <= score_str.length()) {
                    score_str = score_str.substr(0, dot_pos + 3);
                } else {
                    score_str = score_str.substr(0, dot_pos + 2) + "0";
                }
            }
            row.push_back(score_str);
        }
        f_score.push_back(row);
    }
}

void print_score(vector<vector<string>> f_score, int max_course_name_length) {
    // Print f_score
    cout << fixed << setprecision(2);  // set output to fixed-point with 2 decimal places
    for (auto& row : f_score) {
        cout << row[0];
        if (row[0].size() == 5) {
            cout << "   ";  // add two spaces after 5-digit course code
        } else if (row[0].size() == 6) {
            cout << "  ";  // add one space after 6-digit course code
        } else if (row[0].size() == 7) {
            cout << " ";  // add one space after 7-digit course code
        }

        // Add spaces to course name to match the length of the longest name
        int padding_spaces = max_course_name_length - row[1].length() + 1;
        cout << row[1];
        for (int i = 0; i < padding_spaces; i++) {
            cout << " ";
        }

        for (int i = 2; i < row.size(); i++) {
            cout << row[i] << " ";
        }
        cout << "\n";
    }
}

double calculate_gpa(double score) {
    if (score >= 86) {
        return 4.0;
    } else if (score >= 80) {
        return 3.7;
    } else if (score >= 76) {
        return 3.3;
    } else if (score >= 72) {
        return 3.0;
    } else if (score >= 68) {
        return 2.7;
    } else if (score >= 64) {
        return 2.3;
    } else if (score >= 60) {
        return 2.0;
    } else if (score >= 55) {
        return 1.7;
    } else if (score >= 50) {
        return 1.7;
    } else {
        return 0.0;
    }
}

int main()    
{    
    init();

    int currentOption = 0;
    
    while (true) {
        displayMenu(currentOption);
        
        // Wait for user input
        int input = getch();
        
        // Handle user input
        if (input == 224) { // arrow key
            input = getch(); // get second byte of arrow key input
            if (input == 72 && currentOption > 0) { // up arrow
                currentOption--;
            }
            else if (input == 80 && currentOption < numOptions - 1) { // down arrow
                currentOption++;
            }
        }
        else if (input == 13) { // enter key
            // Handle selected option
            system("cls"); // clear the console screen
            if (options[currentOption]=="A. Read info.txt ")
            {
                system("cls"); // clear the console screen
                cout<<"Reading info.txt..."<<endl;
                //_sleep(1*1000);
                read_score();
                cout<<"Done!"<<endl;
                system("pause");
            }
            else if (options[currentOption]=="B. Analyse File")
            {
                system("cls"); // clear the console screen
                cout<<"Analysing..."<<endl;
                //_sleep(0.5*1000);
                cout<<"Done!"<<endl;
                system("pause");
                // Print Analyse Result
                system("cls"); // clear the console screen
                int max_course_name_length = 0;
                for (auto& row : f_score) {
                    if (row[1].length() > max_course_name_length) {
                     max_course_name_length = row[1].length();
                    }
                }

                double s1avg = 0;
                double s2avg = 0;
                double finalavg = 0;
                for (auto& row : f_score) {
                    s1avg += stof(row[2]);
                    s2avg += stof(row[3]);
                    finalavg += stof(row[4]);
                }
                s1avg /= f_score.size();
                s2avg /= f_score.size();
                finalavg /= f_score.size();
                double s1gpa=calculate_gpa(s1avg);
                double s2gpa=calculate_gpa(s2avg);
                double finalgpa=calculate_gpa(finalavg);
                // Print Analyse Result
                cout << "BC Grading Calculator, Ver a0.0.1" <<endl;
                cout << "Powered by Eric Zhang" <<endl;
                cout << "-----------------------------------------" <<endl;
                cout << "          UNOFFICIAL TRANSCRIPT" <<endl;
                cout << "-----------------------------------------" <<endl;
                cout << "Name: " << s_name << endl;
                cout << "Grade: " << s_grade << endl;
                cout << "Class: " << s_class << endl;
                cout << "-----------------------------------------" <<endl;
                cout << "No.     Name";
                for(int i=0, j=1; i<max_course_name_length-3; i++)
                {
                    cout << " ";
                }
                cout << "S1    S2    FINAL "<<endl;
                print_score(f_score, max_course_name_length);
                cout << "-----------------------------------------" <<endl;
                cout << "S1 Average:         " << s1avg << "%" << " " << "|" << " " << "S1 GPA: " << s1gpa <<endl;
                cout << "S2 Average:         " << s2avg << "%" << " " << "|" << " " << "S2 GPA: " << s2gpa <<endl;
                cout << "Final Average:      " << finalavg << "%" << " " << "|" << " " << "FL GPA: " << s1gpa <<endl;
                cout << "-----------------------------------------" <<endl;
                system("pause");

            }
            else if (options[currentOption]=="C. Output Analyse Result")
            {
                cout<<"You selected C"<<endl;
            }
            else if (options[currentOption]=="D. Exit")
            {
                break;
            }
            currentOption = 0; // reset menu to initial state
        }else if (input == 27) { // escape key
            // Exit the program
            break;
        }
    }
    
    return 0;
}