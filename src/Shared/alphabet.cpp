#include "alphabet.h"

Alphabet::Alphabet()
{
}

Alphabet::~Alphabet()
{
    Clear();
}

set<char> Alphabet::get_alphabet() const
{
    return alphabet_;
}

int Alphabet::get_size() const
{
    return alphabet_.size();
}

bool Alphabet::it_belongs(const char& symbol_in) const
{
    
    for(set<char>::iterator it=alphabet_.begin();it!=alphabet_.end();++it)
        if(*it==symbol_in)
            return true;
    
    return false;
}

bool Alphabet::it_belongs(const set<char>& set_symbol_in) const
{
    set<char> alphabet = set_symbol_in;
    
    for(set<char>::iterator it=set_symbol_in.begin();it!=set_symbol_in.end();++it)
        for(set<char>::iterator it2=alphabet_.begin();it2!=alphabet_.end();++it2)
            if(*it==*it2)
                alphabet.erase(*it);

    return alphabet.empty();
}

bool Alphabet::is_empty() const
{
    return alphabet_.empty();
}

void Alphabet::erase(const char& symbol_in)
{
    alphabet_.erase(symbol_in);
}

void Alphabet::Clear()
{
    alphabet_.clear();
}

void Alphabet::InsertSymbol(const char& symbol_in)
{
    alphabet_.insert(symbol_in);
}

void Alphabet::EraseSymbol(const char& symbol_in)
{
    alphabet_.erase(symbol_in);    
}

ostream &operator<<(ostream& output,const Alphabet& alphabet)
{
    
    for(set<char>::iterator it=alphabet.alphabet_.begin();it!=alphabet.alphabet_.end();++it)
        output << *it << " ";
        
    return output;
}

