#include <list>

#include "opnum.h"
#include "token.h"

using namespace std;

void line_parse(std::list<Token> & postfix, int * ret)
{
   char * opnum = get_opnum(ret);
   if (*ret) {
      string str = opnum; 
      Token nt (str, *ret);
      cout << nt << endl;
      postfix.push_back(nt);
   }
}

int main(int argc, char ** argv)
{
   int retval;

   std::list<Token> opnumList; 

   set_input(argc, argv);

   do {
      line_parse(opnumList, &retval);
   } while (retval > SYM_NULL);

   cout << "Postfix list: " << endl << opnumList <<endl;

   return 0;
}

