#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <tchar.h>
#include <string>


int ReadData(char *buffer, unsigned int nbChar);

void MoveCursorWithKeyboard(char& c)
{
    POINT p;
    GetCursorPos(&p);
    // Use whatever method you need to get the keys
    // getch is just a function that gets the arrow keys so i use it here
    c = getch();
    if(c == 'd') // Right Arrow Key
        p.x += 100;  // Move Cursor Right
    if(c == 'a') // Left Arrow Key
        p.x -= 100;  // Move Cursor Left
    if(c == 's') // Up Arrow Key
        p.y += 100;  // Move Cursor Up
    if(c == 'w') // Down Arrow KEy
        p.y -= 100;  // Move Cursor Down
 
    SetCursorPos(p.x,p.y);
}

int main()
{
    char c;
    while(c != 'q')
    {
				//SerialPort serial;
				//serial.connect("/COM7");
				
        MoveCursorWithKeyboard(c);
	  }
    return 0;
}