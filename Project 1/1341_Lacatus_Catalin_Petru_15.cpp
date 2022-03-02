#include <iostream>
#include<stdio.h>
#include<math.h>
using namespace std;

class  Matrice {
private:
    int nr_linii;
    int nr_coloane;
    double matrice[100][100];

public:
    Matrice();///Constructor de initializare fara parametrii
    Matrice(int, int, double);///Constructor de initializare cu parametrii
    Matrice(int, int);///Construct de initializare cu 2 parametrii
    Matrice(Matrice&);///Constructor de copiere
    ~Matrice();
    void set_nr_linii(int);///set
    void set_nr_coloane(int);///set
    void set_valoare(int, int, double);///set
    int get_nr_linii() { return nr_linii; };///get
    int get_nr_coloane() { return nr_coloane; };///get
    double get_valoare(int, int);///get
    void citire(istream& in);
    void afisare(ostream& out);
    friend istream& operator>>(istream& in, Matrice& m);  ///supraincarcare pe >>
    friend ostream& operator<<(ostream& out, Matrice& m); ///supraincarcare pe <<
    void reactualizare(int, int, double);///metoda publica
    Matrice& operator=(Matrice& m);
    friend Matrice& operator+(Matrice& m1, Matrice& m2); ///supraincarcare operator +
    friend Matrice& operator-(Matrice& m1, Matrice& m2); ///supraincarcare operator -
    friend Matrice& operator*(Matrice& m1, Matrice& m2);///supraincarcare operator *
    friend Matrice& operator==(Matrice& m1, Matrice& m2);///supraincarcare operator ==
    friend int afla_nr_linii(double );///functie friend
    friend int afla_nr_coloane(double);///functie friend
    friend int afla_nr_elemente_matrice(double);
};

Matrice::Matrice() {
    this->nr_linii = 0;
    this->nr_coloane = 0;
}

Matrice::Matrice(int nr_linii, int nr_coloane, double el) { ///initializare
    this->nr_linii = nr_linii;
    this->nr_coloane = nr_coloane;

    for (int i = 0; i < nr_linii; i++)
        for (int j = 0; j < nr_coloane; j++)
            matrice[i][j] = el;
}

Matrice::Matrice(int nr_linii, int nr_coloane) { ///initializare
    this->nr_linii = nr_linii;
    this->nr_coloane = nr_coloane;
    for (int i = 0; i < nr_linii; i++)
        for (int j = 0; j < nr_coloane; j++)
            matrice[i][j] = 0;

}

Matrice::Matrice(Matrice& m) {  ///copiere
    this->nr_linii = m.nr_linii;
    this->nr_coloane = m.nr_coloane;
    for (int i = 0; i < nr_linii; i++)
        for (int j = 0; j < nr_coloane; j++)
            this->matrice[i][j] = m.matrice[i][j];
}

Matrice::~Matrice() {///destructor
    this->nr_linii = 0;
    this->nr_coloane = 0;
}

void Matrice::set_nr_linii(int nr_l) {///set
    nr_linii = nr_l;
}

void Matrice::set_nr_coloane(int nr_c) {///set
    nr_coloane = nr_c;
}

void Matrice::set_valoare(int x,int y, double z) {////set
    matrice[x][y] = z;
}

double Matrice::get_valoare(int x, int y) {

     return matrice[x][y];
}

void Matrice::citire(istream& in) {
    cout << "Introduceti numarul de linii al matricei:";
    in >> nr_linii;

    if(nr_linii<=0)
       while(nr_linii<=0){
          cout<<"Numarul de linii nu este valid. Introduceti numarul de linii al matricei:";
          in>>nr_linii;
    }

    cout << "Introduceti numarul de coloane al matricei:";
    in >> nr_coloane;

    if(nr_coloane<=0)
       while(nr_coloane<=0){
          cout<<"Numarul de coloane nu este valid. Introduceti numarul de linii al matricei:";
          in>>nr_coloane;
    }
    cout << "Introduceti elementele matricei:" << endl;
    for (int i = 0; i < nr_linii; i++)
        for (int j = 0; j < nr_coloane; j++)
        {
            cout << "matrice[" << i << "][" << j << "]=";
            in >> matrice[i][j];
        }
}

