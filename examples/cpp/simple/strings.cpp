#include <iostream>
#include <string>
#include <cstring>
using namespace std;


int main(int argc, char **argv)
{
    /* Unlike C (but like Java), C++ has a "string" class to conveniently
       manipulate strings (although you can still manipulate them as
       null-terminated character arrays if you want */

    string s = "Hello, world!";

    /* We can print strings with the iostream library */    
    cout << s << endl;

    /* We can read strings from standard input */
    string name;
    cout << "Enter your first name: ";
    cin >> name;
    cout << "Hello, " << name << "!" << endl;
    
    /* However, if we want to read a string with whitespace in it, we need
       to use the getline() function */
    cout << "Enter your full name: ";
    cin.ignore(); // Needed to clear the remaining '\n' from "cin >> name"
    getline(cin, name);
    cout << "Hello, " << name << "!" << endl;

    
    /* C++ strings include all the usual goodies you expect with strings */

    /* Concatenation */
    string s1, s2, s3;
    
    s1 = "foo";
    s2 = "bar";
    s3 = s1 + s2;
    
    cout << s3 << endl;

    /* String length */
    cout << "The length of '" << s3 << "' is " << s3.size() << endl;

    /* Substrings */
    cout << s3.substr(2,3) << endl;

    /* Finding a string in a string */
    string subs;

    subs = "oo";
    if (s3.find(subs) == string::npos)
        cout << subs << " is not a substring of " << s3 << endl;
    else
        cout << subs << " is a substring of " << s3 << endl;

    subs = "baz";
    if (s3.find(subs) == string::npos)
        cout << subs << " is not a substring of " << s3 << endl;
    else
        cout << subs << " is a substring of " << s3 << endl;

    /* Comparisons */
    cout << "Enter two words: ";
    cin >> s1 >> s2;
    if(s1 == s2)
        cout << "The two words are the same" << endl;
    else if (s1 < s2)
        cout << s1 << " comes before " << s2 << endl;
    else if (s1 > s2)
        cout << s1 << " comes after " << s2 << endl;

    /* Get a C-style string to use with functions that expect one.*/
    const char *cs;
    cs = s3.c_str();
    cout << "The length of '" << cs << "' is " << strlen(cs) << endl;

    
    return 0;
}

