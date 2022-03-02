#include<iostream>
#include<cmath>
#include<string>
#include<typeinfo>
using namespace std;
class Monom {
private:
    int grad;
    double coef;
public:
    friend class Polinom;
    Monom();
    Monom(int, double);///constructor de initializare
    int get_grad() { return grad; };
    double get_coef() { return coef;};
    void set_grad(int x) { grad = x;};
    void set_coef(double x) { coef = x;};
    Monom(Monom&);///Constructor de copiere
    ~Monom();
    void citire(istream& in);
    void afisare(ostream& out);
    friend istream& operator>>(istream&, Monom&);
    friend ostream& operator<<(ostream&, Monom&);
    Monom& operator=(Monom& m);

};
Monom::Monom() {
    this->grad = 0;
    this->coef = 0;
}
Monom::Monom(int grad, double coef) ///initializare cu parametrii
{
    this->grad = grad;
    this->coef = coef;
}
Monom::Monom(Monom& m) {
    this->grad = m.grad;
    this->coef = m.coef;
}
Monom::~Monom()///destructor
{
    this->grad = 0;
    this->coef = 0;
}
void Monom::citire(istream& in) //citire
{

    in >> grad;
    in >> coef;


}
istream& operator>>(istream& in, Monom& m)
{
    m.citire(in);
    return in;
}
void Monom::afisare(ostream& out)
{
    if (grad > 1)
        cout << coef << "x^" << grad;
    else
        if (grad == 1)
            cout << coef << "x";
        else
            cout << coef;
}
ostream& operator<<(ostream& out, Monom& m) {
    m.afisare(out);
    return out;
}
Monom& Monom::operator=(Monom& m)
{
    grad = m.grad;
    coef = m.coef;
    return *this;
}
class Polinom
{
protected:
    int nr_monoame;
    Monom* m;
    static int n;
public:
    Polinom();
    Polinom(int, Monom*);///constructor de initializare
    Polinom(Polinom&);///Constructor de copiere
    int get_nr_monoame() { return nr_monoame; };
    double get_element(int i) { return m[i].coef; };
    void set_element(int, int);
    virtual ~Polinom();
    virtual void citire(istream& in);
    virtual void afisare(ostream& out);
    friend istream& operator>>(istream&, Polinom&);
    friend  ostream& operator<<(ostream&, Polinom&);
    Polinom& operator=(Polinom& m);
    static int Numar_Obiecte() {  return n; }
};
int Polinom::n;
Polinom::Polinom()
{
    n++;
    this->nr_monoame = 0;
    this->m = NULL;
}
Polinom::Polinom(int nr_monoame, Monom* m)
{
    n++;
    this->nr_monoame = nr_monoame;
    m = new Monom[nr_monoame + 1];
    m = nullptr;
}

Polinom::Polinom(Polinom& n)
{
    this->nr_monoame = n.nr_monoame;
    m = new Monom[nr_monoame + 1];
    for (int i = 0; i <= nr_monoame; i++)
        this->m[i] = n.m[i];


}
void Polinom::set_element(int i, int val)
{
    m[i].coef = val;
}

void Polinom::citire(istream& in)
{
    cout << "---------------------------------------------------------------------------------------------\n";

    cout << "Introduceti numarul de monoame pe care doriti sa il cititi:";
    in >> nr_monoame;
    if (nr_monoame < 1)
        while (nr_monoame < 1)
        {   cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << "Numarul de monoame este invalid! Introduceti un numar de monoame valid (numarul de monoame a unui polinom trebuie sa fie >=1)\n";
            cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << "Introduceti numarul de monoame pe care doriti sa il cititi:";
            in >> nr_monoame;
            cout << endl;
        }
    m = new Monom[nr_monoame + 1];
    for (int i = nr_monoame; i >= 0; i--)
    {
        cout << "Introduceti gradul monomului:";
        in >> m[i].grad;
        if (m[i].grad != i)
            while (m[i].grad != i)
            {
                cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                cout << "Introduceti un grad al monomului valid.\n";
                cout << "Un grad valid al monomului este cu o unitate mai mica decat cel precedent/gradul maxim al polinomului.\n";
                cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                cout << "Introduceti un nou grad al polinomului:";
                in >> m[i].grad;

            }
        cout << "Introduceti coeficientul monomului:";
        in >> m[i].coef;
        while (m[i].coef < -10000 || m[i].coef>10000)
        {   cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << "Introduceti un coeficient din intervalul [-10000,10000], deoarece acesta este prea mare pt prelucrare.";
            cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout<<"Introduceti un nou coeficient pentru acest grad:";
            in >> m[i].coef;
        }


        cout << endl;
    }


}
istream& operator>>(istream& in, Polinom& p) {
    p.citire(in);
    return in;
}
void Polinom::afisare(ostream& out)
{
    out << "Polinomul initial este format din " << nr_monoame << " monoame.\n";
    for (int i = nr_monoame; i >= 0; i--)
        if (m[i].coef < 0)
            out << m[i];
        else
            if (i != nr_monoame)
                out << "+" << m[i];
            else
                out << m[i];
}
ostream& operator<<(ostream& out, Polinom& p) {
    if (typeid(p) == typeid(Polinom))
    {
        p.afisare(out);
        out << endl;
    }
    return out;
}
Polinom::~Polinom()
{
    this->nr_monoame = 0;
    delete[]m;
}
Polinom& Polinom::operator=(Polinom& m)
{
    this->nr_monoame = m.nr_monoame;
    this->m = new Monom[nr_monoame + 1];
    for (int i = nr_monoame; i >= 0; i--)
        this->m[i] = m.m[i];
    return *this;
}

