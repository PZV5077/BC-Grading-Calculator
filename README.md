# BC Grading Calculator - README

## Overview

The **BC Grading Calculator** is a C++ application designed to assist students in calculating and analyzing their academic performance. The program allows the user to load course information from text files, calculate various scores, and display the results in a structured and readable format. The software features a simple menu for interaction and provides options to load data, analyze grades, and output the analysis.

This application is powered by **Eric Zhang** and is currently at version **a0.0.1**.

## Features

- **Read Data from Files**: The program loads data from `info.txt` and `database.txt` files. It extracts student information (name, grade, class) and course scores.
- **Score Analysis**: It calculates GPA based on the student's scores using a specific grading scale.
- **Output Results**: The program outputs an unofficial transcript, including individual scores and GPA.
- **Menu Navigation**: The program features an interactive menu to select various options (read data, analyze scores, view results, exit).
- **Console Styling**: The application customizes the Windows console window's appearance (size, color, position) for a better user experience.

## Requirements

- **Operating System**: Windows (uses Windows-specific system calls such as `system("color")` and `system("title")`)
- **Compiler**: A C++ compiler supporting C++11 or later
- **Libraries**: Standard C++ libraries (`iostream`, `fstream`, `vector`, etc.)

## File Structure

- **info.txt**: Contains student-specific data, such as name, grade, class, and course scores.
- **database.txt**: Contains a list of courses with IDs and names used for mapping to the scores in `info.txt`.

## Usage Instructions

1. **Download** the project files to your local machine.
2. **Prepare `info.txt`**: The file should contain the following sections:
   - `[name]`: Student's full name.
   - `[grade]`: Student's grade (e.g., "Junior").
   - `[class]`: Class/section the student belongs to.
   - `[score]`: Scores for each course in the format `CourseID S1_score S2_score`.
   
3. **Prepare `database.txt`**: The file should contain a list of courses in the format:
   ```
   CourseID "Course Name"
   ```

4. **Build and Run** the program using your C++ compiler.

5. **Interactive Menu**:
   - **Option A**: Load and read data from `info.txt`.
   - **Option B**: Analyze the data and calculate average scores and GPAs.
   - **Option C**: Output the analysis results in a formatted transcript.
   - **Option D**: Exit the program.

### Example Workflow

- **Step 1**: Launch the program. The console will display the main menu.
- **Step 2**: Select **Option A** to load the data from the `info.txt` file.
- **Step 3**: Select **Option B** to analyze the loaded scores.
- **Step 4**: Select **Option C** to print the unofficial transcript with GPA calculations.
- **Step 5**: Select **Option D** to exit the program.

## Functions

- **init()**: Initializes the console settings (title, size, color, position).
- **centrized_text()**: Outputs text centered on the screen.
- **displayMenu()**: Displays the interactive menu options.
- **read_score()**: Reads the course and student data from `info.txt` and `database.txt` files.
- **print_score()**: Outputs the formatted scores for each course.
- **calculate_gpa()**: Converts numerical scores into GPA values based on predefined thresholds.

## Sample Output

After running the analysis, the application will output a formatted transcript like this:

```
BC Grading Calculator, Ver a0.0.1
Powered by Eric Zhang
-----------------------------------------
          UNOFFICIAL TRANSCRIPT
-----------------------------------------
Name: John Doe
Grade: Senior
Class: A
-----------------------------------------
No.     Name              S1    S2    FINAL
-----------------------------------------
12345   Calculus         85.00 90.00 87.50
67890   Physics          80.00 85.00 82.50
-----------------------------------------
S1 Average:         82.50% | S1 GPA: 3.0
S2 Average:         87.50% | S2 GPA: 3.7
Final Average:      85.00% | FL GPA: 3.5
-----------------------------------------
```

## Contribution

Contributions to the project are welcome! Feel free to fork the repository, submit pull requests, or open issues for any bugs or feature requests.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.