istream& operator>>(istream& in, Matrice& m) {
    m.citire(in);
    return in;
}

void Matrice::afisare(ostream& out) {
    for (int i = 0; i < nr_linii; i++)
    {
        for (int j = 0; j < nr_coloane; j++)
            cout << matrice[i][j] << " ";
        cout << endl;
    }
}

ostream& operator<<(ostream& out, Matrice& m) {
    m.afisare(out);
    return out;
}

void Matrice::reactualizare(int nr_l, int nr_c, double z) {
    nr_linii = nr_l;
    nr_coloane = nr_c;
    for (int i = 0; i < nr_linii; i++)
        for (int j = 0; j < nr_coloane; j++)
            matrice[i][j] = z;
}

Matrice& Matrice::operator=( Matrice& m) {
    if (this == &m)
    return *this;
     nr_linii = m.nr_linii;
     nr_coloane = m.nr_coloane;
    for (int i = 0; i < nr_linii; i++)
        for (int j = 0; j < nr_coloane; j++)
             matrice[i][j] = m.matrice[i][j];
    return *this;
}

inline Matrice& operator+(Matrice& M1, Matrice& M2) {
    Matrice* M = new Matrice;
    M->nr_linii = M1.nr_linii;
    M->nr_coloane = M1.nr_coloane;
    for (int i = 0; i < M1.nr_linii; i++)
        for (int j = 0; j < M1.nr_coloane; j++)
              M->matrice[i][j] = M1.matrice[i][j];
    if (M1.nr_linii == M2.nr_linii && M1.nr_coloane == M2.nr_coloane)
    {
        for (int i = 0; i < M1.nr_linii; i++)
            for (int j = 0; j < M1.nr_coloane; j++)
                M->matrice[i][j] += M2.matrice[i][j];

        return *M;
    }
    else {
        cout <<"Nu se poate efectua operatia de scadere, deoarece dimensiunile matricelor nu respecta proprietatile matematice." << endl;
        M->nr_coloane = 0;
        return *M;
    }
}

inline Matrice& operator-(Matrice& M1, Matrice& M2) {
    Matrice* M = new Matrice;
    M->nr_linii = M1.nr_linii;
    M->nr_coloane = M1.nr_coloane;
    for (int i = 0; i < M1.nr_linii; i++)
        for (int j = 0; j < M1.nr_coloane; j++)
            M->matrice[i][j] = M1.matrice[i][j];
    if ((M1.nr_linii == M2.nr_linii) && (M1.nr_coloane == M2.nr_coloane))
    {
        for (int i = 0; i < M1.nr_linii; i++)
            for (int j = 0; j < M1.nr_coloane; j++)
                M->matrice[i][j] -= M2.matrice[i][j];

        return *M;

    }
    else {
        cout <<"Nu se poate efectua operatia de scadere, deoarece dimensiunile matricelor nu respecta proprietatile matematice." << endl;
        M->nr_coloane = 0;
        return *M;
         }

}

inline Matrice& operator*(Matrice& M1, Matrice& M2) {
    Matrice* M = new Matrice;
    if (M1.nr_coloane == M2.nr_linii) {
        M->nr_linii = M1.nr_linii;
        M->nr_coloane = M2.nr_coloane;
        for (int i = 0; i < M1.nr_linii; i++)
            for (int j = 0; j < M2.nr_coloane; j++) {
                M->matrice[i][j] = 0;
                for (int k = 0; k < M2.nr_linii; k++)
                    M->matrice[i][j] += M1.matrice[i][k] * M2.matrice[k][j];
            }
        return *M;
    }
    else
    {
        cout << "Nu se poate efectua operatia de inmultire, deoarece dimensiunile matricelor nu respecta proprietatile matematice." <<endl;
        M->nr_coloane = 0;
        return *M;

    }
}

