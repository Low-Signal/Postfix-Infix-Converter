#include <list>
#include <iostream>

#include "opnum.h"
#include "token.h"
#include "bet.h"

using namespace std;


/* This function uses the interface from opnum.h.
 * It extracts tokens from one line of input, and inserts 
 * them to a list.  If there are some incorrect token, 
 * it reports the total number accordingly. */
int get_postfix(std::list<Token> & postfix, int * ret)
{
   int num = 0;
   int retval = 0;
   do {
      char * opnum = get_opnum(&retval);
      if (retval) {
         string str = opnum; 
         Token nt (str, retval);

         if (retval >= SYM_INVAL) {
            cout<< opnum << endl; 
            num ++;
         } else if (retval < SYM_ENDLN) {
            postfix.push_back(nt);
         }
      }
   } while (retval > SYM_NULL && retval != SYM_ENDLN);

   *ret = retval;

   return num;
}


int main(int argc, char ** argv)
{
   int ret = 0;
   std::list<Token> postfix; 

   set_input(argc, argv);

   do {
      int num = get_postfix(postfix, &ret);
      if (num) {
         cout << num << " incorrect tokens found. "<<endl << postfix <<endl;  
         postfix.clear();
         break;
      }

      if (!postfix.empty()) {

         BET<Token> bet;
   
	 bool correct = bet.buildFromPostfix(postfix);

	 if (!correct) {
	    cout << "Incorrect construction from postfix ...\n" << endl;
	 } else if (!bet.empty()) {
            cout << "Postfix expression: ";
            bet.printPostfixExpression();

            cout << "Infix expression: ";
            bet.printInfixExpression();

            cout << "Number of nodes: ";
            cout << bet.size() << endl;

            cout << "Number of leaf nodes: ";
            cout << bet.leaf_nodes() << endl;

            //test copy constructor
            BET<Token> bet2(bet);
            cout << "Testing copy constructor: ";
            bet2.printInfixExpression();
           
            //test assignment operator
            BET<Token> bet3;
            bet3 = bet;
            cout << "Testing assignment operator: ";
            bet3.printInfixExpression();
         }
         cout << "Terminating one line ... ...\n" << endl;
         postfix.clear();
      }
   } while (ret > SYM_NULL);

   return 0;
}