int afla_numitor(double x)
{
    int numitor = 1;
    bool executa = false;
    string s = to_string(x);
    string y = s.substr(s.rfind('.'));

    int l = y.length() - 1;

    while (l != 0)
    {
        if (y[l] == '0' && executa == false)
            y[l] = ' ';
        else
        {
            numitor *= 10;
            executa = true;
        }

        l--;
    }


    return  numitor;
}


class Polinom_ireductibil : public Polinom
{

public:
    Polinom_ireductibil();
    Polinom_ireductibil(int, Monom*);///constructor de initializare
    Polinom_ireductibil(Polinom_ireductibil&);///Constructor de copiere
    ~Polinom_ireductibil();
    void citire(istream& in);
    void afisare(ostream& out);
    friend istream& operator>>(istream&, Polinom_ireductibil&);
    friend ostream& operator<<(ostream&, Polinom_ireductibil&);
    Polinom_ireductibil& operator=(Polinom_ireductibil& m);
    int verif_ireductibilitate_criteriul_Eisenstein(Polinom_ireductibil);

};
Polinom_ireductibil::Polinom_ireductibil() :Polinom()
{

}

Polinom_ireductibil::Polinom_ireductibil(int nr_monoame, Monom* m) : Polinom(nr_monoame, m)///apelam constructorul din baza
{


}
Polinom_ireductibil::Polinom_ireductibil(Polinom_ireductibil& p) : Polinom(p)
{

}
Polinom_ireductibil& Polinom_ireductibil::operator = (Polinom_ireductibil& p)
{

    if (this != &p)
        Polinom::operator=(p);
    return *this;
}
int cmmdc(int a, int b)
{
    if (a < 0)
        a = (-1) * a;

    if (b < 0)
        b = (-1) * b;

    while (a != b)
    {
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }
    return a;

}
void afla_factori_primi(int x, int vector_factor_prim[])
{
    int k = 0;
    int div = 2;
    while (x != 1)
    {
        if (x % div == 0)
            vector_factor_prim[k++] = div;
        while (x % div == 0)
            x = x / div;
        div++;
    }

}
int afla_nr_factori_primi(int x)
{
    int k = 0;
    int div = 2;
    while (x != 1)
    {
        if (x % div == 0)
            k++;
        while (x % div == 0)
            x = x / div;
        div++;
    }
    return k;
}


int verif_ireductibilitate_criteriul_Eisenstein(Polinom_ireductibil a)
{
    int grad_polinom = a.get_nr_monoame();
    int numitor_max = 0;
    for (int i = 0; i < grad_polinom; i++)
        if (afla_numitor(a.get_element(i)) > numitor_max)
            numitor_max = afla_numitor(a.get_element(i));



    if (numitor_max > 1)
        for (int i = 0; i <= grad_polinom; i++)
            a.set_element(i, a.get_element(i) * numitor_max);

    if (grad_polinom == 1)
        return 1;

    if (a.get_element(0) == 1)
        return 2;

    int t_g_m = a.get_element(grad_polinom);
    int termen_liber = a.get_element(0);
    if (a.get_element(0) != 0)
    {
        int nr_cmmdc = cmmdc(a.get_element(0), a.get_element(0));

        for (int j = grad_polinom - 1; j >= 1; j--)
            if (a.get_element(j) != 0)
                nr_cmmdc = cmmdc(nr_cmmdc, a.get_element(j));

        if (nr_cmmdc != 1)
        {
            int nr_factori_primi = afla_nr_factori_primi(nr_cmmdc);
            int* factori_primi = new int[nr_factori_primi];
            afla_factori_primi(nr_cmmdc, factori_primi);
            for (int i = 0; i < nr_factori_primi; i++)
            {

                long  patrat_perfect = factori_primi[i] * factori_primi[i];

                if (t_g_m % factori_primi[i] != 0 && patrat_perfect % termen_liber != 0)


                    return 3;

                else

                    return 2;

                delete[]factori_primi;
            }
        }
        else
            return 2;
    }
    else
        return 4;

}

