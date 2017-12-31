#pragma once

#include "../Shared/alphabet.h"
#include "../CFG/no_terminal.h"
#include "../CFG/production.h"

#include <iostream>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

class Cfg{
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details    Muestra el CFG en el ostream.
*/   

   friend ostream &operator<<(ostream&, const Cfg&);

/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details    Lee el CFG del istream.
*/  

   friend istream& operator>>(istream&, Cfg&);
   
   private:
   
   set<NoTerminal> set_no_terminal_; /**< Conjunto de simbolos no terminales*/
   Alphabet set_terminal_; /**< Conjunto de simbolos terminales*/
   
   public:
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details       Constructor por defecto.
*/

   Cfg();
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details       Destructor por defecto. Limpia los conjuntos de simbolos no terminales y terminales.
*/

   ~Cfg();
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details    Destructor por defecto. Limpia los conjuntos de simbolos no terminales y terminales.
	   
	   * @param  	Devuelve si esta vacío o no el CFG.
*/   
   
   bool is_empty() const;
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details    Simplifica el CFG. Elimina los simbolos y producciones inútiles. Si le pasamos un 1 podemos ver el proceso.
*/   
   
   void Simplify(const bool&);
   
   private:
   
   void Clear();
   
   void SwapNoTerminal(const NoTerminal& , const NoTerminal&);
   
   void ShowNoTerminalDivision(const set<char>&) const;
   
   set<char> SetIntersectionDivision(const set<char>&, const set<char>&) const;
   
   set<char> SetDifferenceDivision(const set<char>&, const set<char>&) const;
   
   set<char> SetUnionDivision(const set<char>&, const set<char>&) const;
   
   void RemoveSymbolFromCfg(const set<char>&);
   
   char GetNoTerminalInitial() const;
   
   NoTerminal GetNoTerminalWithId(const char&) const;
   
};