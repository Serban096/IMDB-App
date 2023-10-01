#include <iostream>
#include<map>
#include<set>
#include<vector>
#include<list>
#include<string.h>
#include<stdexcept>

using namespace std;

class Show
{
protected:
    string titlu;
    int nr_actori;
    map<string, string> actori;
    set<string> genuri;
    int an_lansare;
    float rating;
    int nr_ratinguri;
public:
    Show();
    Show(string, int, map<string, string>, set<string>, int, float, int);
    Show(const Show&);

    Show& operator = (const Show& obj);
    friend istream& operator >> (istream& in, Show& obj);
    friend ostream& operator << (ostream& out, const Show& obj);

    string getTitlu(){return this->titlu;}
    float getRating(){return this->rating;}
    void setRating(float x){this->rating = (this->rating * this->nr_ratinguri + x) / (++this->nr_ratinguri);}

    virtual ~Show(){};
};

Show :: Show()
{
    this->titlu = "";
    this->nr_actori = 0;
    this->actori = {};
    this->genuri = {};
    this->an_lansare = 1895;
    this->rating = 0;
    this->nr_ratinguri = 0;
}

Show :: Show(string titlu, int nr_actori, map<string, string> actori, set<string> genuri, int an_lansare, float rating, int nr_ratinguri)
{
    this->titlu = titlu;
    this->nr_actori = nr_actori;
    this->actori = actori;
    this->genuri = genuri;
    this->an_lansare = an_lansare;
    this->rating = rating;
    this->nr_ratinguri = nr_ratinguri;
}

Show :: Show(const Show& obj)
{
    this->titlu = obj.titlu;
    this->nr_actori = obj.nr_actori;
    this->actori = obj.actori;
    this->genuri = obj.genuri;
    this->an_lansare = obj.an_lansare;
    this->rating = obj.rating;
    this->nr_ratinguri = obj.nr_ratinguri;
}

Show& Show :: operator = (const Show& obj)
{
    if(this != &obj){
        this->titlu = obj.titlu;
        this->nr_actori = obj.nr_actori;
        this->actori = obj.actori;
        this->genuri = obj.genuri;
        this->an_lansare = obj.an_lansare;
        this->rating = obj.rating;
        this->nr_ratinguri = obj.nr_ratinguri;
    }
    return *this;
}

ostream& operator << (ostream& out, const Show& obj)
{
    out<<"Titlu: "<<obj.titlu<<endl;
    out<<"Nr. actori: "<<obj.nr_actori<<endl;
    out<<"Distributie:"<<endl;
    for(auto i : obj.actori)
        out<<i.first<<": "<<i.second<<endl;
    out<<"Genuri: ";
    for(auto i : obj.genuri)
        out<<i<<", ";
    out<<endl;
    out<<"An lansare: "<<obj.an_lansare<<endl;
    out<<"Rating: "<<obj.rating<<endl;
    return out;
}

istream& operator >> (istream& in, Show& obj)
{
    cout<<"Titlu: "; in>>obj.titlu;
    cout<<"Nr. actori:";
     try{
        in>>obj.nr_actori;
        if(obj.nr_actori <= 0)
            throw std::invalid_argument("Argument Invalid!");
    }
    catch(const invalid_argument &e){
        while(obj.nr_actori <= 0){
            cout<<e.what()<<endl;
            cout<<"Nr. actori: "; in>>obj.nr_actori;
        }
    }

    for(int i=0; i<obj.nr_actori; i++){
        string rol, actor;
        cout<<"Rol: "; in>>rol;
        cout<<"Actor: "; in>>actor;
        obj.actori[rol] = actor;
    }
    int nr;
    cout<<"Nr. genuri: "; in>>nr;
    cout<<"Genuri: ";
    for(int i=0; i<nr; i++){
        string gen;
        in>>gen;
        obj.genuri.insert(gen);
    }
    cout<<"An lansare: ";
    try{
        in>>obj.an_lansare;
        if(obj.an_lansare > 2023)
            throw std::invalid_argument("Argument Invalid!");
    }
    catch(const invalid_argument &e){
        while(obj.an_lansare > 2023){
            cout<<e.what()<<endl;
            cout<<"An lansare: "; in>>obj.an_lansare;
        }
    }

    return in;
}

class Film : public Show
{
protected:
    int durata;
public:
    Film();
    Film(string, int, map<string, string>, set<string>, int, float, int, int);
    Film(const Film&);

    Film& operator = (const Film& obj);
    friend istream& operator >> (istream& in, Film& obj);
    friend ostream& operator << (ostream& out, const Film& obj);

    ~Film(){};
};

Film :: Film() : Show()
{
    this->durata = 90;
}

