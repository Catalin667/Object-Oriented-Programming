#include<iostream>
#include<string>
#include <unordered_map>
#include<vector>
#include<typeinfo>
using namespace std;

class Data {
private:
	int zi;
	string luna;
	int an;
public:
	friend class Plata;
	Data();///constructor de initializare fara parametrii
	Data(int, string, int);///constructor de initializare cu parametrii
	Data(const Data&);///constructor de copiere
	void set_zi(int z) { zi = z; };
	void set_luna(string l) { luna = l; };
	void set_an(int a) { an = a; };
	int get_zi() { return zi; };
	string get_luna() { return luna; };
	int get_an() { return an; };
	~Data();
	void citire(istream& in);
	void afisare(ostream& out);
	friend istream& operator >>(istream&, Data&);
	friend ostream& operator <<(ostream&, Data&);
	Data& operator = (const Data& d);///supraincarcare pe operatorul operatorul egal

};
Data::Data() {
	this->an = 0;
	this->luna = "";
	this->zi = 0;
}
Data::Data(int zi, string luna, int an)
{
	if (zi != 0 || luna != "" || an != 0)
	{
		try {
			if (zi > 31 || zi < 1)
				throw 1;
			if (luna != "ianuarie" && luna != "februarie" && luna != "martie" && luna != "aprilie" && luna != "mai" &&
				luna != "iunie" && luna != "iulie" && luna != "august" && luna != "septembrie" && luna != "octombrie" && luna != "noiembrie" && luna != "decembrie")
				throw 2;
			if (an < 1950 || an>2021)
				throw 3;
		}
		catch (int x)
		{
			if (x == 1)
			{
				cout << "Eroare constructor, nu exista aceasta zi din luna! \n";
				exit(EXIT_FAILURE);
			}
			if (x == 2)
			{
				cout << "Eroare constructor, nu exista aceasta luna din an! \n";
				exit(EXIT_FAILURE);
			}
			if (x == 3)
			{
				cout << "Eroare constructor, anul trebuie sa fie in intervalul [1950,2021]! \n";
				exit(EXIT_FAILURE);
			}

		}

	}
	this->zi = zi;
	this->luna = luna;
	this->an = an;

}

