#include "cfg.h"

ostream& operator<<(ostream& output, const Cfg& cfg_in)
{
    output << cfg_in.set_terminal_.get_size() << endl;
    output << cfg_in.set_terminal_ << endl;
    output << cfg_in.set_no_terminal_.size() << endl;
    
    Cfg cfg_aux = cfg_in;

    cfg_aux.set_no_terminal_.erase(cfg_aux.GetNoTerminalWithId(cfg_aux.GetNoTerminalInitial()));
    
    output << cfg_in.GetNoTerminalInitial() << " ";
    for (set<NoTerminal>::iterator it=cfg_aux.set_no_terminal_.begin(); it!=cfg_aux.set_no_terminal_.end();++it)
        output << (*it).get_identifier() << " ";
        
    output << endl;
    
    output << cfg_in.GetNoTerminalWithId(cfg_in.GetNoTerminalInitial()) << endl;
    for (set<NoTerminal>::iterator it=cfg_aux.set_no_terminal_.begin(); it!=cfg_aux.set_no_terminal_.end();++it)
        output << *it << endl;
    
    return output;
}

istream& operator>>(istream& input, Cfg& cfg_in)
{
    bool error=0;
    
    int terminal_counter;
    input >> terminal_counter;
    
    char symbol;
    
    for (int i=0;i<terminal_counter;i++) {
        input >> ws; //necesitamos esto porque si no cogeria \n y espacios
        input.get(symbol);
        cfg_in.set_terminal_.InsertSymbol(symbol);
    }
     cfg_in.set_terminal_.InsertSymbol('~');
    
    int no_terminal_counter;
    input >> no_terminal_counter;
    
    for (int i = 0; i < no_terminal_counter; ++i) {
        input >> ws;
        input.get(symbol);
        NoTerminal no_terminal(symbol);
        if(i==0)
            no_terminal.set_initial(1);
        cfg_in.set_no_terminal_.insert(no_terminal);
    }
    
    for (int i=0;i<no_terminal_counter;++i) {
        input >> ws;
        input.get(symbol);
        NoTerminal no_terminal(symbol);
        set<NoTerminal>::iterator it=cfg_in.set_no_terminal_.find(no_terminal);
        if((*it).is_initial()) no_terminal.set_initial(1);
        //Comprobamos si hemos declarado el no terminal arriba, en caso contrario salimos
        if(it!=cfg_in.set_no_terminal_.end()) {
            
            char* string_temp=new char;
            
            input >> ws;
            input.get(string_temp,3,' ');
            
            if(strcmp(string_temp,"->")==0) {
                input.getline(string_temp,256);
                
                char *split;
                split = strtok (string_temp," |");
                
                while (split != NULL) {
                    Production production(split);
                    if(!cfg_in.set_terminal_.it_belongs(production.get_set_terminal())) {
                        error=1;
                    }
                    no_terminal.set_production(production);
                    split  = strtok (NULL," |");
                }
            }
            else
                error=1;
        
            cfg_in.SwapNoTerminal(*it,no_terminal);
        
        }
        else
            error=1;    
    }
    
    if(!input.eof()) error=1;   // Salgo si todavia queda cadena de entrada
    
    if(error==1)
        cfg_in.Clear();
    
    return input;
    
}

Cfg::Cfg()
{}
   
Cfg::~Cfg()
{
    Clear();
}

bool Cfg::is_empty() const
{
    return (set_terminal_.is_empty() && set_no_terminal_.empty());
}