Film :: Film(string titlu, int nr_actori, map<string, string> actori, set<string> genuri, int an_lansare, float rating, int nr_ratinguri, int durata)
 : Show(titlu, nr_actori, actori, genuri, an_lansare, rating, nr_ratinguri)
 {
     this->durata = durata;
 }

Film :: Film(const Film& obj) : Show(obj)
{
    this->durata = obj.durata;
}

Film& Film :: operator = (const Film& obj)
{
    if(this != &obj){
        Show :: operator = (obj);
        this->durata = obj.durata;
    }
    return *this;
}

istream& operator >> (istream& in, Film& obj)
{
    in>>(Show&)obj;
    cout<<"Durata: "; in>>obj.durata;
    return in;
}

ostream& operator << (ostream& out, const Film& obj)
{
    out<<(Show&)obj;
    out<<"Durata: "<<obj.durata<<" minute"<<endl;
    return out;
}

class Serial : public Show
{
protected:
    int nr_sezoane;
    int nr_episoade;
public:
    Serial();
    Serial(string, int, map<string, string>, set<string>, int, float, int, int, int);
    Serial(const Serial&);

    Serial& operator = (const Serial& obj);
    friend istream& operator >> (istream& in, Serial& obj);
    friend ostream& operator << (ostream& out, const Serial& obj);

    ~Serial(){};
};

Serial :: Serial() : Show()
{
    this->nr_sezoane = 1;
    this->nr_episoade = 1;
}

Serial :: Serial(string titlu, int nr_actori, map<string, string> actori, set<string> genuri, int an_lansare, float rating, int nr_ratinguri, int nr_sezoane, int nr_episoade)
 : Show(titlu, nr_actori, actori, genuri, an_lansare, rating, nr_ratinguri)
 {
    this->nr_sezoane = nr_sezoane;
    this->nr_episoade = nr_episoade;
 }

Serial :: Serial(const Serial& obj) : Show(obj)
{
    this->nr_sezoane = obj.nr_sezoane;
    this->nr_episoade = obj.nr_episoade;
}

Serial& Serial :: operator = (const Serial& obj)
{
    if(this != &obj){
        Show :: operator = (obj);
        this->nr_sezoane = obj.nr_sezoane;
        this->nr_episoade = obj.nr_episoade;
    }
    return *this;
}

istream& operator >> (istream& in, Serial& obj)
{
    in>>(Show&)obj;
    cout<<"Nr. sezoane: "; in>>obj.nr_sezoane;
    cout<<"Nr. episoade: "; in>>obj.nr_episoade;
    return in;
}

ostream& operator << (ostream& out, const Serial& obj)
{
    out<<(Show&)obj;
    out<<"Nr. sezoane: "<<obj.nr_sezoane<<endl;
    out<<"Nr. episoade: "<<obj.nr_episoade<<endl;
    return out;
}

class FilmRomanesc : public Film
{
protected:
    string locatie_filmare;
public:
    FilmRomanesc();
    FilmRomanesc(string, int, map<string, string>, set<string>, int, float, int, int, string);
    FilmRomanesc(const FilmRomanesc&);

    FilmRomanesc& operator = (const FilmRomanesc& obj);
    friend istream& operator >> (istream& in, FilmRomanesc& obj);
    friend ostream& operator << (ostream& out, const FilmRomanesc& obj);

    ~FilmRomanesc(){};
};

FilmRomanesc :: FilmRomanesc() : Film()
{
    this->locatie_filmare = "";
}

FilmRomanesc :: FilmRomanesc(string titlu, int nr_actori, map<string, string> actori, set<string> genuri, int an_lansare, float rating, int nr_ratinguri, int durata, string locatie_filmare)
 : Film(titlu, nr_actori, actori, genuri, an_lansare, rating, nr_ratinguri, durata)
 {
     this->locatie_filmare = locatie_filmare;
 }

FilmRomanesc :: FilmRomanesc(const FilmRomanesc& obj) : Film(obj)
{
    this->locatie_filmare = obj.locatie_filmare;
}

FilmRomanesc& FilmRomanesc :: operator = (const FilmRomanesc& obj)
{
    if(this != &obj){
        Film :: operator = (obj);
        this->locatie_filmare = obj.locatie_filmare;
    }
    return *this;
}

istream& operator >> (istream& in, FilmRomanesc& obj)
{
    in>>(Film&)obj;
    cout<<"Locatie filmare: "; in>>obj.locatie_filmare;
    return in;
}

ostream& operator << (ostream& out, const FilmRomanesc& obj)
{
    out<<(Film&)obj;
    out<<"Locatie filmare: "<<obj.locatie_filmare<<endl;
    return out;
}