Data::Data(const Data& d)
{
	this->zi = d.zi;
	this->luna = d.luna;
	this->an = d.an;
}
Data::~Data() {

	this->zi = 0;
	this->luna = "";
	this->an = 0;
}
void Data::citire(istream& in)
{
	cout << "Introduceti data dorita:\n";
	cout << " Introduceti anul:";
	in >> an;
	while (an < 1950 || an>2021)
	{
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << "\nNu ati introdus un an valid.Introduceti un an din intervalul [1950,2021] .\n";
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << " Introduceti anul:";
		in >> an;
	}
	cout << " Introduceti luna:";
	in >> luna;
	while (luna != "ianuarie" && luna != "februarie" && luna != "martie" && luna != "aprilie" && luna != "mai" &&
		luna != "iunie" && luna != "iulie" && luna != "august" && luna != "septembrie" && luna != "octombrie" && luna != "noiembrie" && luna != "decembrie")
	{
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << "\nNu ati introdus o luna valida.Introduceti o luna din an existenta.Luna se scrie cu litere mici in intregime!\n";
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << " Introduceti luna:";
		in >> luna;
	}
	cout << " Introduceti ziua:";
	in >> zi;
	while (zi < 1)
	{
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << "\nAceasta zi nu exista in luna.Introduceti o noua zi valida.\n";
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << " Introduceti ziua:";
		in >> zi;
	}
	while ((luna == "ianuarie" || luna == "martie" || luna == "mai" || luna == "iulie" || luna == "august" || luna == "octombrie"
		|| luna == "decembrie") && (zi > 31))
	{
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << "\nAceasta zi nu exista in luna.Introduceti o noua zi valida.\n";
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << " Introduceti ziua:";
		in >> zi;
	}
	while ((luna == "aprilie" || luna == "iunie" || luna == "septemrbie" || luna == "noiembrie") && (zi > 30))
	{
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << "\nAceasta luna are doar 30 de zile.Introduceti un noua zi valida pentru aceasta luna.\n";
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << " Introduceti ziua:";
		in >> zi;
	}
	while (luna == "februarie" && an % 4 != 0 && zi > 28)
	{
		if (zi == 29)
		{
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			cout << "\nAceasta luna are doar 28 de zile, deoarece anul " << an << " nu este este bisect.Introduceti un noua zi valida pentru aceasta luna.\n";
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			cout << " Introduceti ziua:";
			in >> zi;
		}
		else
		{
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			cout << "\nLuna februarie are 28/29 de zile.Introduceti un noua zi valida pentru aceasta luna.\n";
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			cout << " Introduceti ziua:";
			in >> zi;
		}

	}
	while (luna == "februarie" && an % 4 == 0 && zi > 29)
	{
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << "\nAceasta luna are 29 de zile, deoarece anul " << an << " este este bisect.Introduceti un noua zi valida pentru aceasta luna.\n";
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << " Introduceti ziua:";
		in >> zi;
	}

}
void Data::afisare(ostream& out)
{
	out << "\n";
	out << "DATA: ";
	out << zi;
	out << ",";
	out << luna;
	out << ",";
	out << an;
}
istream& operator>>(istream& in, Data& d)
{
	d.citire(in);
	return in;
}
ostream& operator<<(ostream& out, Data& d)
{
	d.afisare(out);
	return out;
}
Data& Data::operator = (const Data& d) {
	if (this != &d)
	{
		zi = d.zi;
		luna = d.luna;
		an = d.an;

	}
	return *this;
}
class Plata {
protected:
	Data data;
	double suma;
	static int nr_plati;
	int id_plata;
public:
	Plata();
	Plata(Data, double);
	Plata(const Plata&);
	virtual ~Plata();
	virtual void citire(istream& in);
	virtual void afisare(ostream& out);
	friend istream& operator>>(istream&, Plata&);
	friend ostream& operator<<(ostream&, Plata&);
	Plata& operator=(const Plata& p);
	static int Nr_Plati() { return nr_plati; }

};
int Plata::nr_plati;///declar variabila
Plata::Plata() {
	nr_plati++;
    id_plata=nr_plati/2;
	suma = 0;
}
Plata::Plata(Data d, double s) {
	nr_plati++;
	id_plata = nr_plati/2;

	if (s != 0) {
		try {
			if (s < 0)
				throw s;
		}
		catch (double x)
		{
			cout << "Eroare constructor, suma trebuie sa fie pozitiva! \n";
			exit(EXIT_FAILURE);
		}
	}
	suma = s;

}
Plata::Plata(const Plata& p) {

	this->data = p.data;
	this->suma = p.suma;

}

