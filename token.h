#ifndef NTOKEN_H

#define NTOKEN_H

#include <iostream>
#include <iomanip>
#include <sstream>

#include <list>
#include <string>

#include "opnum.h"

using namespace std;

class Token {

   private:
      string t_val; /* the string token */
      int t_cls; /* the type of token */

   public:
      Token ( const string & val = "", int cls = 0 )
        : t_val { val }, t_cls { cls } 
      { }

      Token ( string && val, int cls = 0)
        : t_val { std::move( val ) }, t_cls { cls }
      { }

      string getValue() const { return t_val; }
      int getType () const { return t_cls; }
};

std::ostream & operator<<(std::ostream &os, const Token & a) 
{ 
   os << "[" << a.getType() << "]: " << a.getValue() << "; " ;
   return os;
}

std::ostream & operator<<(std::ostream &os, const list<Token> & a) { 
   auto itr = a.begin();
   while ( itr != a.end() ) {
      if ((*itr).getType() == SYM_ENDLN) {
	 os << endl;
      } else {
	 os << (*itr).getValue() << ' ';
      }
      itr++;
   }
   return os;
}
#endif