void Polinom_ireductibil::citire(istream& in)
{
    Polinom::citire(in);

}
void Polinom_ireductibil::afisare(ostream& out)
{
    Polinom::afisare(out);
    out << endl;
    out << endl;
    out << "Rezultatul in urma verificarii ireductibilitatii cu criteriul lui Eisenstein este urmatorul:\n";
}
istream& operator>>(istream& in, Polinom_ireductibil& p)
{

    p.citire(in);
    return in;
}
ostream& operator<<(ostream& out, Polinom_ireductibil& p)
{
    if (typeid(p) == typeid(Polinom_ireductibil))
    {
        p.afisare(out);
        if (verif_ireductibilitate_criteriul_Eisenstein(p) == 1)
            out << "Polinomul este ireductibil.\n";
        else
            if (verif_ireductibilitate_criteriul_Eisenstein(p) == 2)
                out << "Nu se poate determina ireductibilitatea cu criteriul lui Eisenstein.\n";
            else
                if (verif_ireductibilitate_criteriul_Eisenstein(p) == 3)
                    out << "Polinomul este ireductibil cu criteriul lui Eisenstein.\n";
                else
                    if (verif_ireductibilitate_criteriul_Eisenstein(p) == 4)
                        out << "Polinomul nu este ireductibil cu criteriul lui Eisenstein, dar se poate da factor comun.\n";

        out << endl;
    }
    return out;
}



Polinom_ireductibil::~Polinom_ireductibil()
{

}


class Polinom_reductibil : public Polinom
{

public:
    Polinom_reductibil();
    Polinom_reductibil(int, Monom*);///constructor de initializare
    Polinom_reductibil(Polinom_reductibil&);///Constructor de copiere
    ~Polinom_reductibil();
    void citire(istream& in);
    void afisare(ostream& out);
    friend istream& operator>>(istream&, Polinom_reductibil&);
    friend ostream& operator<<(ostream&, Polinom_reductibil&);
    Polinom_reductibil& operator=(Polinom_reductibil& m);
    void decompunere_polinom(Polinom_reductibil);
};
Polinom_reductibil::Polinom_reductibil() :Polinom()
{

}

Polinom_reductibil::Polinom_reductibil(int nr_monoame, Monom* m) : Polinom(nr_monoame, m)///apelam constructorul din baza
{


}
Polinom_reductibil::Polinom_reductibil(Polinom_reductibil& p) : Polinom(p)
{

}
Polinom_reductibil& Polinom_reductibil::operator = (Polinom_reductibil& p)
{

    if (this != &p)
        Polinom::operator=(p);
    return *this;
}

void afla_divizori(int x, int vector_div[])
{
    int k = 0;
    if (x < 0)
        x = x * (-1);
    for (int i = 1; i <= x; i++)

        if (x % i == 0)
        {
            vector_div[k++] = i;
            vector_div[k++] = -i;

        }




}

int numar_divizori(int x)
{
    int nr_divizori = 0;;
    if (x < 0)
        x = x * (-1);

    for (int i = 1; i <= x / 2; i++)

        if (x % i == 0)
            nr_divizori += 2;


    return nr_divizori;


}

