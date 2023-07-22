#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>  // for setprecision and fixed

using namespace std;

const int MAX_LINES = 100;

vector<vector<string>> f_score;
float s_score[MAX_LINES][4];

string s_name;
string s_grade;
string s_class;

void print_score(vector<vector<string>> f_score, int max_course_name_length);  // function prototype

void read_score() {
    ifstream fin("info.txt");
    ifstream db("database.txt");
    string line;
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
    cout << "Name: " << s_name << endl;
    cout << "Grade: " << s_grade << endl;
    cout << "Class: " << s_class << endl; 
    print_score(f_score, max_course_name_length);
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

int main() {
    
    read_score();
   
    return 0;
}