#include <iostream>
#include <fstream>

using namespace std;

int main ()
{
    char* str = NULL;
    char* tokens =(char*)(" ,.-@");
    char * pch;
    int test_case =0;

    string line;
    int lineCounter =0;
    ifstream myfile ("Tokenizer_Sample_Input.txt");
    if (myfile.is_open())
    {
      while (! myfile.eof() )
      {
        getline (myfile,line);
        if (line.length() > 0) {
          str = (char*)line.c_str();
          cout << "Splitting string: " << str << " into tokens:" << tokens << endl;
          pch = strtok (str,tokens);
          while (pch != NULL)
          {
            cout << pch <<endl;
            pch = strtok (NULL, tokens);
          }
        }
      }
      myfile.close();
    }
    return 0;
}