template <class T>
void cautare_titlu(vector<T*>& v, string titlu)
{
    for(int i=0; i<v.size(); i++)
        if(v[i]->getTitlu() == titlu)
            cout<<*v[i]<<endl;
}

template <class T>
void cautare_rating(vector<T*>& v, float min_rating, float max_rating)
{
    for(int i=0; i<v.size(); i++)
        if(v[i]->getRating() > min_rating && v[i]->getRating() < max_rating)
            cout<<*v[i]<<endl;
}

template<class T1, class T2>
    vector<T2*> filtru( vector<T1*>& v)
    {
        vector<T2*> filtrat;
        for(int i=0; i<v.size(); i++)
            if(dynamic_cast<T2*>(v[i]))
                filtrat.push_back(dynamic_cast<T2*>(v[i]));
        return filtrat;
    }

class Meniu
{
    vector<Show*> v;
    Meniu() = default;
    Meniu(const Meniu&) = delete;
    static int noOfInstance;
    static Meniu* obiect;
public:
    void startApp();
    void addObject();
    void modifyObject();
    void deleteObject();
    void showObject();
    void giveRating();
    void filtreaza();

    static Meniu* getInstance()
    {
        noOfInstance++;
        if(!obiect)
            obiect = new Meniu();
        return obiect;
    }

   ~Meniu(){
        noOfInstance--;
        if(noOfInstance==0)
            if(obiect)
                delete obiect;}
};

int Meniu :: noOfInstance = 0;
Meniu* Meniu :: obiect = 0;

void Meniu :: startApp()
{
    system("CLS");
    int k=1;
    while(k){
        cout<<"IMDB"<<endl;
        cout<<"1. Adauga"<<endl;
        cout<<"2. Modifica"<<endl;
        cout<<"3. Sterge"<<endl;
        cout<<"4. Afiseaza"<<endl;
        cout<<"5. Da rating unui show"<<endl;
        cout<<"6. Cauta"<<endl;
        cout<<"0. Stop"<<endl;
        int x;
        cin>>x;
        switch(x)
        {
            case 1:{
                addObject();
                break;
            }
            case 2:{
                modifyObject();
                break;
            }
            case 3:{
                deleteObject();
                break;
            }
            case 4:{
                showObject();
                break;
            }
            case 5:{
                giveRating();
                break;
            }
            case 6:{
                filtreaza();
                break;
            }
            case 0:{
                k = 0;
                break;
            }
            default:{
                system("CLS");
                cout<<"Comanda invalida!"<<endl;
                system("PAUSE");
                system("CLS");
                break;
            }
        }
        system("CLS");
    }
}

void Meniu :: addObject()
{
    system("CLS");
    cout<<"1. Adauga film"<<endl;
    cout<<"2. Adauga film romanesc"<<endl;
    cout<<"3. Adauga serial"<<endl;
    int x;
    cin>>x;
    system("CLS");
    if(x == 1){
        Film* obj = new Film();
        cin>>*obj;
        v.push_back(obj);
    }
    else if(x == 2){
        FilmRomanesc* obj = new FilmRomanesc();
        cin>>*obj;
        v.push_back(obj);
    }
    else{
        Serial* obj = new Serial();
        cin>>*obj;
        v.push_back(obj);
    }
}

void Meniu :: deleteObject()
{
    system("CLS");
    for(int i=0; i<v.size(); i++)
        cout<<*v[i]<<endl;
    cout<<"Scrie indicele obiectului pe care vrei sa-l stergi"<<endl;
    int j;
    cin>>j;
    try{
        if(j >= v.size() || j < 0)
            throw std::out_of_range("Indice invalid!");
        v.erase(v.begin() + j);}

    catch(const std::out_of_range &e){
        system("CLS");
        cout<<e.what()<<endl;
        system("PAUSE");
    }
}

void Meniu :: modifyObject()
{
    system("CLS");
    for(int i=0; i<v.size(); i++)
        cout<<*v[i]<<endl;
    cout<<"Scrie indicele obiectului pe care vrei sa-l modifici"<<endl;
    int j;
    cin>>j;
    try{
        if(j >= v.size() || j < 0)
            throw std::out_of_range("Indice invalid!");
        system("CLS");
        if(dynamic_cast<Film*>(v[j])){
            Film* aux = new Film();
            cin>>*aux;
            v[j] = aux;
            }
        else if(dynamic_cast<Serial*>(v[j])){
            Serial* aux = new Serial();
            cin>>*aux;
            v[j] = aux;
        }
        else if(dynamic_cast<FilmRomanesc*>(v[j])){
            FilmRomanesc* aux = new FilmRomanesc();
            cin>>*aux;
            v[j] = aux;
        }
    }

    catch(const std::out_of_range &e){
        system("CLS");
        cout<<e.what()<<endl;
        system("PAUSE");
    }
}

