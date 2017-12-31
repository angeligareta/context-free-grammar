#include "production.h"

ostream& operator<<(ostream& output, const Production& production_in)
{
    output << production_in.set_symbol_;
    return output;
}

Production::Production(const string& string_in):
set_symbol_(string_in),
num_no_terminal_(0),
num_terminal_(0),
epsilon_symbol_(0)
{
    Update();    
}

Production::Production(const char* string_in):
set_symbol_(string_in),
num_no_terminal_(0),
num_terminal_(0),
epsilon_symbol_(0)
{
    Update();    
}

Production::~Production(){}
   
string Production::get_set_symbol() const
{
    return set_symbol_;
}
   
int Production::get_num_terminal() const
{
    return num_terminal_;
}

set<char> Production::get_set_no_terminal() const
{
    set<char> set_no_terminal;
    
    for(int i=0;i<set_symbol_.size();i++)
        if(isupper(set_symbol_[i]))
            set_no_terminal.insert(set_symbol_[i]);
    
    return set_no_terminal;
}
   
int Production::get_num_no_terminal() const
{
    return num_no_terminal_;
}

set<char> Production::get_set_terminal() const
{
    set<char> set_terminal;
    
    for(int i=0;i<set_symbol_.size();i++)
        if(!isupper(set_symbol_[i]) && set_symbol_[i]!=' ')
            set_terminal.insert(set_symbol_[i]);
    
    return set_terminal;
}

bool Production::has_only_terminal_symbols() const
{
    return (num_terminal_>0 && num_no_terminal_==0);
}

bool Production::has_epsilon_symbol() const
{
    return epsilon_symbol_;
}

void Production::set_set_symbol_(const string& string_in)
{
    set_symbol_=string_in;
    Update();
}

void Production::Update()
{
    for(int i=0; i<set_symbol_.size();i++){
        if(isupper(set_symbol_[i]))
            ++num_no_terminal_;
        else if (set_symbol_[i]=='~')
            epsilon_symbol_=1;
        else
            ++num_terminal_;
    }
}

Production& Production::operator=(const Production& production_in)
{
    this->set_symbol_= production_in.set_symbol_;
    this->num_terminal_= production_in.num_terminal_;
    this->num_no_terminal_= production_in.num_no_terminal_;
    this->epsilon_symbol_= production_in.epsilon_symbol_;
    return *this;
}

int Production::operator==(const Production& production_in) const
{
    if( this->set_symbol_ == production_in.set_symbol_) return 0;
    return 1;
}

int Production::operator<(const Production& production_in) const
{
    if( this->set_symbol_.length() == production_in.set_symbol_.length()){
        if (this->set_symbol_ < production_in.set_symbol_)
            return 1;
    }        
    else if( this->set_symbol_.length() > production_in.set_symbol_.length()) return 1;
    
    return 0;
}