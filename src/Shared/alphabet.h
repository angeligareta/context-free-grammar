#pragma once

#include <set>
#include <iostream>

using namespace std;

class Alphabet{
   
   friend ostream &operator<<(ostream&,const Alphabet&);
   
   private:
   
   set<char> alphabet_;
   
   public:
   
   Alphabet();
   
   ~Alphabet();
   
   set<char> get_alphabet() const;
   
   int get_size() const;
   
   bool it_belongs(const char&) const;
   
   bool it_belongs(const set<char>&) const;
   
   bool is_empty() const;
   
   void erase(const char& symbol_in);
   
   void Clear();
   
   void InsertSymbol(const char&);
   
   void EraseSymbol(const char&);
   
};