void Cfg::Simplify(const bool& show)
{
    set<char> set_terminal_original;
    
    for (set<NoTerminal>::iterator it=set_no_terminal_.begin(); it!=set_no_terminal_.end(); ++it)
        set_terminal_original.insert((*it).get_identifier());
    
    // 1ºEtapa: Elimino no terminales desde las que no se pueda derivar una cadena.
    set<char> set_no_terminal;
    
    for (set<NoTerminal>::iterator it=set_no_terminal_.begin(); it!=set_no_terminal_.end(); ++it)
        if((*it).is_final())
            set_no_terminal.insert((*it).get_identifier());
            
    if(show!=0) {
        cout << "\nPrimera Estapa\nInicialización:" << endl;
        ShowNoTerminalDivision(set_no_terminal);
    }
    
    bool change; int iteration=0;
    
    do{
        change=0;
        for (set<NoTerminal>::iterator it=set_no_terminal_.begin(); it!=set_no_terminal_.end(); ++it)
            if(!(*it).get_set_production().empty())
                for (set<Production>::iterator it2=(*it).get_set_production().begin(); it2!=(*it).get_set_production().end();++it2)
                    //Si todos los no terminales de la produccion estan en set_no_terminal | Si A interseccion B = A | B pertenece a A
                    if(SetIntersectionDivision((*it2).get_set_no_terminal(),set_no_terminal)==(*it2).get_set_no_terminal())
                        if(set_no_terminal.count((*it).get_identifier())==0) { // Si no está ya
                            set_no_terminal.insert((*it).get_identifier());
                            change=1;
                            if(show!=0) {
                                cout << ++iteration << "º iteración:\t" << endl;
                                ShowNoTerminalDivision(set_no_terminal);
                            }
                        }
    }while(change==1);
    
    if(show!=0) {
        cout << "Eliminamos..."; ShowNoTerminalDivision(SetDifferenceDivision(set_terminal_original,set_no_terminal)); cout << endl;
    }
    
    RemoveSymbolFromCfg(SetDifferenceDivision(set_terminal_original,set_no_terminal));
    
    if(show!=0)
        cout << "\nSegunda etapa" << endl;  
    // 2º Etapa: Elimino simbolos que no se puedan derivar partiendo de S.
    set<char> alphabet; iteration=0;
    set_no_terminal.clear(); set_no_terminal.insert(GetNoTerminalInitial());
    queue<char> queue_char; assert(GetNoTerminalInitial() != '\0'); // Si hay estado inicial
    queue_char.push(GetNoTerminalInitial());
    
    while(!queue_char.empty()) {
        NoTerminal no_terminal= GetNoTerminalWithId(queue_char.front());  queue_char.pop();
        set<Production> set_production_aux=no_terminal.get_set_production();
        for (set<Production>::iterator it=set_production_aux.begin(); it!=set_production_aux.end();++it) {
            alphabet=SetUnionDivision(alphabet,(*it).get_set_terminal());
            set<char> set_aux=(*it).get_set_no_terminal(); //?
            for (set<char>::iterator it2=set_aux.begin(); it2!=set_aux.end();++it2)
                if(set_no_terminal.count(*it2)==0) {
                    queue_char.push(*it2);
                    set_no_terminal.insert(*it2);
                    if(show!=0) {
                        cout << ++iteration << "º Cambio:\t" << endl;
                        cout << "V' = "; ShowNoTerminalDivision(set_no_terminal);
                        cout << "Alfabeto = "; ShowNoTerminalDivision(alphabet);
                    }
                }
        }
    }
    
    if(show!=0) {
        cout << "Eliminamos..."; ShowNoTerminalDivision(SetDifferenceDivision(set_terminal_original,set_no_terminal)); cout << endl;
    }
    RemoveSymbolFromCfg(SetDifferenceDivision(set_terminal_original,set_no_terminal));
    if(show!=0) {
        cout << "Eliminamos..."; ShowNoTerminalDivision(SetDifferenceDivision(set_terminal_.get_alphabet(),alphabet)); cout << endl;
    }
    RemoveSymbolFromCfg(SetDifferenceDivision(set_terminal_.get_alphabet(),alphabet));
    
}

void Cfg::Clear()
{
    set_terminal_.Clear();
    set_no_terminal_.clear();
}
   
void Cfg::SwapNoTerminal(const NoTerminal& no_terminal_in_1, const NoTerminal& no_terminal_in_2)
{
    set_no_terminal_.erase(no_terminal_in_1);
    set_no_terminal_.insert(no_terminal_in_2);
}

void Cfg::ShowNoTerminalDivision(const set<char>& set_no_terminal) const
{
    if(set_no_terminal.size()>0) {
        cout << "{ ";
        set<char>::iterator it=set_no_terminal.begin();
        while(it!=set_no_terminal.end()) {
            cout << *it;
            ++it;
            if (it!=set_no_terminal.end())
                cout << " , ";
            else
                cout << " }" << endl;
        }
    }
}

set<char> Cfg::SetIntersectionDivision(const set<char>& division_1, const set<char>& division_2) const
{
    set<char> division_out;
    
    set_intersection(division_1.begin(), division_1.end(), division_2.begin(), division_2.end(), inserter(division_out, division_out.begin()));
    
    return division_out;
}

set<char> Cfg::SetDifferenceDivision(const set<char>& division_1, const set<char>& division_2) const
{
    set<char> division_out;
    
    set_difference(division_1.begin(), division_1.end(), division_2.begin(), division_2.end(), inserter(division_out, division_out.begin()));
    
    return division_out;  
}

set<char> Cfg::SetUnionDivision(const set<char>& division_1, const set<char>& division_2) const
{
    set<char> division_out;
    
    set_union(division_1.begin(), division_1.end(), division_2.begin(), division_2.end(), inserter(division_out, division_out.begin()));
    
    return division_out;  
}

void Cfg::RemoveSymbolFromCfg(const set<char>& set_symbol_useless)
{
    set<NoTerminal> set_no_terminal=set_no_terminal_;
    int i=0;
    for (set<char>::iterator it=set_symbol_useless.begin(); it!=set_symbol_useless.end();++it) {
        for (set<NoTerminal>::iterator it2=set_no_terminal_.begin(); it2!=set_no_terminal_.end(); ++it2) {
            if((*it2).get_identifier() == *it && !(*it2).is_initial()) {
                set_no_terminal.erase(*it2);    
            }
            else{
                NoTerminal no_terminal=*it2;
                no_terminal.RemoveSymbolFromProductions(*it);
                set_no_terminal.erase(*it2); set_no_terminal.insert(no_terminal);
            }
        }
        if(set_terminal_.it_belongs(*it))
            set_terminal_.erase(*it);
        set_no_terminal_=set_no_terminal;
    }
    
}

char Cfg::GetNoTerminalInitial() const
{
    for (set<NoTerminal>::iterator it=set_no_terminal_.begin(); it!=set_no_terminal_.end(); ++it)
        if((*it).is_initial())
            return (*it).get_identifier();
}

NoTerminal Cfg::GetNoTerminalWithId(const char& no_terminal_id) const
{
    for (set<NoTerminal>::iterator it=set_no_terminal_.begin(); it!=set_no_terminal_.end(); ++it)
        if(no_terminal_id==(*it).get_identifier())
            return (*it);
}