void Plata::citire(istream& in) {

	cout << "Introduceti suma platita:";
	in >> suma;
	while (suma <= 0)
	{
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << "\nSuma introdusa nu este valida.Introduceti un numar pozitiv mai mare decat 0!\n";
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << "Introduceti suma platita:";
		in >> suma;
	}
	in >> data;
}
void Plata::afisare(ostream& out) {


	out << "Suma platita: ";
	out << suma;
	out << data << "\n";

}
istream& operator>>(istream& in, Plata& p)
{
	p.citire(in);
	return in;
}
ostream& operator<<(ostream& out, Plata& p)
{
	p.afisare(out);
	return out;
}
Plata& Plata::operator = (const Plata& p) {
	if (this != &p)
	{
		data = p.data;
		suma = p.suma;
	}
	return *this;
}
Plata::~Plata()
{
	nr_plati--;
	suma = 0;

}
class Cash :public Plata {
public:
	Cash();
	Cash(Data, double);
	Cash(const Cash&);
	~Cash();
	void citire(istream& in);
	void afisare(ostream& out);
	friend istream& operator>>(istream&, Cash&);
	friend ostream& operator<<(ostream&, Cash&);
	Cash& operator=(const Cash& p);
};
Cash::Cash() :Plata() {

}
Cash::Cash(Data d, double s) : Plata(d, s) {

}
Cash::Cash(const Cash& c) : Plata(c) {

}
void Cash::citire(istream& in)
{
	Plata::citire(in);

}
void Cash::afisare(ostream& out)
{
	Plata::afisare(out);

}
istream& operator>>(istream& in, Cash& c)
{
	c.citire(in);
	return in;
}
ostream& operator<<(ostream& out, Cash& c)
{
	c.afisare(out);
	return out;

}
Cash& Cash::operator = (const Cash& c)
{

	if (this != &c)
		Plata::operator=(c);
	return *this;
}
Cash::~Cash() {

}
class Cec :public Plata
{
private:
	string nume_titular;
public:
	Cec();
	Cec(Data, double, string);
	Cec(const Cec&);
	~Cec();
	void citire(istream& in);
	void afisare(ostream& out);
	friend istream& operator>>(istream&, Cec&);
	friend ostream& operator<<(ostream&, Cec&);
	Cec& operator=(const Cec& p);
};
Cec::Cec() :Plata() {
	this->nume_titular = "";
}
Cec::Cec(Data d, double s, string nume_titular) : Plata(d, s) {
	if (nume_titular != "")
	{
		int poz_lib = 0;
		while (nume_titular[poz_lib] == ' ')
		{
			poz_lib++;
		}
		try {
			if (nume_titular[poz_lib] < 'A' || nume_titular[poz_lib]>'Z')
				throw 2;
			for (int i = poz_lib; i < nume_titular.length(); i++)
			{
				if (nume_titular[i] >= '0' && nume_titular[i] <= '9')
					throw 1;
				if (nume_titular[i] == ' ' && nume_titular[i + 1] != ' ' && (nume_titular[i + 1] < 'A' || nume_titular[i + 1]>'Z'))
					throw 2;
			}
		}
		catch (int x)
		{
			if (x == 1)
			{
				cout << "Eroare constructor, numele unei persoane nu poate contine cifre! \n";
				exit(EXIT_FAILURE);
			}
			else
				if (x == 2)
				{
					cout << "Eroare constructor, numele/prenumele unei persoane incepe cu litera mare! \n";
					exit(EXIT_FAILURE);
				}

		}
	}
	this->nume_titular = nume_titular;
}
Cec::Cec(const Cec& c) :Plata(c) {
	this->nume_titular = c.nume_titular;
}

Cec::~Cec()
{
	nume_titular = "";
}

