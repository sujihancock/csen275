// Recusion example
// examples of cout and cin
#include <iostream>
#include <ncurses.h> // Mac users can use <ncurses.h>
using namespace std;

long fact(int n) 
{ 
    if (n==0)
        return 1;
    return (n*fact(n-1)); // recurssive function call
}

int main()
{
    int num;

    cout << "Enter a positive number: ";
    cin >> num;

    cout << "Factorial of number " << num << " is " << fact(num) << endl; // cascading cout, many << operators

    //getch();  // We can also use cin.get(), then we don't need to include <conio.h>
    return 0;
}