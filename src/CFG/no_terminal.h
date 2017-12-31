#pragma once

#include "production.h"

#include <set>
#include <iostream>

using namespace std;

class NoTerminal{

   friend ostream &operator<<(ostream&, const NoTerminal&);
   
   private:
   
   char identifier_; /**< Simbolo identificador. */
   bool initial_; /** Si es incial. */
   set<Production> set_production_; /** Conjunto de producciones. */
   
   public:
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details    Constructor al que le paso el identificador de entrada.
*/   
   
   NoTerminal(const char&);

/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details    Destructor. Limpia el identificador, el inicial y el set de producciones.
*/

   ~NoTerminal();
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details       Devuelve el identificador del Símbolo No Terminal.
*/

   char get_identifier() const;
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details       Devuelve el conjunto de producciones del Símbolo No Terminal.
*/

   set<Production> get_set_production() const;
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details       Devuelve si el Símbolo No Terminal es inicial.
*/

   bool is_initial() const;
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details       Devuelve si el Símbolo No Terminal es final.
*/

   bool is_final() const;
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details       Función que asigna un nuevo identificador al No Terminal.
*/

   void set_identifier(const char&);
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details       Función que asigna si es inicial el No Terminal.
*/

   void set_initial(const bool&);
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details       Función que asigna una nueva produccion al No Terminal.
*/

   void set_production(const Production&);
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details       Función sobrecargada con el operador igual.
*/

   NoTerminal& operator=(const NoTerminal&);
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details       Función sobrecargada con el operador igual==
*/

   int operator==(const NoTerminal&) const;
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	\details       Función sobrecargada con el operador <
*/

   int operator<(const NoTerminal&) const;
   
/**
      \author   	Angel Luis Igareta Herráiz(angeliton@hotmail.es)
      \date 		22 de octubre de 2016

	   \details       Elimina el Símbolo que le pasamos de todas las producciones
*/

   void RemoveSymbolFromProductions(const char&);
   
};