inline Matrice& operator==(Matrice& M1, Matrice& M2) {
    Matrice* M = new Matrice;
    if (M1.nr_coloane == M2.nr_coloane && M1.nr_linii == M2.nr_linii) {
        for(int i=0;i<M1.nr_linii;i++)
            for(int j=0;j<M1.nr_coloane;j++)
                if(M1.matrice[i][j]!=M2.matrice[i][j])
                { cout << "Matricele nu sunt egale." << endl;
                return *M;
                }
        {
            cout << "Da, matricele sunt egale." << endl;
            return *M;
        }
    }
    else
    {
        cout << "Matricele nu sunt egale." << endl;
        return *M;
    }
}
int afla_nr_linii(Matrice& M1) {
    return M1.get_nr_linii();
}
int afla_nr_coloane(Matrice& M1) {
    return M1.get_nr_coloane();
}
int afla_nr_elemente_matrice(Matrice& M1) {
    int nr_el = afla_nr_linii(M1) * afla_nr_coloane(M1);
    return nr_el;
}


int main()
{
        cout << "\n Lacatus Catalin-Petru Grupa 134- Proiect -  Clasa Matrice : \n";
        cout << "\n\t MENIU:";
        cout << "\n===========================================\n";
        cout << "\n======OBSERVATIE!!   A->PRIMA MATRICE, B->A DOUA MATRICE======"<<endl;
        cout << "Citeste si afiseaza doua matrice: " << endl;
        ///A->prima matrice;
        ///B->a doua matrice;

        Matrice A, B;
        cin >> A;
        cout << endl;
        cout <<A<<endl;
        cin >> B;
        cout << endl;
        cout << B<<endl;
        cout << "\n===========================================\n";
        cout<< "\n\t APLICATII MATRICE \n";
        cout << endl;

    int alegere;
    bool ok = true;
    while (ok != false) {


        cout << "Apasa (1) pentru a calcula suma a doua matrice. " << endl;
        cout << "Apasa (2) pentru a calcula diferenta a doua matrice. " << endl;
        cout << "Apasa (3) pentru a calcula  produsul a doua matrice.  " << endl;
        cout << "Apasa (4) pentru a testa egalitatea intre doua matrici." << endl;
        cout << "Apasa (5) pentru a si reactualiza matricea A si B." << endl;
        cout<<  "Apasa (6) pentru a se afisa nr de linii si coloane al unei matrice. " << endl;
        cout << "Apasa (7) pentru a schimba valoarea unui element de pe o pozitie din matricea(B)." << endl;
        cout << "Apasa (8) pentru a rezolva o ecuatie de tipul ''E * X + F = 0'' ;" << endl;  ///eu o sa folosesc E,F,X->MATRICE(Pentru ca am folosit deja A,B)
        cout << "Apasa (9) pentru a iesi din meniu;" << endl;
        cout << "Optiunea dumneavoastra este:";
        cin >> alegere;
        cout << endl;

        switch (alegere) {
        case 1: {
            Matrice C;
            C = A + B;
            if (afla_nr_coloane(C) != 0)
            {
                cout << "Noua matrice dupa adunare este :" << endl;
                cout << C << endl;
            }
            break;
        }

        case 2: {
            Matrice D;
            int efectueaza;
            cout << "    Alege 1 daca vrei sa scazi A-B, unde A si B->matrice."<<endl;
            cout << "    Alege 2 daca vrei sa scazi B-A, unde A si B->matrice." << endl;
            cout << "Optiunea dumneavoastra este:";
            cin >> efectueaza;
            cout << endl;
            if (efectueaza == 1)
                D = A - B;
            else
                D = B - A;
            if (afla_nr_coloane(D) != 0)
            {
                cout <<"Noua matrice dupa scadere este :" << endl;
                cout << D << endl;
            }
            cout << endl;
            break;
        }

        case 3: {
            Matrice C;
            C = A * B;
            if (afla_nr_coloane(C) != 0)
            {
                cout << "Noua matrice dupa inmultire este :" << endl;
                cout << C << endl;
            }
            cout << endl;

            break;
        }

        case 4: {
            A == B;
            cout << endl;
            break;
        }

        case 5: {
            int n, m;
            double x;
            cout << "  Introduceti numarul de linii al matricei pt reactualizare(A):";
            cin >> n;
            cout << endl;
            cout << "  Introduceti numarul de coloane al matricei pt reactualizare(A):";
            cin >> m;
            cout << "  Introduceti elementul cu care vor fi egale toate componentele matricei pt reactualizare(A):";
            cin >> x;
            cout << endl;
            A.reactualizare(n, m, x);
            cout << "Matricea reactualizata(A):" << endl;
            cout << A;
            cout << endl;

            int a, b;
            double c;
            cout << "  Introduceti numarul de linii al matricei pt reactualizare(B):";
            cin >> a;
            cout << endl;
            cout << "  Introduceti numarul de coloane al matricei pt reactualizare(B):";
            cin >> b;
            cout << "  Introduceti elementul cu care vor fi egale toate componentele matricei pt reactualizare(B):";
            cin >> c;
            cout << endl;
            B.reactualizare(a, b, c);
            cout << "Matricea reactualizata(B):" << endl;
            cout << B;
            cout << endl;
            break;
        }

        case 6: {
            int efectueaza1;
            cout << "    Alege 1 daca vrei sa obtii numarul liniilor si coloanelor primei matrice(A)." << endl;
            cout << "    Alege 2 daca vrei sa obtii numarul liniilor si coloanelor celei de-a doua matrice(B)." << endl;
            cout << "Optiunea dumneavoastra este:"<<endl;
            cin >> efectueaza1;
            if (efectueaza1 == 1)
            {
                cout <<"Numarul liniilor matricei (A) este: "<< afla_nr_linii(A) << endl;
                cout <<"Numarul coloanelor matricei (A) este: " << afla_nr_coloane(A) << endl;
            }
            else
            {
                cout << "Numarul liniilor matricei (B) este: " << afla_nr_linii(B) << endl;
                cout << "Numarul coloanelor matricei (B) este: " << afla_nr_coloane(B) << endl;
            }

            cout << endl;
            break;
        }

        case 7: {
            int n,m;
            double z;
            cout << "  Introduceti linia:";
            cin >> n;
            cout << "Introduceti coloana:";
            cin >> m;
            cout << "Introduceti elementul:";
            cin >> z;
            cout << endl;
            if (n <= B.get_nr_linii() && m <= B.get_nr_coloane())
            {
                B.set_valoare(n, m, z);
                cout << endl;
                cout << B;
                cout << endl;
            }
            else
            {
                cout << "Nu se poate!" << endl;
                cout << endl;
            }
            break;
        }

        case 8: {

            int n1, m1;
            double x1,x2;
            cout << "  Introduceti numarul de linii al matricei (E,F):";
            cin >> n1;
            cout << endl;
            cout << "  Introduceti numarul de coloane al matricei (E,F):";
            cin >> m1;
            cout << "  Introduceti elementul cu care vor fi egale toate componentele matricei (E):";
            cin >> x1;
            cout << endl;
            cout << "  Introduceti elementul cu care vor fi egale toate componentele matricei (F):";
            cin >> x2;
            Matrice E(n1, m1, x1), F(n1, m1, x2), X(0,0,0);
            double n = F.get_valoare(0, 0)/ (double(E.get_nr_coloane())*E.get_valoare(0,0));
            X.reactualizare(n1, m1, (-n));
            cout << X;
            cout << endl;

        }

        case 9: {

            return 0;
         }

       }
   }

    return 0;
}
