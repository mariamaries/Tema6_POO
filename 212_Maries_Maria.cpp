#include <iostream>
#include <vector>
#include <tuple>
#include <cstdlib>
#include <string.h>

using namespace std;

typedef vector<tuple<string,unsigned int,float>> my_tup;

class Farmacie{
public:
    Farmacie(){
    }
    virtual ~Farmacie(){
    }
    virtual void citire(istream &in){
    }
    virtual void afisare(ostream &out){
    }
    friend istream& operator>> (istream& in , Farmacie& f){
        f.citire(in);
        return in;
    }
    friend ostream& operator<< (ostream& out, Farmacie& f){
        f.afisare(out);
        return out;
    }
};

class FarmacieNormala:public Farmacie{
private:
    string denumire;
    unsigned int nr_angajati;
    float profit;
public:
    FarmacieNormala(string den = " ",unsigned int nra = 0, float p = 0){
        this->denumire = den;
        this->nr_angajati = nra;
        this->profit = p;
    }
    ~FarmacieNormala(){
        this->denumire = " ";
        this->nr_angajati = 0;
        this->profit = 0;
    }
    FarmacieNormala(FarmacieNormala &f){
        this->denumire = f.denumire;
        this->nr_angajati = f.nr_angajati;
        this->profit = f.profit;
    }
    FarmacieNormala& operator= (FarmacieNormala &f){
        if (this != &f){
        denumire = f.denumire;
        nr_angajati =  f.nr_angajati;
        profit = f.profit;
        }
        return *this;
    }
    void citire(istream &in){
        string d;
        cout<<"Denumire farmacie: ";
        in>>d;
        denumire = d;
        unsigned int n;
        cout<<"Numarul angajatilor: ";
        in>>n;
        nr_angajati = n;
        float p;
        cout<<"Profitul: ";
        in>>p;
        profit = p;
    }
    void afisare(ostream &out)const{
        out<<"Denumire farmacie: "<<denumire<<"\n";
        out<<"Numarul angajatilor: "<<nr_angajati<<"\n";
        out<<"Profitul: "<<profit<<"\n";
    }
    friend istream& operator>>(istream& in,FarmacieNormala& f){
    f.citire(in);
    return in;
    }

    friend ostream& operator<<(ostream& out, FarmacieNormala& f){
    f.afisare(out);
    return out;
    }
};

class FarmacieOnline:public Farmacie{
private:
    string adresa_web;
    unsigned int nr_vizitatori;
    float discount;
public:
    FarmacieOnline(string aw = " ",unsigned int nrv = 0, float d = 0){
        this->adresa_web = aw;
        this->nr_vizitatori = nrv;
        this->discount = d;
    }
    ~FarmacieOnline(){
        this->adresa_web = " ";
        this->nr_vizitatori = 0;
        this->discount = 0;
    }
    FarmacieOnline(FarmacieOnline &f){
        this->adresa_web = f.adresa_web;
        this->nr_vizitatori = f.nr_vizitatori;
        this->discount = f.discount;
    }
    unsigned int get_nr_vizitatori(){
        return nr_vizitatori;
    }
    string get_adresaweb(){
        return adresa_web;
    }
    float get_discount(){
        return discount;
    }
    FarmacieOnline& operator= (FarmacieOnline &f){
        if (this != &f){
        adresa_web = f.adresa_web;
        nr_vizitatori =  f.nr_vizitatori;
        discount = f.discount;
        }
        return *this;
    }
    void citire(istream &in){
        string d;
        cout<<"Adresa web a farmaciei: ";
        loop:try{
            in>>d;
            if(d[0]!='w'||d[1]!='w'||d[2]!='w'){
                throw 11;
            }
        } catch(int x){
            cout<<"Introduceti o adresa web valida "<<x<<endl;
            goto loop;
        }
        adresa_web = d;
        unsigned int n;
        cout<<"Numarul vizitatorilor: ";
        in>>n;
        nr_vizitatori = n;
        float p;
        cout<<"Discountul: ";
        in>>p;
        discount = p;
    }
    void afisare(ostream &out)const{
        out<<"Adresa web a farmaciei: "<<adresa_web<<"\n";
        out<<"Numarul vizitatorilor: "<<nr_vizitatori<<"\n";
        out<<"Discountul: "<<discount<<"\n";
    }
    friend istream& operator>>(istream& in,FarmacieOnline& f){
    f.citire(in);
    return in;
    }

    friend ostream& operator<<(ostream& out, FarmacieOnline& f){
    f.afisare(out);
    return out;
    }
};

