#include "no_terminal.h"

ostream& operator<<(ostream& output, const NoTerminal& no_terminal_in){
    output << no_terminal_in.get_identifier() << " -> ";
    
    set<Production>::iterator it=no_terminal_in.set_production_.begin();
    
    while(it!=no_terminal_in.set_production_.end()){
        output << *it;
        ++it;
        if(it!=no_terminal_in.set_production_.end())
            output << " | ";
    }
            
    return output;
}

NoTerminal::NoTerminal(const char& identifier_in):
identifier_(identifier_in),
initial_(0)
{   
    //cout << "NAZCO "<< identifier_ << endl;
    assert(isupper(identifier_));
}
   
NoTerminal::~NoTerminal()
{  
    //cout << "MUERO "<< identifier_ << endl;
    set_production_.clear(); 
}

char NoTerminal::get_identifier() const
{
    return identifier_;
}
   
set<Production> NoTerminal::get_set_production() const
{
    return set_production_;
}
   
bool NoTerminal::is_initial() const
{
    return initial_;
}
   
bool NoTerminal::is_final() const
{
    for(set<Production>::iterator it=set_production_.begin(); it!=set_production_.end();++it)
        if((*it).has_epsilon_symbol() || (*it).has_only_terminal_symbols())
            return 1;
    return 0;
}
   
void NoTerminal::set_identifier(const char& identifier_in)
{
    identifier_=identifier_in;        
}

void NoTerminal::set_initial(const bool& initial_in)
{
    initial_=initial_in;
}

void NoTerminal::set_production(const Production& production_in)
{
    set_production_.insert(production_in);
}

void NoTerminal::RemoveSymbolFromProductions(const char& symbol_to_remove)
{
    set<Production> set_production=set_production_;
    
    for(set<Production>::iterator it=set_production_.begin(); it!=set_production_.end();++it){
        string string_original=(*it).get_set_symbol();
        bool error=0;
        for (int i=0;i<string_original.size();i++)
            if(string_original[i]==symbol_to_remove)
                error=1;
        if(error==1) 
            set_production.erase(*it);
    }
    
    set_production_=set_production;
}

NoTerminal& NoTerminal::operator=(const NoTerminal& no_terminal_in)
{
    this->identifier_= no_terminal_in.identifier_;
    this->initial_= no_terminal_in.initial_;
    this->set_production_= no_terminal_in.set_production_;
    return *this;
}

int NoTerminal::operator==(const NoTerminal& no_terminal_in) const
{
    if( this->identifier_ != no_terminal_in.identifier_) return 0;
    if( this->initial_ != no_terminal_in.initial_) return 0;
    if( this->set_production_!= no_terminal_in.set_production_) return 0;
    return 1;
}

int NoTerminal::operator<(const NoTerminal& no_terminal_in) const
{    
    if (this->identifier_ < no_terminal_in.identifier_) return 1;
    return 0;
    
    /*if( this->initial_ != no_terminal_in.initial_){
        if (this->identifier_ < no_terminal_in.identifier_) 
            return 1;
        else
            return 0;
    }
        if( this->initial_ == true) return 1;
    
    return 0;*/
    
    /*if( this->initial_ | no_terminal_in.initial_ ){
        if (this->initial_ == 1) 
            return 1;
        else 
            return 0;
    }
    else{
        if (this->identifier_ < no_terminal_in.identifier_) 
            return 1;
        else 
            return 0;
    }
    */
}