void Cec::citire(istream& in)
{
	in.get();
	int ok = 0, poz_lib = 0;
	cout << "Introduceti numele titularului: ";
	getline(in, nume_titular);
	while (nume_titular[poz_lib] == ' ')
	{
		poz_lib++;
	}

	while (ok == 0)
	{
		ok = 1;
		try {
			if (nume_titular[poz_lib] < 'A' || nume_titular[poz_lib]>'Z')
			{

				ok = 0;
				throw 2;
			}
			for (int i = poz_lib + 1; i < nume_titular.length(); i++)
			{
				if (nume_titular[i] >= '0' && nume_titular[i] <= '9')
				{
					ok = 0;
					throw 1;
				}
				if (nume_titular[i] == ' ' && nume_titular[i + 1] != ' ' && (nume_titular[i + 1] < 'A' || nume_titular[i + 1]>'Z') && i != nume_titular.length())
				{
					ok = 0;
					throw 2;
				}
			}

		}
		catch (int x)
		{
			if (x == 1)
			{
				cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
				cout << "\nNumele unei persoane nu poate contine cifre.\n";
				cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			}
			else
				if (x == 2)
				{
					cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
					cout << "\nNumele/prenumele unei persoane incepe cu litera mare si nu contine cifre.\n";
					cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
				}
		}
		if (ok == 0)
		{
			cout << "Introduceti numele titularului:";
			getline(in, nume_titular);
		}
	}
	Plata::citire(in);
}
void Cec::afisare(ostream& out)
{
	out << "\n";
	out << "Numele titularului este: ";
	out << nume_titular;
	out << "\n";
	Plata::afisare(out);

}
istream& operator>>(istream& in, Cec& c)
{
	c.citire(in);
	return in;
}
ostream& operator<<(ostream& out, Cec& c)
{
	c.afisare(out);
	return out;
}
Cec& Cec::operator = (const Cec& c)
{

	if (this != &c)
		nume_titular = c.nume_titular;
	Plata::operator=(c);
	return *this;
}
class Card :public Plata
{
private:
	string nume_titular;
	string numar_card;
public:
	Card();
	Card(Data, double, string, string);
	Card(const Card&);
	string get_nume() { return nume_titular; };
	~Card();
	void citire(istream& in);
	void afisare(ostream& out);
	friend istream& operator>>(istream&, Card&);
	friend ostream& operator<<(ostream&, Card&);
	Card& operator=(const Card& p);
};
Card::Card() :Plata() {
	this->numar_card = "";
	this->nume_titular = "";
}
Card::Card(Data d, double s, string nume_titular, string numar_card) : Plata(d, s)
{
	if (nume_titular != "")
	{
		int poz_lib = 0;
		while (nume_titular[poz_lib] == ' ')
		{
			poz_lib++;
		}
		try {
			if (nume_titular[poz_lib] < 'A' || nume_titular[poz_lib]>'Z')
				throw 2;
			for (int i = poz_lib; i < nume_titular.length(); i++)
			{
				if (nume_titular[i] >= '0' && nume_titular[i] <= '9')
					throw 1;
				if (nume_titular[i] == ' ' && nume_titular[i + 1] != ' ' && (nume_titular[i + 1] < 'A' || nume_titular[i + 1]>'Z'))
					throw 2;
			}
		}
		catch (int x)
		{
			if (x == 1)
			{
				cout << "Eroare constructor, numele unei persoane nu poate contine cifre! \n";
				exit(EXIT_FAILURE);
			}
			else
				if (x == 2)
				{
					cout << "Eroare constructor, numele/prenumele unei persoane incepe cu litera mare! \n";
					exit(EXIT_FAILURE);
				}

		}
	}
	this->nume_titular = nume_titular;

	if (numar_card != "")
	{

		try {
			if (numar_card.length() != 16)
				throw 1;
			for (int i = 0; i < numar_card.length(); i++)
				if (numar_card[i] < '0' || numar_card[i]>'9')
					throw 2;
		}
		catch (int x)
		{
			if (x == 1)
			{
				cout << "Eroare constructor, numarul cardului trebuie sa fie de exact 16 cifre! \n";
				exit(EXIT_FAILURE);
			}
			else
				if (x == 2)
				{
					cout << "Eroare constructor, numarul cardului trebuie sa contina doar cifre! \n";
					exit(EXIT_FAILURE);
				}
		}
	}
}
Card::~Card()
{
	numar_card = "";
	nume_titular = "";
}
Card::Card(const Card& c) :Plata(c) {
	this->numar_card = c.numar_card;
	this->nume_titular = c.nume_titular;
}
void Card::citire(istream& in)
{
    in.get();
	int ok = 0, poz_lib = 0;
	cout << "Introduceti numele titularului: ";
	getline(in, nume_titular);
	while (nume_titular[poz_lib] == ' ')
	{
		poz_lib++;
	}

	while (ok == 0)
	{
		ok = 1;
		try {
			if (nume_titular[poz_lib] < 'A' || nume_titular[poz_lib]>'Z')
			{

				ok = 0;
				throw 2;
			}
			for (int i = poz_lib + 1; i < nume_titular.length(); i++)
			{
				if (nume_titular[i] >= '0' && nume_titular[i] <= '9')
				{
					ok = 0;
					throw 1;
				}
				if (nume_titular[i] == ' ' && nume_titular[i + 1] != ' ' && (nume_titular[i + 1] < 'A' || nume_titular[i + 1]>'Z') && i != nume_titular.length())
				{
					ok = 0;
					throw 2;
				}
			}

		}
		catch (int x)
		{
			if (x == 1)
			{
				cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
				cout << "\nNumele unei persoane nu poate contine cifre.\n";
				cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			}
			else
				if (x == 2)
				{
					cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
					cout << "\nNumele/prenumele unei persoane incepe cu litera mare si nu contine cifre.\n";
					cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
				}
		}
		if (ok == 0)
		{
			cout << "Introduceti numele titularului:";
			getline(in, nume_titular);
		}
	}
	Plata::citire(in);
	cout << "Introduceti numarul cardului(Acesta trebuie sa fie de exact 16 cifre):";
	in >> numar_card;
	int ok1 = 0;

	while (ok1 == 0)
	{
		ok1 = 1;
		try {
			if (numar_card.length() != 16)
			{
				ok1 = 0;
				throw 1;
			}
			for (int i = 0; i < numar_card.length(); i++)
				if (numar_card[i] < '0' || numar_card[i]>'9')
				{
					ok1 = 0;
					throw 2;
				}

		}
		catch (int x)
		{
			if (x == 1)
			{
				cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
				cout << "Numarul cardului trebuie sa fie de exact 16 cifre! \n";
				cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			}
			else
				if (x == 2)
				{
					cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
					cout << "Numarul cardului trebuie sa contina doar cifre! \n";
					cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
				}
		}
		if (ok1 == 0)
		{
			cout << "Introduceti numarul cardului(Acesta trebuie sa fie de exact 16 cifre!):";
			in >> numar_card;
			in.get();
		}
	}

}
void Card::afisare(ostream& out)
{
	out << "Numele titularului este: ";
	out << nume_titular;
	out << "\n";
	Plata::afisare(out);

	out << "Numarul cardului este: ";
	out << numar_card;
	out << "\n";

}
istream& operator>>(istream& in, Card& c)
{
	c.citire(in);
	return in;
}
ostream& operator<<(ostream& out, Card& c)
{
	c.afisare(out);
	return out;
}
Card& Card::operator = (const Card& c)
{

	if (this != &c)
	{
		numar_card = c.numar_card;
		nume_titular = c.nume_titular;
	}

	Plata::operator=(c);
	return *this;
}
template <class t> class Gestiune
{
private:
    int nr;
	unordered_map<int, t>gestiune;
	static int np;
public:
	const int get_nr() { return nr;};
	Gestiune(unordered_map<int, t>gestiune = {}, int nr = 0) {
		np++;
		this->nr = nr;
		if (nr != 0)
		{
			try
			{

				if (nr < 0)
					throw 1;

			}
			catch (int x)
			{
					cout << "Eroare constructor,numarul de chitante nu poate fi negativ ! \n";
					exit(EXIT_FAILURE);
			}
		}
		for (auto itr = gestiune.begin(); itr != gestiune.end(); itr++)
		{
			this->gestiune.insert({ itr->first,itr->second });
		}
	};

	Gestiune(const Gestiune& g) {
		this->nr = g.nr;
		for (auto itr = g.gestiune.begin(); itr != g.gestiune.end(); itr++)
			this->gestiune.insert({ itr->first,itr->second });


	};
	~Gestiune() {
		np--;
		gestiune.clear();
	};

	friend istream& operator>>(istream& in, Gestiune <t>& g) {
		cout << "Introduceti numarul de chitante pe care doriti sa le adaugati: ";
		in >> g.nr;
		int ok = 0;
		while (ok == 0)
		{
			ok = 1;
			try
			{
				if (g.nr < 0)
				{
					ok = 0;
					throw 2;
				}
			}
			catch (int x)
			{
				cout << "Numarul de chitante trebuie sa fie unul pozitiv. Introduceti un nou numar. \n";

			}
			if (ok == 0)
			{
				cout << "Introduceti numarul de chitante pe care doriti sa le adaugati: ";
				in >> g.nr;
				cout << "\n";
			}
		}


		for (int i = 0; i < g.nr; i++)
		{

			t p;
			cout << "\n========================================================================================\n\n";
			cout << "Introduceti datele platii chitantei cu numarul " << i + 1 << ":\n";
			in >> p;
			g.gestiune.insert({ i + 1,p });
		}

		return in;
	}
	friend ostream& operator<<(ostream& out, Gestiune<t>& g) {

		out << "\n========================================================================================\n\n";
		out << "Numarul total de plati este: " << g.nr << "\n";
		if (g.nr > 0)
		{
			out << "In gestiune se gasesc urmatoarele chitante de acest tip: \n";
			out << "\n----------------------------------------------------------------------------------------\n\n";
		}
		else
			if (typeid(g) == typeid(Plata))///nu inteleg de ce nu e cu not
			{
				out << "In gestiune nu s-a inregistrat nicio chitanta de acest tip. \n";
				out << "\n----------------------------------------------------------------------------------------\n\n";
			}
			else
			{
				out << "Nu s-a inregistrat nicio plata. \n";
				out << "\n----------------------------------------------------------------------------------------\n\n";
			}


		for (auto itr = g.gestiune.begin(); itr != g.gestiune.end(); itr++)
		{
			out << "Chitanta cu numarul " << itr->first << " are urmatoarele informatii: \n" << itr->second;
			out << "\n========================================================================================\n\n";
		}

		return out;

	}
	Gestiune& operator=(const Gestiune& g)
	{
		if (this != &g)
		{
			this->nr = g.nr;
			gestiune.clear();
			for (auto itr = g.gestiune.begin(); itr != g.gestiune.end(); itr++)
				this->gestiune.insert({ itr->first,itr->second });
		}

		return *this;
	}
	Gestiune& operator+=(t& nou)
	{
		this->gestiune.insert({ nr + 1,nou });
		this->nr++;
		return *this;
	}


};
template <class t> int Gestiune<t>::np;///declar variabila