template <class T>
class GestionareFarmacii {
private:
    T *v;
    static int index;
    int id_lant;
public:
    GestionareFarmacii(T *p = NULL, int n = 0, unsigned int id = 1){
        index=n;
        id_lant = id;
//        cout<<"Introduceti id-ul lantului de farmacii: "<<endl;
//        cin>>id_lant;
        if (n!=0){
            v=new T[n];
            for(int i=0;i<n;i++)
            {
                v[i]=p[i];
            }
        }
    }
    GestionareFarmacii(GestionareFarmacii &gm){
        index=gm.index;
        v=new T[index];
        for(int i=0;i<gm.index;i++)
        {
            v[i]=gm.v[i];
        }
    }
    ~GestionareFarmacii()
    {
        delete [] v;
    }
    T get_v(int i){
        return v[i];
    }
    static int get_index(){
        return index;
    }
    friend istream& operator >>(istream &in, GestionareFarmacii <T> &gf){
        cout<<"Introduceti id-ul lantului de farmacii: ";
        in>>gf.id_lant;
        cout<<"Introduceti numarul de farmacii: ";
        in>>gf.index;
        gf.v=new T[gf.index];
        cout<<"Introduceti farmaciile: \n";
        for(int i=0;i<gf.index;i++){
           in>>gf.v[i];
           cout<<"\n";
        }
        return in;
    }
    friend ostream& operator <<(ostream &out, GestionareFarmacii<T> &gf){
        out<<"In lantul de farmacii cu id_ul "<<gf.id_lant<<" se gasesc urmatoarele "<<gf.index<<" farmacii:"<<"\n";
        for(int i=0;i<gf.index;i++)
            out<<gf.v[i]<<"\n";
        return out;
    }
    GestionareFarmacii& operator= (const GestionareFarmacii& gf){
            id_lant = gf.id_lant;
            delete v;
            this->index = gf.index;
            v = new T[index];
            for (int i = 0; i < gf.index; i++) v[i] = gf.v[i];
            return *this;
    }

    GestionareFarmacii& operator+= (T& f){
            if(index == 0){
                index++;
                v = new T[1];
                v[0] = f;
                cout<<"Introduceti id-ul lantului: \n";
                cin>>id_lant;
            }
            else {
                index++;
                T *ptr = v;
                v = new T[index];
                for(int i=0;i<index-1;i++){
                    v[i] = ptr[i];
                }
                v[index-1] = f;
            }
            cout << endl << "O noua farmacie a fost adaugata in lant." << endl;
            return *this;
    }
};
template <class T> int GestionareFarmacii< T >::index = 0;
template <>
class GestionareFarmacii<FarmacieOnline>{
private:
    int total;
public:
    GestionareFarmacii(int n = 0){
        this->total = n;
    }
    GestionareFarmacii(GestionareFarmacii &gm){
        gm.total = this->total;
    }
    ~GestionareFarmacii()
    {
        this->total = 0;
    }
    int get_total(){
        return total;
    }
    friend istream& operator >>(istream &in, GestionareFarmacii <FarmacieOnline> &gf){
        int nr;
        cout<<"Introduceti numarul de farmacii: ";
        in>>nr;
        cout<<"Introduceti numarul de vizitatori online ai farmaciilor: \n";
        for(int i=0;i<nr;i++){
            int vizitatori;
            in>>vizitatori;
            gf.total += vizitatori;
            cout<<"\n";
        }
        return in;
    }
    friend ostream& operator <<(ostream &out, GestionareFarmacii<FarmacieOnline> &gf){
        out<<"farmaciile online au avut in total "<<gf.total<<" vizitatori"<<"\n";
        return out;
    }
    GestionareFarmacii& operator= (const GestionareFarmacii& gf){
            total = gf.total;
            return *this;
    }

    GestionareFarmacii& operator+= (FarmacieOnline& f){
            total += f.get_nr_vizitatori();
            return *this;
    }
};

void menu_output(){
    cout<<"\nGESTIONARE FARMACII\n";
    cout<<"\n\t\tMENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"1. Citeste informatii despre farmacii.";
    cout<<"\n";
    cout<<"2. Afisare informatii despre farmaciile normale. ";
    cout<<"\n";
    cout<<"3. Afisare informatii despre farmaciile online. ";
    cout<<"\n";
    cout<<"4. Afisare numar total de vizitatori ai farmaciilor online.";
    cout<<"\n";
    cout<<"0. Iesire.";
    cout<<"\n";
    cout<<"\nIntroduceti numarul actiunii: ";
}

void menu(){
    int option = 0;
    int nextoption = 0;
    GestionareFarmacii <FarmacieNormala> *gf1 = new GestionareFarmacii <FarmacieNormala>;
    GestionareFarmacii <FarmacieOnline> *gf2 = new GestionareFarmacii <FarmacieOnline>;
    my_tup farmaciiOnline;
    do{
    menu_output();
    cin>>option;

    switch(option){
    case 0:
        cout<<"\nEXIT\n\n";
        break;
    case 1:
        cout<<"1. Introduceti o farmacie normala. ";
        cout<<"\n";
        cout<<"2. Introduceti o farmacie online. ";
        cout<<"\n";
        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>nextoption;
        if (nextoption == 1){
            FarmacieNormala *fn = new FarmacieNormala();
            cin>>*fn;
            *gf1 += *fn;
        }
        if(nextoption == 2){
            FarmacieOnline *fo = new FarmacieOnline();
            cin>>*fo;
            *gf2 += *fo;
            farmaciiOnline.push_back(make_tuple((*fo).get_adresaweb(),(*fo).get_nr_vizitatori(),(*fo).get_discount()));
        }
        break;
    case 2:
        cout<<*gf1;
        break;
    case 3:
        for (my_tup::const_iterator i = farmaciiOnline.begin(); i != farmaciiOnline.end(); ++i) {
        cout << get<0>(*i) << endl;
        cout << get<1>(*i) << endl;
        cout << get<2>(*i) << endl;
        }
        break;
    case 4:
        cout<<*gf2;
        break;
    default:
        cout<<"\nSelectie invalida\n";
        break;
    }
    cout<<"\n";
    system("pause");
    system("cls");
}
while(option != 0);
}

int main()
{
      menu();
      return 0;
}