void Meniu :: showObject()
{
    system("CLS");
    for(int i=0; i<v.size(); i++)
        if(dynamic_cast<Film*>(v[i]))
            if(dynamic_cast<FilmRomanesc*>(v[i]))
                cout<<*(dynamic_cast<FilmRomanesc*>(v[i]))<<endl;
            else cout<<*(dynamic_cast<Film*>(v[i]))<<endl;
        else if(dynamic_cast<Serial*>(v[i]))
            cout<<*(dynamic_cast<Serial*>(v[i]))<<endl;


    system("PAUSE");
}

void Meniu :: giveRating()
{
    system("CLS");
    for(int i=0; i<v.size(); i++)
        cout<<*v[i]<<endl;
    cout<<"Scrie indicele show-ului caruia vrei sa-i dai nota"<<endl;
    int j;
    cin>>j;
    try{
        if(j >= v.size() || j < 0)
            throw std::out_of_range("Indice invalid!");
        system("CLS");
        float x;
        cout<<"Rating-ul tau: ";
        cin>>x;
        try{
        if(x < 0 || x > 10)
            throw std::invalid_argument("Rating-ul trebuie sa fie intre 0 si 10!");
    }
        catch(const invalid_argument &e){
            while(x < 0 || x > 10){
                cout<<e.what()<<endl;
                cout<<"Rating-ul tau: "; cin>>x;
            }
        }
        v[j]->setRating(x);
    }

    catch(const std::out_of_range &e){
        system("CLS");
        cout<<e.what()<<endl;
        system("PAUSE");
    }
}

void Meniu :: filtreaza()
{
    system("CLS");
    cout<<"1. Arata filmele"<<endl;
    cout<<"2. Arata filmele romanesti"<<endl;
    cout<<"3. Arata serialele"<<endl;
    cout<<"4. Cauta dupa nume"<<endl;
    cout<<"5. Cauta dupa rating"<<endl;
    int x;
    cin>>x;
    switch(x)
    {
        case 1:{
            system("CLS");
            vector<Film*> filtrat;
            filtrat = filtru<Show, Film>(v);
            for(int i=0; i<filtrat.size(); i++)
                cout<<*filtrat[i]<<endl;
            break;
        }
        case 2:{
            system("CLS");
            vector<FilmRomanesc*> filtrat;
            filtrat = filtru<Show, FilmRomanesc>(v);
            for(int i=0; i<filtrat.size(); i++)
                cout<<*filtrat[i]<<endl;
            break;
        }
        case 3:{
            system("CLS");
            vector<Serial*> filtrat;
            filtrat = filtru<Show, Serial>(v);
            for(int i=0; i<filtrat.size(); i++)
                cout<<*filtrat[i]<<endl;
            break;
        }
        case 4:{
            system("CLS");
            string titlu;
            cout<<"Introduceti titlul cautat: ";
            cin>>titlu;
            cautare_titlu<Show>(v, titlu);
            break;
        }
        case 5:{
            system("CLS");
            float minim, maxim;
            cout<<"Rating minim: "; cin>>minim;
            cout<<"Rating maxim: "; cin>>maxim;
            try{
                if(minim < 0 || maxim > 10)
                    throw std::invalid_argument("Rating-ul trebuie sa fie intre 0 si 10!");
                system("CLS");
                cautare_rating<Show>(v, minim, maxim);
            }
            catch(const invalid_argument &e){
                system("CLS");
                cout<<e.what()<<endl;
            }
            break;
        }
    }
    system("PAUSE");
}

int main()
{
    Meniu* a = a->getInstance();
    a->startApp();
//    cout<<a<<endl<<b<<endl<<c;
//    vector<Film> v;
//    map<string, string> m;
//    string titlu;
//    int minim, maxim;
//    m.insert(pair<string, string>("ceva", "Leonardo DiCaprio"));
//    m.insert(pair<string, string>("altceva", "Robert DeNiro"));
//    Show a, b("Wolf of Wall Street", 2, m, {"comedie"}, 2012, 8.9);
//    Film c, d("Ceva", 2, m, {"actiune", "drama"}, 2012, 4.9, 120), e("Ceva", 2, m, {"comedie", "drama"}, 2012, 8.9, 120);
//    v.push_back(c);
//    v.push_back(d);
//    v.push_back(e);
//    cin>>minim>>maxim;
//    //cin>>titlu;
//    cautare_rating(v, minim, maxim);
//   // cout<<c<<endl<<d<<endl<<e<<endl;

    return 0;
}
