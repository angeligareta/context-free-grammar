#pragma once

#include <iostream>
#include <set>
#include <string>
#include <cctype>
#include <cassert>

using namespace std;

class Production{

   friend ostream &operator<<(ostream&, const Production&);
   
   private:
   
   string set_symbol_;
   int num_terminal_;
   int num_no_terminal_;
   bool epsilon_symbol_;
   
   public:
   
   Production(const string&);
   
   Production(const char* string_in);
   
   ~Production();
   
   string get_set_symbol() const;
   
   int get_num_terminal() const;
   
   set<char> get_set_no_terminal() const;
   
   int get_num_no_terminal() const;
   
   set<char> get_set_terminal() const;
   
   bool has_only_terminal_symbols() const;
   
   bool has_epsilon_symbol() const;
   
   void set_set_symbol_(const string&);
   
   Production& operator=(const Production&);

   int operator==(const Production&) const;

   int operator<(const Production&) const;
   
   private:
   
   void Update();
   
};