template <> class Gestiune <Card>
{
private:
	vector<string>Nume_persoane;
	int nr;
public:
	const int get_nr() { return nr; };///o variabila care nu e const poate apela o functie const, dar invers nu
	Gestiune(vector < string>Nume_persoane = {}, int nr = 0)
	{
		this->nr = nr;
		if (nr != 0)
		{
			try
			{

				if (nr < 0)
					throw 1;

			}
			catch (int x)
			{
				cout << "Eroare constructor,numarul de chitante nu poate fi negativ ! \n";
				exit(EXIT_FAILURE);
			}
		}
		for (unsigned int i = 0; i < Nume_persoane.size(); i++) {
			this->Nume_persoane.push_back(Nume_persoane[i]);
		}
	};
	Gestiune(const Gestiune& g)
	{

		this->nr = g.nr;
		for (unsigned int i = 0; i < g.Nume_persoane.size(); i++) {
			this->Nume_persoane.push_back(g.Nume_persoane[i]);
		}
	};
	~Gestiune()
	{
		Nume_persoane.clear();
	};
	friend istream& operator>>(istream& in, Gestiune <Card>& g) {
		cout << "Introduceti numarul de chitante pe care doriti sa le adaugati: ";
		in >> g.nr;
		int ok = 0;
		while (ok == 0)
		{
			ok = 1;
			try
			{
				if (g.nr < 0)
				{
					ok = 0;
					throw 2;
				}
			}
			catch (int x)
			{
				cout << "Numarul de chitante trebuie sa fie unul pozitiv. Introduceti un nou numar. \n";

			}
			if (ok == 0)
			{
				cout << "Introduceti numarul de chitante pe care doriti sa le adaugati: ";
				in >> g.nr;
				cout << "\n";
			}
		}
		for (unsigned int i = 0; i < g.nr; i++)
		{

			Card p;
			cout << "\n========================================================================================\n\n";
			cout << "Introduceti datele platii chitantei pentru o plata de tip card cu numarul " << i + 1 << ":\n";
			in >> p;
			g.Nume_persoane.push_back(p.get_nume());
		}

		return in;
	}
	friend ostream& operator<<(ostream& out, Gestiune <Card>& g) {

			out << "\n========================================================================================\n\n";
			out << "Numarul clientilor care platesc cu cardul este: " << g.nr << "\n";
			if (g.nr >= 1)
			   out << "Persoanele care platesc cu cardul sunt:\n";
		for (unsigned int i = 0; i < g.nr; i++)
		{
			out << i + 1 << "." << g.Nume_persoane[i]<<"\n";
		}
		return out;
	}
		Gestiune& operator=(const Gestiune & g)
		{
			if (this != &g)
			{
				this->nr = g.nr;
				Nume_persoane.clear();
				for (unsigned int i = 0; i < g.nr; i++)
					this->Nume_persoane.push_back(g.Nume_persoane[i]);
			}

			return *this;
		}
		Gestiune& operator +=(Card& nou)
		{
			this->Nume_persoane.push_back(nou.get_nume());
			this->nr++;
			return *this;
		}
};
void tip(Plata*& a)
{
	int verif = 0;
	int optiune;
	cout << "Apasati (1) pentru a memora datele afenrente unei plati cash.\n";
	cout << "Apasati (2) pentru a memora datele afenrente unei plati de tip cec.\n";
	cout << "Apasati (3) pentru a memora datele afenrente unei plati cu card.\n";
	cout << "Optiunea dumneavoastra este: ";
	cin >> optiune;
	while (verif == 0)
	{
		try
		{
			verif = 1;
			if (optiune == 1)
			{
				a = new Cash();
				cin >> *a;

			}
			else
				if (optiune == 2)
				{
					a = new Cec();
					cin >> *a;

				}
				else
					if (optiune == 3)
					{
						a = new Card();
						cin >> *a;

					}
					else
						throw 1;
		}
		catch (int j)
		{
			verif = 0;
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			cout << "Apasati (1),(2) sau (3).";
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		}
		if (verif == 0)
		{

			cout << "Apasati (1) pentru a memora datele afenrente unei plati cash.\n";
			cout << "Apasati (2) pentru a memora datele afenrente unei plati de tip cec.\n";
			cout << "Apasati (3) pentru a memora datele afenrente unei plati cu card.\n";
			cout << "Optiunea dumneavoastra este: ";
			cin >> optiune;
		}
	}

}

