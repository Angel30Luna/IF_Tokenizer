#include <string>
#include <iostream>
#include "ifinterpreter.h"
using namespace std;

const string FILENAME = "if2.html";

int main()
{
  IFInterpreter* interpreter = new IFInterpreter(FILENAME);
  interpreter->play();

  delete interpreter;
  return 0;
}