void decompunere_polinom(Polinom_reductibil a)
{
    int grad_polinom = a.get_nr_monoame();
    int numitor_max = 0;
    for (int i = 0; i < grad_polinom; i++)
        if (afla_numitor(a.get_element(i)) > numitor_max)
            numitor_max = afla_numitor(a.get_element(i));

    if (numitor_max > 1)
        for (int i = 0; i <= grad_polinom; i++)
            a.set_element(i, a.get_element(i) * numitor_max);



    int termenul_liber = a.get_element(0);
    if (termenul_liber != 0)
    {
        int x = numar_divizori(termenul_liber);
        int* vector_div = new int[x * x];
        afla_divizori(termenul_liber, vector_div);


        long  verificare;
        for (int i = 0; i < x; i++)
        {
            int* forma_noua = new int[grad_polinom + 1];
            int k = grad_polinom;

            verificare = vector_div[i] * a.get_element(grad_polinom);
            forma_noua[k--] = a.get_element(grad_polinom);
            for (int j = grad_polinom - 1; j >= 0; j--)
            {
                int y = a.get_element(j);
                verificare = verificare + y;
                forma_noua[k--] = verificare;
                verificare = verificare * vector_div[i];
            }
            if (verificare == 0)
            {
                if (vector_div[i] > 0)
                    cout << "(x-" << vector_div[i] << ")(";
                else
                    cout << "(x+" << (-1) * vector_div[i] << ")(";
                for (int j = grad_polinom; j >= 1; j--)

                {
                    if (forma_noua[j] > 0 && j != grad_polinom)
                        cout << "+" << (double)forma_noua[j] / numitor_max;
                    else
                        if (forma_noua[j] != 0)
                            cout << (double)forma_noua[j] / numitor_max;
                    if (j - 1 > 1 && forma_noua[j] != 0)
                        cout << "x^" << j - 1;
                    else
                        if (j - 1 == 1 && forma_noua[j] != 0)
                            cout << "x";

                }
                cout << ")" << endl;
                break;
            }
            delete[] forma_noua;
        }
        if (verificare != 0)
            cout << "Polinomul nu are radacini intregi/este ireductibil (cu algoritmul lui  Horner)." << endl;

        delete[]vector_div;
    }
    else
    {
        int i = 1;

        while (a.get_element(i) == 0 && i < grad_polinom)
            i++;
        if (i != grad_polinom)
        {
            cout << "x";
            if (i != 1)
                cout << "^" << i << "(";
            else
                cout << "(";
            for (int j = grad_polinom; j >= i; j--)
            {
                if (a.get_element(j) > 0 && j != grad_polinom)
                    cout << "+" << (double)a.get_element(j) / numitor_max;
                else
                    if (a.get_element(j) != 0)
                        cout << (double)a.get_element(j) / numitor_max;
                if (j - i > 1 && a.get_element(j) != 0)
                    cout << "x^" << j - i;
                else
                    if (j - i == 1 && a.get_element(j) != 0)
                        cout << "x";

            }
            cout << ")" << endl;
        }
        else
            cout << a.get_element(grad_polinom) << "x^" << grad_polinom << endl;
    }

}

void Polinom_reductibil::citire(istream& in)
{
    Polinom::citire(in);

}

void Polinom_reductibil::afisare(ostream& out)
{
    Polinom::afisare(out);
    out << endl;
    out << endl;
    out << "S-a incercat scrierea ca produs de doua polinoame/factorul comun.\nRezultatul este urmatorul:\n";
}
istream& operator>>(istream& in, Polinom_reductibil& p)
{
    p.citire(in);
    return in;

}
ostream& operator<<(ostream& out, Polinom_reductibil& p)
{
    if (typeid(p) == typeid(Polinom_reductibil))
    {
        p.afisare(out);
        decompunere_polinom(p);
        out << endl;
    }
    return out;
}


Polinom_reductibil::~Polinom_reductibil()
{

}
void tip(Polinom*& a, int i, int optiune)
{


    if (optiune == 1)
    {
        a = new Polinom_ireductibil();
        cin >> *a;
        //cout << (*dynamic_cast<Polinom_ireductibil*>(a));
    }
    else
        if (optiune == 2)
        {
            a = new Polinom_reductibil();
            cin >> *a;
           // cout << (*dynamic_cast<Polinom_reductibil*>(a));
        }
}