int main()
{
	cout << "\n\t\t Lacatus Catalin-Petru Grupa 134- Proiect 3- FIRMA X \n";
	cout<<"\n!!OBSERVATIE!!->luna anului se scrie cu litere mici, in intregime\n";
	cout << "\n\t\t\t\t ~~MENIU~~";
	cout << "\n============================================================================================\n";


	vector<Plata*>v;
	Gestiune<Cash>plati_cash;
	Gestiune<Cec>plati_cec;
	Gestiune<Card>plati_card;
	int alegere,n=0;
	bool ok = true;
	while (ok == true)
	{
		cout << endl;
		cout << "Apasa (1)  pentru a citi,memora plati." << endl;
		cout << "Apasa (2)  pentru a afisa platile citite si memorate." << endl;
		cout << "Apasa (3)  pentru a introduce chitante pentru plata cash in gestiune. " << endl;
		cout << "Apasa (4)  pentru a introduce chitante pentru plata cu cec in gestiune. " << endl;
		cout << "Apasa (5)  pentru a introduce chitante pentru plata card in gestiune. " << endl;
		cout << "Apasa (6)  pentru a afisa informatiile si chitantele introduse pentru plata cash. " << endl;
		cout << "Apasa (7)  pentru a afisa informatiile si chitantele introduse pentru plata cu cec. " << endl;
		cout << "Apasa (8)  pentru a afisa informatiile si persoanele introduse care au platit cu cardul. " << endl;
		cout << "Apasa (9)  pentru a afisa numarul total de plati inregistrate in gestiune(Pe categorii)."<< endl;
		cout << "Apasa (10) pentru a inregistra in gestiune o noua plata de tip cec/card/cash" << endl;
		cout << "Apasa (11) pentru a iesi din program." << endl;
		cout << "Optiunea dumneavoastra este:";
		cin >> alegere;
		cout << endl;
		switch (alegere)
		{
		case 1:
		{
			int verif=0;
			cout << "Introduceti numarul de plati: ";
			cin >> n;
			while (verif == 0)
			{
				verif = 1;
				try {
					if (n == 0)
						throw 1;
					if (n < 0)
						throw 2;

				}
				catch (int x)
				{
					verif = 0;
					if (x == 1)
					{
						cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
						cout << "Cititi macar detaliile unei plati!\n";
						cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
					}
					else
						if (x == 2)
						{
							cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
							cout << "Numarul platilor nu poate fi negativ!\n";
							cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

						}
				}
				if (verif == 0)
				{
					cout << "Introduceti numarul de plati: ";
					cin >> n;
				}
			}

			for (int i = 0; i < n; i++)
			{
				v.push_back(new Plata);
				tip(v[i]);
			}

			break;

		}
		case 2:
		{
			if (n == 0)
				cout << "Nu ati memorat nicio plata.";
			else
			{
				cout << "\n----------------------------------------------------------------------------------------\n";
				cout << "Ati memorat " << n << " plati:\n";
				for (int i = 0; i < n; i++)
				{
					if (typeid(*v[i]) == typeid(Cash))
						cout << "\n" << (*dynamic_cast<Cash*>(v[i]))<<"\n";
					else
						if (typeid(*v[i]) == typeid(Cec))
							cout << "\n" << (*dynamic_cast<Cec*>(v[i])) << "\n";
						else
							if (typeid(*v[i]) == typeid(Card))
								cout << "\n" << (*dynamic_cast<Card*>(v[i])) << "\n";
				}
			}
			break;
		}
		case 3:
		{
			cin >> plati_cash;
			break;
		}
		case 4:
		{
			cin >> plati_cec;
			break;
		}
		case 5:
		{
			cin >> plati_card;
			break;
		}
		case 6:
		{
         cout << plati_cash;
		 break;
		}
		case 7:
		{
         cout << plati_cec;
		 break;
		}
		case 8:
		{
         cout << plati_card;
		 break;
		}
		case 9:
		{
			if (Plata::Nr_Plati() == 0)
				cout << "Pana acum nu ati inregistrat nicio plata.\n";
			else
				cout << "Pana acum ati inregistrat urm. nr. de plati in gestiune: "<< plati_cash.get_nr()+ plati_cec.get_nr()+ plati_card.get_nr() << endl;
			cout << "\n=============================================================================================\n";

			if (plati_cash.get_nr() == 0)
				cout << "Pana acum nu ati inregistrat nicio plata cash.\n";
			else
				cout << "Pana acum ati inregistrat " << plati_cash.get_nr() << " plati cash." << endl;
			cout << "\n=============================================================================================\n";

			if (plati_cec.get_nr() == 0)
				cout << "Pana acum nu ati inregistrat nicio plata de tip cec.\n";
			else
				cout << "Pana acum ati inregistrat " << plati_cec.get_nr() << " plati de tip cec." << endl;
			cout << "\n=============================================================================================\n";

			if (plati_card.get_nr() == 0)
				cout << "Pana acum nu ati inregistrat nicio plata de tip card.\n";
			else
				cout << "Pana acum ati inregistrat " << plati_card.get_nr() << " plati de tip card." << endl;
			cout << "\n=============================================================================================\n";


			break;
		}
		case 10:
		{
			int verif = 0;
			int optiune;
			cout << "Apasati (1) pentru a memora datele afenrente unei plati cash.\n";
			cout << "Apasati (2) pentru a memora datele afenrente unei plati de tip cec.\n";
			cout << "Apasati (3) pentru a memora datele afenrente unei plati cu card.\n";
			cout << "Optiunea dumneavoastra este: ";
			cin >> optiune;
			while (verif == 0)
			{
				try
				{
					verif = 1;
					if (optiune == 1)
					{
						Cash c;
						cin >> c;
						plati_cash += c;
					}
					else
						if (optiune == 2)
						{
							Cec c;
							cin >> c;
							plati_cec += c;

						}
						else
							if (optiune == 3)
							{
								Card c;
								cin >> c;
								plati_card += c;
							}
							else
								throw 1;
				}
				catch (int j)
				{
					verif = 0;
					cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
					cout << "Apasati (1),(2) sau (3).";
					cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
				}
				if (verif == 0)
				{

					cout << "Apasati (1) pentru a memora datele afenrente unei plati cash.\n";
					cout << "Apasati (2) pentru a memora datele afenrente unei plati de tip cec.\n";
					cout << "Apasati (3) pentru a memora datele afenrente unei plati cu card.\n";
					cout << "Optiunea dumneavoastra este: ";
					cin >> optiune;
				}
			}
			break;
		}
		case 11:
		{
			cout << "\n=============================================================================================\n";
			ok = false;
			break;
		}

		}
	}
	cout << "O zi buna! :))))))))" << endl;

	return 0;
}
