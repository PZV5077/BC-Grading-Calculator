#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <string.h>
#include <Windows.h>
using namespace std;  

int detect_width()
{
    struct winsize size;
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);
    return size.ws_col;
    //return static_cast <int> (system("stty size | awk '{print $2}'"));
}

//Initialize the windows
void init()
{
    // set the title bar of the console

    //set the color of the console
    cout << "color 1F";
    //clear the console
    system("clear");    
}


void centrized_text(string text)
{
    int width = detect_width();
    int text_length = text.length();
    // The below line is used to test the length of the string
    // cout << text_length << endl;

    int space_length = (width - text_length)/2;

    // The below line is used to test the length of the space
    // cout << space_length << endl;

    for(int i = 0; i < space_length; i++)
    {
        cout << " ";
    }
    cout << text << endl;
}

int main()    
{    
    init();
    string text="Hello ddwdwdwdwdwdwdw wddwdwdwada Ms. Gao!";
    centrized_text(text);
    return 0;    
}