int main()
{
    cout << "\n Lacatus Catalin-Petru Grupa 134- Proiect 2 ~~TEMA 13 POLINOAME ~~ : \n";
    cout << "\n\t MENIU:";
    cout << "\n============================================================================================\n";
    Polinom** v;
    int n=0;
    int alegere;
    bool ok=true;
    while(ok==true)
    {   cout<<endl;
        cout<< "Apasa (1) pentru a citi si a afisa un polinom. " << endl;
        cout<< "Apasa (2) pentru a citi si a verifica daca un polinom este ireductibil cu criteriul lui Eisenstein. " << endl;
        cout<< "Apasa (3) pentru a citi si a afisa polinomul/mesaj(in caz contrar) ca produs de doua polinoame(Heron)/cu metoda factorului comun.  " << endl;
        cout<< "Apasa (4) pentru a se afisa cate obiecte de tip polinom ati creat." << endl;
        cout<< "Apasa (5) pentru a citi, memora si a afisa n polinoame reductibile/ireductibile." << endl;
        cout<< "Apasa (6) pentru a eveidentia conceptul de downcasting pe un obiect. " << endl;
        cout<< "Apasa (7) pentru a iesi din program." << endl;
        cout<< "Optiunea dumneavoastra este:";
        cin>>alegere;
        cout<<endl;

  switch (alegere)
  {
      case 1:{
           Polinom p;
           cin>>p;
           cout<<p<<endl;
           cout<<"\n=============================================================================================\n";
           break;
        }

        case 2:{
            Polinom_ireductibil p;
            cin>>p;
            cout<<p<<endl;
            cout<<"\n=============================================================================================\n";
            break;
        }
        case 3:{
            Polinom_reductibil p;
            cin>>p;
            cout<<p<<endl;
            cout<<"\n=============================================================================================\n";
            break;

        }
        case 4:{
            if(Polinom::Numar_Obiecte()==0)
                cout<<"Pana acum nu ati creat niciun obiect de tip polinom.\nApasati din nou optiunea (4) dupa ce creati niste obiecte de tip polinom.\n";
            else
                cout<<"Pana acum ati creat "<<Polinom::Numar_Obiecte()<<" obiecte de tip polinom."<<endl;


             cout<<"\n=============================================================================================\n";
             break;
        }


   case 5:{

    cout << "Introduceti numarul de obiecte:";
    cin >> n;
    while (n < 1)
    {   cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "Numarul de obiecte trebuie sa fie >= 1.";
        cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout<<"Introduceti numarul de obiecte:";
        cin >> n;
    }
     v = new Polinom * [n];
    for (int i = 0; i < n; i++)
    {
        int optiune;
        cout << "____________________________________________________________________________________________\n\n";
        cout<<"Polinomul "<<i+1<<" :"<<endl;
        cout << "Apasa 1 pentru a citi un polinom ireductibil si a verifica daca este ireductibil cu criteriul lui Eisenstein.\n";
        cout << "Apasa 2 pentru a citi un polinom reductibil si a incerca metoda lui Horner/a factorului comun.\n";
        cout << "Optiunea dumneavoastra este:";
        cin >> optiune;
        while (optiune != 1 && optiune != 2)
        {   cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << "\nOptiunea dumneavoastra nu este valida. Introduceti 1 sau 2.\n";
            cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << "Optiunea dumneavoastra este:";
            cin >> optiune;
            cout << endl;
        }
        if (optiune == 1 || optiune == 2)
            tip(v[i], i, optiune);

    }

        for (int i = 0; i < n; i++)
        {
            cout << "\n________________________________________________________________________\n";
            cout<<"Polinomul "<<i+1<<" din vectorul de polinoame creat:"<<endl;
            if (typeid(*v[i]) == typeid(Polinom_ireductibil))
              cout << "\n" << (*dynamic_cast<Polinom_ireductibil*>(v[i]));
            else
                if (typeid(*v[i]) == typeid(Polinom_reductibil))
                    cout << "\n" << (*dynamic_cast<Polinom_reductibil*>(v[i]));
        }
         cout<<"\n=============================================================================================\n";
         break;
   }
   case 6:{
        int op;
        cout << "Apasa 1 pentru a citi un polinom ireductibil.\n";
        cout << "Apasa 2 pentru a citi un polinom reductibil.\n";
        cout << "Optiunea dumneavoastra este:";
        cin >> op;
        while (op != 1 && op != 2)
        {   cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << "\nOptiunea dumneavoastra nu este valida. Introduceti 1 sau 2.\n";
            cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << "Optiunea dumneavoastra este:";
            cin >> op;
            cout << endl;
        }
        if(op==1)
        {
            Polinom_ireductibil* b =(Polinom_ireductibil*) new Polinom();
            cin >> *b;
            cout << (*dynamic_cast<Polinom*>(b));
        }
        else
        {
            Polinom_reductibil* b =(Polinom_reductibil*) new Polinom();
            cin >> *b;
            cout << (*dynamic_cast<Polinom*>(b));
        }
        cout<<"\n=============================================================================================\n";

            break;
   }
           case 7:{
                 cout<<"\n=============================================================================================\n";
                ok=false;
                break;

           }


  }
}


cout<<"O zi buna! :))))))))"<<endl;



    return 0;
}
