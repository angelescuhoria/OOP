#include <iostream>
#include <cstring>
#include <string>
#include <cctype>
#include <cmath>
#include <fstream>
#include <vector>
#include <list>
#include <iterator>
#include <unistd.h>

using namespace std;

class Employees
{
private:
    char* employee_name;
    bool working;
    char gender;
    char where_is_it_working[35];
    float salary;
    const int ID;
    static int number_of_employees;
    int age;
    int* weekdays;

public:
    char* getEmployeeName()
    {
        return this->employee_name;
    }
    void setEmployeeName(char* employee_name)
    {
        if (this->employee_name != nullptr) delete[] this->employee_name;
        this->employee_name = new char[strlen(employee_name) + 1];
        strcpy(this->employee_name, employee_name);
    }
    bool getWorking()
    {
        return this->working;
    }
    void setWorking(bool working)
    {
        this->working = working;
    }
    char getGender()
    {
        return this->gender;
    }
    void setGender(char gender)
    {
        this->gender = gender;
    }
    char* getWhereIsItworking()
    {
        return this->where_is_it_working;
    }
    void setWhereIsItworking(char where_is_it_working[35])
    {
        strcpy(this->where_is_it_working, where_is_it_working);
    }
    float getSalary()
    {
        return this->salary;
    }
    void setSalary(float salary)
    {
        this->salary = salary;
    }
    int getAge()
    {
        return this->age;
    }
    void setAge(int age)
    {
        this->age = age;
    }
    int* getWeekdays()
    {
        return this->weekdays;
    }
    void setWeekdays(int* weekdays)
    {
        if (this->weekdays != nullptr) delete[] this->weekdays;
        this->weekdays = new int[5];
        for (int i = 0; i < 5; i++) this->weekdays[i] = weekdays[i];
    }


    Employees(char* employee_name, char gender, int age, int* weekdays, bool working, float salary, char where_is_it_working[35]);
    Employees(char* employee_name, char gender, int age);
    Employees(const Employees &emp);
    Employees();
    ~Employees();

    void toString();

    Employees &operator = (const Employees &emp)
    {
        if (this != &emp)
        {
            if (this->employee_name != nullptr) delete[] this->employee_name;
            this->employee_name = new char[strlen(emp.employee_name) + 1];
            strcpy(this->employee_name, emp.employee_name);
            this->gender = emp.gender;
            this->age = emp.age;
            if (this->weekdays != nullptr) delete[] this->weekdays;
            this->weekdays = new int[5];
            for (int i = 0; i < 5; i++) this->weekdays[i] = emp.weekdays[i];
            this->working = emp.working;
            this->salary = emp.salary;
            strcpy(this->where_is_it_working, emp.where_is_it_working);
        }
        return *this;
    }

    friend istream &operator >> (istream &input, Employees &Emp)
    {
        int i;
        char copy[25];
        cout << "Introduceti numele: ";
        input >> copy;
        if (Emp.employee_name != nullptr) delete[] Emp.employee_name;
        Emp.employee_name = new char[strlen(copy) + 1];
        strcpy(Emp.employee_name, copy);
        cout << "Introduceti varsta: ";
        input >> Emp.age;
        try
        {
            if (Emp.age < 0) throw 7;
            else
            {
                cout << "Gen M / F: ";
                input >> Emp.gender;
                Emp.gender = toupper(Emp.gender);
                while (Emp.gender != 'M' && Emp.gender!= 'F')
                {
                    cout << "Gresit! Introduceti M sau F: ";
                    input >> Emp.gender;
                    Emp.gender = toupper(Emp.gender);
                }
                cout << "Unde lucreaza angajatul (Departamentul de Finante (DF) / Departamentul de Operatiuni (DO)): ";
                input >> Emp.where_is_it_working;
                while (strcmp(Emp.where_is_it_working, "DF") && strcmp(Emp.where_is_it_working, "DO") && strcmp(Emp.where_is_it_working, "df") && strcmp(Emp.where_is_it_working, "do"))
                {
                    cout << "Gresit! Introduceti DF sau DO: ";
                    input >> Emp.where_is_it_working;
                }
                cout << "Introduceti salariul angajatului: ";
                input >> Emp.salary;
                cout << "Angajatul lucreaza in aceasta saptamana sau nu? Introduceti 1 sau 0: ";
                input >> Emp.working;
                if (Emp.working == 1)
                {
                    if (Emp.weekdays != nullptr) delete[] Emp.weekdays;
                    Emp.weekdays = new int[5];
                    for (i = 0; i < 5; i++)
                    {
                        cout << "Lucreaza sau nu in ziua " << (i + 1) << "? (Ziua 1 = Luni, Ziua 5 = Vineri)\n" << "Introduceti 1 sau respectiv 0: ";
                        input >> Emp.weekdays[i];
                        while (Emp.weekdays[i] != 0 && Emp.weekdays[i] != 1)
                        {
                            cout << "Gresit! Introduceti 1 (daca lucreaza) sau 0 (daca nu lucreaza): ";
                            input >> Emp.weekdays[i];
                        }
                    }
                }
            }
        }
        catch (int x)
        {
            cout << "Eroarea numarul: " << x << " Varsta pe care ati introdus-o (" << Emp.age << ") nu este valida.\n";
        }

        return input;
    }

    friend ostream &operator << (ostream &output, const Employees Emp)
    {
        if (Emp.age <= 0) {}
        else
        {
            int count_zero = 0, count_one = 0, i;
            for (i = 0; i < 5; i++)
            {
                if (Emp.weekdays[i] == 0) count_zero++;
                else count_one++;
            }
            if (Emp.working == 1)
            {
                if (count_one == 5)
                    output << "\nAngajatul " << Emp.employee_name << ", avand " << Emp.age << " de ani, genul " << Emp.gender << " si ID-ul " << Emp.ID <<  " lucreaza la " << Emp.where_is_it_working << ".\n" << "Acesta are un salariu de " << Emp.salary << "$/mo si lucreaza " << count_one << " zile pe saptamana.\n";
                else
                {
                    int c;
                    c = (((count_zero) * 50) * 4);
                    output << "\nAngajatul " << Emp.employee_name << ", avand " << Emp.age << " de ani, genul " << Emp.gender << " si ID-ul " << Emp.ID <<  " lucreaza la " << Emp.where_is_it_working << ".\n" << "Acesta are un salariu initial de " << Emp.salary << "$/mo si lucreaza " << count_one << " zile pe saptamana. Pentru fiecare zi in care nu lucreaza, acesta pierde 50$, astfel, salariul sau final este " << (Emp.salary - c) << "$/mo.\n";
                }
                output << "Compania are " << Emp.number_of_employees << " angajati.\n";
            }
            else
                output << "\nAngajatul " << Emp.employee_name << " este in concediu. Lasati-l in pace! :) \n";
        }
        return output;
    }

    friend ifstream &operator >> (ifstream &fin, Employees &Emp)
    {
        int i;
        char copy[25];
        fin >> copy;
        if (Emp.employee_name != nullptr) delete[] Emp.employee_name;
        Emp.employee_name = new char[strlen(copy) + 1];
        strcpy(Emp.employee_name, copy);
        fin >> Emp.age;
        try
        {
            if (Emp.age < 0) throw 7;
            else
            {
                fin >> Emp.gender;
                fin >> Emp.where_is_it_working;
                fin >> Emp.salary;
                fin >> Emp.working;
                if (Emp.working == 1)
                {
                    if (Emp.weekdays != nullptr) delete[] Emp.weekdays;
                    Emp.weekdays = new int[5];
                    for (i = 0; i < 5; i++) fin >> Emp.weekdays[i];
                }
            }
        }
        catch (int x)
        {
            cout << "Eroarea numarul: " << x << " Varsta pe care ati introdus-o (" << Emp.age << ") nu este valida.\n";
        }

        return fin;
    }

    friend ofstream &operator << (ofstream &fout, const Employees &Emp)
    {
        if (Emp.age <= 0) {}
        else
        {
            fout << "Numele angajatului este: " << Emp.employee_name << "\n";
            fout << "Varsta angajatului este: " << Emp.age << "\n";
            fout << "Genul angajatului este: " << Emp.gender << "\n";
            fout << "Locul in care lucreaza angajatului este: " << Emp.where_is_it_working << "\n";
            fout << "Salariul angajatului este de: " << Emp.salary << "$\n";
            if (Emp.working == 1)
            {
                for (int i = 0; i < 5; i++)
                {
                    if(Emp.weekdays[i] == 1) fout << "Angajatul lucreaza in ziua " << (i + 1) << "\n";
                    else fout << "Angajatul nu lucreaza in ziua " << (i + 1) << "\n";

                }
            }
            else
                fout << "Angajatul e in concediu! :)";

        }
        return fout;
    }

};

int Employees::number_of_employees = 0;

Employees::Employees(char* employee_name, char gender, int age, int* weekdays, bool working, float salary, char where_is_it_working[35]):ID(1010)
{
    this->employee_name = new char[strlen(employee_name) + 1];
    strcpy(this->employee_name, employee_name);
    this->gender = gender;
    this->age = age;
    try
    {
        if (this->age < 0) throw 7;
    }
    catch (int x)
    {
        cout << "Eroarea numarul: " << x << " Varsta pe care ati introdus-o (" << this->age << ") nu este valida.\n";
    }

    this->weekdays = new int[5];
    for (int i = 0; i < 5; i++) this->weekdays[i] = weekdays[i];
    this->working = working;
    this->salary = salary;
    strcpy(this->where_is_it_working, where_is_it_working);
    Employees::number_of_employees++;
}

Employees::Employees(char* employee_name, char gender, int age):ID(1010)
{
    this->employee_name = new char[strlen(employee_name) + 1];
    strcpy(this->employee_name, employee_name);
    this->gender = gender;
    this->age = age;
    try
    {
        if (this->age < 0) throw 7;
    }
    catch (int x)
    {
        cout << "Eroarea numarul: " << x << " Varsta pe care ati introdus-o (" << this->age << ") nu este valida.\n";
    }
    this->weekdays = new int[5];
    for (int i = 0; i < 5; i++) this->weekdays[i] = 0;
    this->working = 0;
    this->salary = 0;
    strcpy(this->where_is_it_working, "0000");
    Employees::number_of_employees++;
}

Employees::Employees():ID(1010)
{
    this->employee_name = new char[strlen("Anonymous") + 1];
    strcpy(this->employee_name, "Anonymous");
    this->gender = 'O';
    this->age = 0;
    this->weekdays = new int[5];
    for (int i = 0; i < 5; i++) this->weekdays[i] = 0;
    this->working = 0;
    this->salary = 0;
    strcpy(this->where_is_it_working, "000000000");
    Employees::number_of_employees++;
}

Employees::Employees(const Employees &emp):ID(emp.ID)
{
    this->employee_name = new char[strlen(emp.employee_name) + 1];
    strcpy(this->employee_name, emp.employee_name);
    this->gender = emp.gender;
    this->age = emp.age;
    try
    {
        if (emp.age < 0) throw 7;
    }
    catch (int x)
    {
        cout << "Eroarea numarul: " << x << " Varsta pe care ati introdus-o (" << this->age << ") nu este valida.\n";
    }
    this->weekdays = new int[5];
    for (int i = 0; i < 5; i++) this->weekdays[i] = emp.weekdays[i];
    this->working = emp.working;
    this->salary = emp.salary;
    strcpy(this->where_is_it_working, emp.where_is_it_working);
}

Employees::~Employees()
{
    if (this->employee_name != nullptr) delete[] this->employee_name;
    if (this->weekdays != nullptr) delete[] this->weekdays;
    cout << "Employee is killed. Ouch!\n";
}

void Employees::toString()
{
    if (this->age <= 0) {}
    else
    {
        if (this->working == 1)
            cout << "Employee " << this->employee_name << "is " << this->age << " years old. Gender: " << this->gender << ", ID: " << this->ID << ". Currently he is working at "<< this->where_is_it_working << " and has a salary of " << this->salary << "$/mo" << '\n';
        else
            cout << "Employee " << this->employee_name << "is " << this->age << " years old. Gender: " << this->gender << ", ID: " << this->ID << ". Currently he is not working at "<< this->where_is_it_working << " and has a salary of " << this->salary << "$/mo" << '\n';
    }
}

class World_Economy
{
public:
    virtual float calcTotal() = 0;
};

class Company : public World_Economy
{
private:
    int dim;
    vector <Employees> EVector;
    const char company_name[17] = "Tzeaca_Computer$";
    float* net_worth;
    int months;

public:
    const char* getCompanyName()
    {
        return this->company_name;
    }
    int getMonths()
    {
        return this->months;
    }
    void setMonths(int months)
    {
        this->months = months;
    }
    float* getNetWorth()
    {
        return this->net_worth;
    }
    void setNetWorth(float* net_worth, int months)
    {
        if (this->net_worth != nullptr) delete[] this->net_worth;
        this->months = months;
        this->net_worth = new float[months];
        for (int i = 0; i < months; i++) this->net_worth[i] = net_worth[i];
    }

    Company(int months, float* net_worth); // constructor
    Company(int months);
    Company(); // no parameter constructor
    Company(const Company &comp); // copy constructor
    ~Company(); // deconstructor

    void toString();

    Company &operator = (const Company &comp)
    {
        if (this != &comp)
        {
            this->months = comp.months;
            if (this->net_worth != nullptr) delete[] this->net_worth;
            this->net_worth = new float[comp.months];
            for (int i = 0; i < comp.months; i++) this->net_worth[i] = comp.net_worth[i];
        }
        return *this;
    }

    friend istream &operator >> (istream &input, Company &Comp)
    {
        int i;
        cout << "Introduceti numarul de luni: ";
        input >> Comp.months;
        if (Comp.net_worth != nullptr) delete[] Comp.net_worth;
        Comp.net_worth = new float[Comp.months];
        for (i = 0; i < Comp.months; i++)
        {
            cout << "Introduceti valoarea neta a companiei in luna " << (i + 1) << ": ";
            input >> Comp.net_worth[i];
        }
        cout << "Introduceti numarul de angajati: ";
        input >> Comp.dim;
        for (int i = 0; i < Comp.dim; i++)
        {
            cout << "Introduceti detaliile angajatului " << (i + 1) << ":" << "\n";
            Employees uuu;
            input >> uuu;
            Comp.EVector.push_back(uuu);
        }

        return input;
    }

    int vector_capacity()
    {
        return EVector.capacity();
    }

    void vector_add(int x)
    {
        for (int i = 0; i < x; i++)
        {
            Employees uuu;
            cin >> uuu;
            EVector.push_back(uuu);
        }
    }

    void vector_decrease(int x)
    {
        for (int i = 0; i < x; i++) EVector.erase(EVector.begin() + i);
    }

    float calcTotal()
    {
        float t;
        for (int i = 0; i < this->months; i++) t += this->net_worth[i];
        return t;
    }

    friend ostream &operator << (ostream &output, const Company &Comp)
    {
        int i;
        output << "Compania " << Comp.company_name << " are " << Comp.dim << " angajati, iar detaliile le gasiti mai jos: " << endl;
        for (auto ir = Comp.EVector.begin(); ir != Comp.EVector.end(); ++ir)
            cout << (*ir) << endl;
        output << "Totodata, " << Comp.company_name << " ";
        for (i = 0; i < (Comp.months - 2); i++)
        {
            if (Comp.net_worth[i] > Comp.net_worth[i + 1])
            {
                output << "a avut o descrestere in luna " << (i + 2) << " in valoare de " << (Comp.net_worth[i] - Comp.net_worth[i + 1]) << "$, ";
            }
            else if (Comp.net_worth[i] < Comp.net_worth[i + 1])
            {
                output << "a avut o crestere in luna " << (i + 2) << " in valoare de " << (Comp.net_worth[i + 1] - Comp.net_worth[i]) << "$, ";
            }
            else if (Comp.net_worth[i] == Comp.net_worth[i + 1])
            {
                output << "a stagnat in luna " << (i + 2) << ", ";
            }
        }
        if (Comp.net_worth[Comp.months - 2] > Comp.net_worth[Comp.months - 1])
        {
            output << "a avut o descrestere in ultima luna in valoare de " << (Comp.net_worth[Comp.months - 2] - Comp.net_worth[Comp.months - 1]) << "$." << '\n';
        }
        else if (Comp.net_worth[Comp.months - 2] < Comp.net_worth[Comp.months - 1])
        {
            output << "a avut o crestere in ultima luna in valoare de " << (Comp.net_worth[Comp.months - 1] - Comp.net_worth[Comp.months - 2]) << "$." << '\n';
        }
        else if (Comp.net_worth[Comp.months - 2] == Comp.net_worth[Comp.months - 1])
        {
            output << "a stagnat in ultima luna" << "." << '\n';
        }
        return output;
    }

    friend ifstream &operator >> (ifstream &fin, Company &Comp)
    {
        fin >> Comp.months;
        if (Comp.net_worth != nullptr) delete[] Comp.net_worth;
        Comp.net_worth = new float[Comp.months];
        for (int i = 0; i < Comp.months; i++)
        {
            fin >> Comp.net_worth[i];
        }
        return fin;
    }

    friend ofstream &operator << (ofstream &fout, const Company &Comp)
    {
        fout << "Numarul de luni este: " << Comp.months << "\n";
        for (int i = 0; i < Comp.months; i++)
        {
            fout << "Valoarea neta a companiei in luna " << (i + 1) << "este de: " << Comp.net_worth[i] << "$\n";
        }
        return fout;
    }

};

Company::Company(int months, float* net_worth)
{
    this->months = months;
    this->net_worth = new float[months];
    for (int i = 0; i < months; i++) this->net_worth[i] = net_worth[i];
}

Company::Company(int months)
{
    this->months = months;
    this->net_worth = new float[months];
    for (int i = 0; i < months; i++) this->net_worth[i] = 0.1;
}

Company::Company(const Company &comp)
{
    this->months = comp.months;
    this->net_worth = new float[comp.months];
    for (int i = 0; i < comp.months; i++) this->net_worth[i] = comp.net_worth[i];
}

Company::Company()
{
    this->months = 1;
    this->net_worth = new float[months];
    for (int i = 0; i < months; i++) this->net_worth[i] = 0.1;
    this->dim = 0;
}

Company::~Company()
{
    if(this->net_worth != nullptr) delete[] this->net_worth;
    cout << "\nCompany " << this->company_name << " is about done\n";
}


void Company::toString()
{
    cout << "Company " << this->company_name << " ";
    for (int i = 0; i < this->months; i++)
    {
        cout << "had a net worth " << this->net_worth[i] << " in month " << (i + 1) << ", ";
    }
    cout << "and now is looking steady!\n";
}

class Departments
{
private:
    string name;

public:
    string getName()
    {
        return this->name;
    }
    void setName(string name)
    {
        this->name = name;
    }

    Departments(string name);
    Departments();
    ~Departments();

    virtual float calcSomething() = 0;
    void toString();

    friend istream &operator >> (istream &input, Departments &D)
    {
        cout << "Introduceti numele departamentului <finante> sau <operatiuni>: ";
        input >> D.name;
        while((D.name != "finante") && (D.name != "operatiuni"))
        {
            cout << "Gresit! Introduceti <finante> sau <operatiuni>: ";
            input >> D.name;
        }
        return input;
    }

    friend ostream &operator << (ostream &output, const Departments &D)
    {
        output << "\nDepartamentul de " << D.name << " ";
        return output;
    }

    friend ifstream &operator >> (ifstream &fin, Departments &D)
    {
        fin >> D.name;
        return fin;
    }

    friend ofstream &operator << (ofstream &fout, Departments &D)
    {
        fout << "Numele Departamentului este: " << D.name << "\n";
        return fout;
    }

};

Departments::Departments(string name)
{
    this->name = name;
}

Departments::Departments()
{
    this->name = "Empty Dept";
}

Departments::~Departments()
{
    cout << "Departments are gone! ";
}

void Departments::toString()
{
    cout << "Departments are working! ";
}

class FinanceDept : public Departments
{
private:
    int days;
    float* income;
    float expenses, profit;

public:
    int getDays()
    {
        return this->days;
    }
    void setDays(int days)
    {
        this->days = days;
    }
    float* getIncome()
    {
        return this->income;
    }
    void setIncome(float* income, int days)
    {
        if (this->income != nullptr) delete[] this->income;
        this->days = days;
        this->income = new float[days];
        for (int i = 0; i < days; i++) this->income[i] = income[i];
    }
    float getExpenses()
    {
        return this->expenses;
    }
    void setExpenses(float expenses)
    {
        this->expenses = expenses;
    }
    float getProfit()
    {
        return this->profit;
    }
    void setProfit(float profit)
    {
        this->profit = profit;
    }

    FinanceDept(int days, float* income, float expenses);
    FinanceDept(int days, float* income);
    FinanceDept(const FinanceDept &fd);
    FinanceDept();
    FinanceDept operator++();
    FinanceDept operator++(int);
    FinanceDept operator-(float);
    FinanceDept operator*(float);
    bool operator==(FinanceDept&);
    bool operator<=(FinanceDept&);
    ~FinanceDept();

    void toString();

    FinanceDept &operator = (const FinanceDept &fd)
    {
        if (this != &fd)
        {
            this->days = fd.days;
            if (this->income != nullptr) delete[] this->income;
            this->income = new float[fd.days];
            for (int i = 0; i < fd.days; i++) this->income[i] = fd.income[i];
            this->expenses = fd.expenses;
        }
        return *this;
    }

    int operator [](int index)
    {
        if ((index < days) && index > 0) return this->income[index];
        else
        {
            cout << "Index invalid";
            return -1;
        }
    }

    explicit operator int()
    {
        return (int)this->expenses;
    }

    friend istream &operator >> (istream &input, FinanceDept &Fd)
    {
        int i;
        float s = 0;
        input >> (Departments &)Fd;
        cout << "Introduceti numarul de zile: ";
        input >> Fd.days;
        if(Fd.income != nullptr) delete[] Fd.income;
        Fd.income = new float[Fd.days];
        for(i = 0; i < Fd.days; i++)
        {
            cout << "Introduceti venitul in ziua " << (i + 1) << ": ";
            input >> Fd.income[i];
            s += Fd.income[i];
        }
        cout << "Introduceti cheltuielile: ";
        input >> Fd.expenses;
        Fd.profit = s - Fd.expenses;
        return input;
    }

    float calcSomething()
    {
        float s = 0;
        for (int i = 0; i < this->days; i++) s += this->income[i];
        this->profit = s - this->expenses;
        return this->profit;
    }

    friend ostream &operator << (ostream &output, const FinanceDept &Fd)
    {
        if (Fd.profit >= 0)
        {
            output << (Departments &)Fd << "a inregistrat ";
            for (int i = 0; i < (Fd.days) - 1; i++)
            {
                output << Fd.income[i] <<"$ in ziua " << (i + 1) << ", ";
            }
            output << Fd.income[(Fd.days) - 1] << "$ in ultima zi." << '\n' << "Cheltuielile sunt de " << Fd.expenses << "$, iar profitul este de: " << Fd.profit << "$ ." << '\n';
        }
        else
        {
            output << (Departments &)Fd << "a inregistrat ";
            for (int i = 0; i < (Fd.days) - 1; i++)
            {
                output << Fd.income[i] <<"$ in ziua " << (i + 1) << ", ";
            }
            output << Fd.income[(Fd.days) - 1] << "$ in ultima zi." << '\n' << "Cheltuielile sunt de " << Fd.expenses << "$, iar compania are pierderi de " << abs(Fd.profit) << "$ ." << '\n';
        }
        return output;
    }

    friend ifstream &operator >> (ifstream &fin, FinanceDept &Fd)
    {
        float s = 0;
        fin >> (Departments &)Fd;
        fin >> Fd.days;
        if(Fd.income != nullptr) delete[] Fd.income;
        Fd.income = new float[Fd.days];
        for(int i = 0; i < Fd.days; i++)
        {
            fin >> Fd.income[i];
            s += Fd.income[i];
        }
        fin >> Fd.expenses;
        Fd.profit = s - Fd.expenses;
        return fin;
    }

    friend ofstream &operator << (ofstream &fout, const FinanceDept &Fd)
    {
        if (Fd.profit >= 0)
        {
            fout << (Departments &)Fd << "a inregistrat ";
            for (int i = 0; i < (Fd.days) - 1; i++)
            {
                fout << Fd.income[i] <<"$ in ziua " << (i + 1) << ", ";
            }
            fout << Fd.income[(Fd.days) - 1] << "$ in ultima zi." << '\n' << "Cheltuielile sunt de " << Fd.expenses << "$, iar profitul este de: " << Fd.profit << "$ ." << '\n';
        }
        else
        {
            fout << (Departments &)Fd << "a inregistrat ";
            for (int i = 0; i < (Fd.days) - 1; i++)
            {
                fout << Fd.income[i] <<"$ in ziua " << (i + 1) << ", ";
            }
            fout << Fd.income[(Fd.days) - 1] << "$ in ultima zi." << '\n' << "Cheltuielile sunt de " << Fd.expenses << "$, iar compania are pierderi de " << abs(Fd.profit) << "$ ." << '\n';
        }
        return fout;
    }

};

FinanceDept::FinanceDept(int days, float* income, float expenses)
{
    this->days = days;
    this->income = new float[days];
    for(int i = 0; i < days; i++) this->income[i] = income[i];
    this->expenses = expenses;
}

FinanceDept::FinanceDept(int days, float* income)
{
    this->days = days;
    this->income = new float[days];
    for(int i = 0; i < days; i++) this->income[i] = income[i];
    this->expenses = 0;
}

FinanceDept::FinanceDept(const FinanceDept &fd)
{
    this->days = fd.days;
    this->income = new float[fd.days];
    for(int i = 0; i < fd.days; i++) this->income[i] = fd.income[i];
    this->expenses = fd.expenses;
}

FinanceDept::FinanceDept()
{
    this->days = 1;
    this->income = new float[days];
    for(int i = 0; i < days; i++) this->income[i] = 5;
    this->expenses = 0;
    this->profit = this->income[1]; // fiind doar o zi
}

FinanceDept FinanceDept::operator++()
{
    this->expenses++;
    return *this;
}

FinanceDept FinanceDept::operator++(int)
{
    this->expenses++;
    return *this;
}

FinanceDept FinanceDept::operator-(float x)
{
    this->expenses -= x;
    return *this;
}

FinanceDept FinanceDept::operator*(float x)
{
    this->expenses *= x;
    return *this;
}

bool FinanceDept::operator==(FinanceDept &fd)
{
    return this->expenses == fd.expenses;
}

bool FinanceDept::operator<=(FinanceDept &fd)
{
    return this->expenses <= fd.expenses;
}

FinanceDept::~FinanceDept()
{
    if(this->income != nullptr) delete[] this->income;
    cout << "Rip money\n";
}

void FinanceDept::toString()
{
    if (profit >= 0)
    {
        cout << "Company had an income of ";
        int s = 0;
        for (int i = 0; i < this->days; i++)
        {
            s += this->income[i];
            cout << this->income[i] << "$ in day " << (i + 1) << ", ";
        }
        this->profit = s - this->expenses;
        cout << " having expenses of " << this->expenses << "$ . Profit is: " << this->profit << "." << '\n';
    }
    else
    {
        cout << "Company had an income of ";
        int s = 0;
        for (int i = 0; i < this->days; i++)
        {
            s += this->income[i];
            cout << this->income[i] << "$ in day " << (i + 1) << ", ";
        }
        this->profit = s - this->expenses;
        cout << " having expenses of " << this->expenses << "$ . Company is losing " << abs(this->profit) << "." << '\n';
    }
}

class OpManagement : public Departments
{
private:
    int nr_of_trucks;
    int* materials;
    char* product_name;
    float product_price;
    bool enough_materials;
    char size;
    char barcode[7];
    const int product_ID;
    static int nr_of_products;

public:
    int getNrOfTrucks()
    {
        return this->nr_of_trucks;
    }
    void setNrOfTrucks(int nr_of_trucks)
    {
        this->nr_of_trucks = nr_of_trucks;
    }
    int* getMaterials()
    {
        return this->materials;
    }
    void setMaterials(int* materials, int nr_of_trucks)
    {
        if (this->materials != nullptr) delete[] this->materials;
        this->nr_of_trucks = nr_of_trucks;
        this->materials = new int[nr_of_trucks];
        for (int i = 0; i < nr_of_trucks; i++) this->materials[i] = materials[i];
    }
    char* getProductName()
    {
        return this->product_name;
    }
    void setProductName(char* product_name)
    {
        if (this->product_name != nullptr) delete[] this->product_name;
        this->product_name = new char[strlen(product_name) + 1];
        strcpy(this->product_name, product_name);
    }
    float getProductPrice()
    {
        return this->product_price;
    }
    void setProductPrice(float product_price)
    {
        this->product_price = product_price;
    }
    bool getEnoughMaterials()
    {
        return this->enough_materials;
    }
    void setEnoughMaterials(bool enough_materials)
    {
        this->enough_materials = enough_materials;
    }
    char getSize()
    {
        return this->size;
    }
    void setSize(char size)
    {
        this->size = size;
    }
    char* getBarcode()
    {
        return this->barcode;
    }
    void setBarcode(char barcode[7])
    {
        strcpy(this->barcode, barcode);
    }

    OpManagement(char* product_name, float product_price, char size, int nr_of_trucks, int* materials, bool enough_materials, char barcode[7]);
    OpManagement(char* product_name, float product_price);
    OpManagement(const OpManagement &manage);
    OpManagement();
    OpManagement operator++();
    OpManagement operator++(int);
    OpManagement operator-(float);
    OpManagement operator*(float);
    bool operator==(OpManagement&);
    bool operator<=(OpManagement&);
    ~OpManagement();


    void toString();

    OpManagement &operator = (const OpManagement &op)
    {
        if (this != &op)
        {
            if (this->product_name != nullptr) delete[] this->product_name;
            this->product_name = new char[strlen(op.product_name) + 1];
            strcpy(this->product_name, op.product_name);
            this->product_price = op.product_price;
            this->size = op.size;
            if (this->materials != nullptr) delete[] this->materials;
            this->nr_of_trucks = op.nr_of_trucks;
            this->materials = new int[op.nr_of_trucks];
            for (int i = 0; i < op.nr_of_trucks; i++) this->materials[i] = op.materials[i];
            this->enough_materials = op.enough_materials;
            strcpy(this->barcode, op.barcode);
        }
        return *this;
    }

    char operator [](int index)
    {
        if ((index < strlen(barcode)) && index > 0) return this->barcode[index];
        else
        {
            cout << "Index invalid";
            return -1;
        }
    }

    explicit operator int()
    {
        return (int)this->product_price;
    }

    friend istream &operator >> (istream &input, OpManagement &Op)
    {
        char copy[30];
        int i;
        int c = 0, d = 0;
        input >> (Departments &)Op;
        cout << "Introduceti numele produsului: ";
        input >> copy;
        if (Op.product_name != nullptr) delete[] Op.product_name;
        Op.product_name = new char[strlen(copy) + 1];
        strcpy(Op.product_name, copy);
        try
        {
            for (int i = 0; i < strlen(Op.product_name); i++)
            {
                if (isdigit(Op.product_name[i]))
                {
                    throw 10;
                    break;
                }
            }
        }
        catch (int x)
        {
            cout << "Eroarea numarul: " << x << ". Numele produsului pe care l-ati introdus (" << Op.product_name << ") este invalid.\n";
            d = 1;
        }
        if (d == 0)
        {
            cout << "Alege marimea produsului (S, M, L): ";
            input >> Op.size;
            Op.size = toupper(Op.size); // pot scrie si lowercase s / m / l
            while (Op.size != 'S' && Op.size != 'M' && Op.size != 'L')
            {
                cout << "Gresit! Introduceti S, M sau L: ";
                input >> Op.size;
                Op.size = toupper(Op.size);
            }
            cout << "Introduceti numarul de camioane cu marfa: ";
            input >> Op.nr_of_trucks;
            if (Op.materials != nullptr) delete[] Op.materials;
            Op.materials = new int[Op.nr_of_trucks];
            for (i = 0; i < Op.nr_of_trucks; i++)
            {
                cout << "Introduceti cantitatea de marfa pe care o aduce camionul " << (i + 1) << ": ";
                input >> Op.materials[i];
                c += Op.materials[i];
            }
            cout << "Introduceti pretul produsului: ";
            input >> Op.product_price;
            cout << "Introduceti codul de bare: #";
            input >> Op.barcode;
            if (Op.size == 'S')
            {
                Op.nr_of_products += (c / 100);
                if ((c % 100) != 0)
                {
                    Op.enough_materials = 0;
                }
                else
                {
                    Op.enough_materials = 1;
                }
            }
            else if (Op.size == 'M')
            {
                Op.nr_of_products += (c / 500);
                if ((c % 500) != 0)
                {
                    Op.enough_materials = 0;
                }
                else
                {
                    Op.enough_materials = 1;
                }
            }
            else if (Op.size == 'L')
            {
                Op.nr_of_products += (c / 1000);
                if ((c % 1000) != 0)
                {
                    Op.enough_materials = 0;
                }
                else
                {
                    Op.enough_materials = 1;
                }
            }
        }

        return input;
    }

    float calcSomething()
    {
        int c = 0;
        for (int i = 0; i < this->nr_of_trucks; i++) c += this->materials[i];
        return c;
    }

    friend ostream &operator << (ostream &output, const OpManagement &Op)
    {
        int i;
        int c = 0, d = 0;
        for (int j = 0; j < strlen(Op.product_name); j++)
        {
            if (isdigit(Op.product_name[j]))
            {
                d = 1;
                break;
            }
        }
        if (d == 0)
        {
            for (i = 0; i < Op.nr_of_trucks; i++)
            {
                c += Op.materials[i];
            }
            if (Op.size == 'S')
            {
                if (c < 100)
                {
                    output << "\nNu sunt destule materiale pentru produsul ales." << '\n';
                }
                else
                {
                    if (Op.enough_materials == 0)
                    {
                        output << (Departments &)Op << "produce obiecte de tip " << Op.product_name << " de marime " << Op.size << " ce costa " << Op.product_price << "$ a fost fabricat de " << Op.nr_of_products << " ori." << '\n' << "Din cele " << c << " materiale, s-au folosit cate 100 de resurse pentru fiecare produs in parte." << '\n' << "Codul de bare este: #" << Op.barcode << " iar Totalul este: " << (long)(Op.nr_of_products * Op.product_price) << "$." << '\n' << "Au ramas " << (c % 100) << " materiale in depozit." << '\n';
                    }
                    else if (Op.enough_materials == 1)
                    {
                        output << (Departments &)Op << "produce obiecte de tip " << Op.product_name << " de marime " << Op.size << " ce costa " << Op.product_price << "$ a fost fabricat de " << Op.nr_of_products << " ori." << '\n' << "Din cele " << c << " materiale, s-au folosit cate 100 de resurse pentru fiecare produs in parte." << '\n' << "Codul de bare este: #" << Op.barcode << " iar Totalul este: " << (long)(Op.nr_of_products * Op.product_price) << "$." << '\n' << "Nu au mai ramas materiale in depozit." << '\n';
                    }
                }

            }
            else if (Op.size == 'M')
            {
                if (c < 500)
                {
                    output << "\nNu sunt destule materiale pentru produsul ales." << '\n';
                }
                else
                {
                    if (Op.enough_materials == 0)
                    {
                        output << (Departments &)Op << "produce obiecte de tip " << Op.product_name << " de marime " << Op.size << " ce costa " << Op.product_price << "$ a fost fabricat de " << Op.nr_of_products << " ori." << '\n' << "Din cele " << c << " materiale, s-au folosit cate 500 de resurse pentru fiecare produs in parte." << '\n' << "Codul de bare este: #" << Op.barcode << " iar Totalul este: " << (long)(Op.nr_of_products * Op.product_price) << "$." << '\n' << "Au ramas " << (c % 500) << " materiale in depozit." << '\n';
                    }
                    else if (Op.enough_materials == 1)
                    {
                        output << (Departments &)Op << "produce obiecte de tip " << Op.product_name << " de marime " << Op.size << " ce costa " << Op.product_price << "$ a fost fabricat de " << Op.nr_of_products << " ori." << '\n' << "Din cele " << c << " materiale, s-au folosit cate 500 de resurse pentru fiecare produs in parte." << '\n' << "Codul de bare este: #" << Op.barcode << " iar Totalul este: " << (long)(Op.nr_of_products * Op.product_price) << "$." << '\n' << "Nu au mai ramas materiale in depozit." << '\n';
                    }
                }
            }
            else if (Op.size == 'L')
            {
                if (c < 1000)
                {
                    output << "\nNu sunt destule materiale pentru produsul ales." << '\n';
                }
                else
                {
                    if (Op.enough_materials == 0)
                    {
                        output << (Departments &)Op << "produce obiecte de tip " << Op.product_name << " de marime " << Op.size << " ce costa " << Op.product_price << "$, avand ID-ul " << Op.product_ID << " a fost fabricat de " << Op.nr_of_products << " ori." << '\n' << "Din cele " << c << " materiale, s-au folosit cate 1000 de resurse pentru fiecare produs in parte." << '\n' << "Codul de bare este: #" << Op.barcode << " iar Totalul este: " << (long)(Op.nr_of_products * Op.product_price) << "$." << '\n' << "Au ramas " << (c % 1000) << " materiale in depozit." << '\n';
                    }
                    else if (Op.enough_materials == 1)
                    {
                        output << (Departments &)Op << "produce obiecte de tip " << Op.product_name << " de marime " << Op.size << " ce costa " << Op.product_price << "$, avand ID-ul " << Op.product_ID << " a fost fabricat de " << Op.nr_of_products << " ori." << '\n' << "Din cele " << c << " materiale, s-au folosit cate 1000 de resurse pentru fiecare produs in parte." << '\n' << "Codul de bare este: #" << Op.barcode << " iar Totalul este: " << (long)(Op.nr_of_products * Op.product_price) << "$." << '\n' << "Nu au mai ramas materiale in depozit." << '\n';
                    }
                }
            }
        }

        return output;
    }

    friend ifstream &operator >> (ifstream &fin, OpManagement &Op)
    {
        char copy[30];
        int c = 0;
        fin >> (Departments &)Op;
        fin >> copy;
        if (Op.product_name != nullptr) delete[] Op.product_name;
        Op.product_name = new char[strlen(copy) + 1];
        strcpy(Op.product_name, copy);
        fin >> Op.size;
        Op.size = toupper(Op.size);
        fin >> Op.nr_of_trucks;
        if (Op.materials != nullptr) delete[] Op.materials;
        Op.materials = new int[Op.nr_of_trucks];
        for (int i = 0; i < Op.nr_of_trucks; i++)
        {
            fin >> Op.materials[i];
            c += Op.materials[i];
        }
        fin >> Op.product_price;
        fin >> Op.barcode;
        if (Op.size == 'S')
        {
            Op.nr_of_products += (c / 100);
            if ((c % 100) != 0)
            {
                Op.enough_materials = 0;
            }
            else
            {
                Op.enough_materials = 1;
            }
        }
        else if (Op.size == 'M')
        {
            Op.nr_of_products += (c / 500);
            if ((c % 500) != 0)
            {
                Op.enough_materials = 0;
            }
            else
            {
                Op.enough_materials = 1;
            }
        }
        else if (Op.size == 'L')
        {
            Op.nr_of_products += (c / 1000);
            if ((c % 1000) != 0)
            {
                Op.enough_materials = 0;
            }
            else
            {
                Op.enough_materials = 1;
            }
        }
        return fin;
    }

    friend ofstream &operator << (ofstream &fout, const OpManagement &Op)
    {
        int c = 0, d = 0;
        try
        {
            for (int i = 0; i < strlen(Op.product_name); i++)
            {
                if (isdigit(Op.product_name[i]))
                {
                    throw 10;
                    break;
                }
            }
        }
        catch (int x)
        {
            fout << "Eroarea numarul: " << x << ". Numele produsului pe care l-ati introdus (" << Op.product_name << ") este invalid.\n";
            d = 1;
        }
        if (d == 0)
        {
            for (int i = 0; i < Op.nr_of_trucks; i++)
            {
                c += Op.materials[i];
            }
            if (Op.size == 'S')
            {
                if (c < 100)
                {
                    fout << "\nNu sunt destule materiale pentru produsul ales." << '\n';
                }
                else
                {
                    if (Op.enough_materials == 0)
                    {
                        fout << (Departments &)Op << "Acesta produce obiecte de tip " << Op.product_name << ", de marime " << Op.size << " ce costa " << Op.product_price << "$ a fost fabricat de " << Op.nr_of_products << " ori." << '\n' << "Din cele " << c << " materiale, s-au folosit cate 100 de resurse pentru fiecare produs in parte." << '\n' << "Codul de bare este: #" << Op.barcode << " iar Totalul este: " << (long)(Op.nr_of_products * Op.product_price) << "$." << '\n' << "Au ramas " << (c % 100) << " materiale in depozit." << '\n';
                    }
                    else if (Op.enough_materials == 1)
                    {
                        fout << (Departments &)Op << "Acesta produce obiecte de tip " << Op.product_name << ", de marime " << Op.size << " ce costa " << Op.product_price << "$ a fost fabricat de " << Op.nr_of_products << " ori." << '\n' << "Din cele " << c << " materiale, s-au folosit cate 100 de resurse pentru fiecare produs in parte." << '\n' << "Codul de bare este: #" << Op.barcode << " iar Totalul este: " << (long)(Op.nr_of_products * Op.product_price) << "$." << '\n' << "Nu au mai ramas materiale in depozit." << '\n';
                    }
                }

            }
            else if (Op.size == 'M')
            {
                if (c < 500)
                {
                    fout << "\nNu sunt destule materiale pentru produsul ales." << '\n';
                }
                else
                {
                    if (Op.enough_materials == 0)
                    {
                        fout << (Departments &)Op << "Acesta produce obiecte de tip " << Op.product_name << ", de marime " << Op.size << " ce costa " << Op.product_price << "$ a fost fabricat de " << Op.nr_of_products << " ori." << '\n' << "Din cele " << c << " materiale, s-au folosit cate 500 de resurse pentru fiecare produs in parte." << '\n' << "Codul de bare este: #" << Op.barcode << " iar Totalul este: " << (long)(Op.nr_of_products * Op.product_price) << "$." << '\n' << "Au ramas " << (c % 500) << " materiale in depozit." << '\n';
                    }
                    else if (Op.enough_materials == 1)
                    {
                        fout << (Departments &)Op << "Acesta produce obiecte de tip " << Op.product_name << ", de marime " << Op.size << " ce costa " << Op.product_price << "$ a fost fabricat de " << Op.nr_of_products << " ori." << '\n' << "Din cele " << c << " materiale, s-au folosit cate 500 de resurse pentru fiecare produs in parte." << '\n' << "Codul de bare este: #" << Op.barcode << " iar Totalul este: " << (long)(Op.nr_of_products * Op.product_price) << "$." << '\n' << "Nu au mai ramas materiale in depozit." << '\n';
                    }
                }
            }
            else if (Op.size == 'L')
            {
                if (c < 1000)
                {
                    fout << "\nNu sunt destule materiale pentru produsul ales." << '\n';
                }
                else
                {
                    if (Op.enough_materials == 0)
                    {
                        fout << (Departments &)Op << "Acesta produce obiecte de tip " << Op.product_name << ", de marime " << Op.size << " ce costa " << Op.product_price << "$, avand ID-ul " << Op.product_ID << " a fost fabricat de " << Op.nr_of_products << " ori." << '\n' << "Din cele " << c << " materiale, s-au folosit cate 1000 de resurse pentru fiecare produs in parte." << '\n' << "Codul de bare este: #" << Op.barcode << " iar Totalul este: " << (long)(Op.nr_of_products * Op.product_price) << "$." << '\n' << "Au ramas " << (c % 1000) << " materiale in depozit." << '\n';
                    }
                    else if (Op.enough_materials == 1)
                    {
                        fout << (Departments &)Op << "Acesta produce obiecte de tip " << Op.product_name << ", de marime " << Op.size << " ce costa " << Op.product_price << "$, avand ID-ul " << Op.product_ID << " a fost fabricat de " << Op.nr_of_products << " ori." << '\n' << "Din cele " << c << " materiale, s-au folosit cate 1000 de resurse pentru fiecare produs in parte." << '\n' << "Codul de bare este: #" << Op.barcode << " iar Totalul este: " << (long)(Op.nr_of_products * Op.product_price) << "$." << '\n' << "Nu au mai ramas materiale in depozit." << '\n';
                    }
                }
            }
        }
        return fout;
    }

};

int OpManagement::nr_of_products = 0;

OpManagement::OpManagement(char* product_name, float product_price, char size, int nr_of_trucks, int* materials, bool enough_materials, char barcode[11]):product_ID(9999)
{
    this->product_name = new char[strlen(product_name) + 1];
    strcpy(this->product_name, product_name);
    try
    {
        for (int i = 0; i < strlen(this->product_name); i++)
        {
            if (isdigit(this->product_name[i]))
            {
                throw 10;
                break;
            }
        }
    }
    catch (int x)
    {
        cout << "Eroarea numarul: " << x << ". Numele produsului pe care l-ati introdus (" << this->product_name << ") este invalid.\n";
    }
    this->product_price = product_price;
    this->size = size;
    this->nr_of_trucks = nr_of_trucks;
    this->materials = new int[nr_of_trucks];
    for (int i = 0; i < nr_of_trucks; i++) this->materials[i] = materials[i];
    this->enough_materials = enough_materials;
    strcpy(this->barcode, barcode);
    //OpManagement::nr_of_products++;
}

OpManagement::OpManagement(char* product_name, float product_price):product_ID(9997)
{
    this->product_name = new char[strlen(product_name) + 1];
    strcpy(this->product_name, product_name);
    try
    {
        for (int i = 0; i < strlen(this->product_name); i++)
        {
            if (isdigit(this->product_name[i]))
            {
                throw 10;
                break;
            }
        }
    }
    catch (int x)
    {
        cout << "Eroarea numarul: " << x << ". Numele produsului pe care l-ati introdus (" << this->product_name << ") este invalid.\n";
    }
    this->product_price = product_price;
    this->size = 'S';
    this->nr_of_trucks = 1;
    this->materials = new int[nr_of_trucks];
    for (int i = 0; i < nr_of_trucks; i++) this->materials[i] = 0;
    this->enough_materials = 0;
    strcpy(this->barcode, "00000010");
    //OpManagement::nr_of_products++;
}

OpManagement::OpManagement(const OpManagement &manage):product_ID(manage.product_ID)
{
    this->product_name = new char[strlen(manage.product_name) + 1];
    strcpy(this->product_name, manage.product_name);
    this->product_price = manage.product_price;
    this->size = manage.size;
    this->nr_of_trucks = manage.nr_of_trucks;
    this->materials = new int[manage.nr_of_trucks];
    for (int i = 0; i < nr_of_trucks; i++) this->materials[i] = manage.materials[i];
    this->enough_materials = manage.enough_materials;
    strcpy(this->barcode, manage.barcode);
}

OpManagement::OpManagement():product_ID(9996)
{
    this->product_name = new char[strlen("Empty box") + 1];
    strcpy(this->product_name, "Empty box");
    this->product_price = 0;
    this->size = 'S';
    this->nr_of_trucks = 1;
    this->materials = new int[nr_of_trucks];
    for (int i = 0; i < nr_of_trucks; i++) this->materials[i] = 0;
    this->enough_materials = 0;
    strcpy(this->barcode, "00000010");
    //OpManagement::nr_of_products++;
}

OpManagement OpManagement::operator++()
{
    this->product_price++;
    return *this;
}

OpManagement OpManagement::operator++(int)
{
    this->product_price++;
    return *this;
}


OpManagement OpManagement::operator-(float x)
{
    this->product_price -= x;
    return *this;
}

OpManagement OpManagement::operator*(float x)
{
    this->product_price *= x;
    return *this;
}

bool OpManagement::operator==(OpManagement &op)
{
    return this->product_price == op.product_price;
}

bool OpManagement::operator<=(OpManagement &op)
{
    return this->product_price <= op.product_price;
}

OpManagement::~OpManagement()
{
    if (this->product_name != nullptr) delete[] this->product_name;
    if (this->materials != nullptr) delete[] this->materials;
    cout << "Operations Management is not working anymore!\n";
}

void OpManagement::toString()
{
    int c = 0;
    for (int i = 0; i < strlen(this->product_name); i++)
    {
        if (isdigit(this->product_name[i]))
        {
            c = 1;
            break;
        }
    }
    if (c == 0)
    {
        int s = 0;
        for (int i = 0; i < this->nr_of_trucks; i++)
            s += this->materials[i];
        if (this->enough_materials == 1)
            cout << "Operations Management has 10 " << this->product_name << " each valued at " << this->product_price << " of size " << this->size << " and " << s << " mats left. They think that they have enough mats, and the barcode is: " << this->barcode << '\n';
        else
            cout << "Operations Management has 10 " << this->product_name << " each valued at " << this->product_price << " of size " << this->size << " and " << s << " mats left. They don't think that they have enough mats, and the barcode is: " << this->barcode << '\n';
    }

}

int main()
{
//======Company Class test runs======
    /*
      Company wow;
      cin >> wow;
      cout << wow;

      //float net_worth[] = {3550.5, 4690.4, 13580};
      //Company test(3, net_worth);
      //Company test;
      //test.toString();

      //Company clock;
      //Company sheep(3);
      //sheep.toString();
      //cout << sheep;
      //Company clock(test);
      //Company clock;
      //clock = test;
      //cout << clock;
      //clock.toString();

      ifstream f("CompanyIn.txt");
      ofstream g("CompanyOut.txt");
      Company clomp;
      f >> clomp;
      cout << clomp;
      g << clomp;
    */
//======FinanceDept Class test runs======
    /*
      FinanceDept test;
      cin >> test;
      cout << test.calcSomething() << endl;
      cout << test;

      //cout << (int)test << endl;

      //float venituri[] = {3500, 5000, 2400};
      //FinanceDept halloween(3, venituri, 2000);
      //FinanceDept halloween(3, venituri);
      //FinanceDept halloween;
      //halloween.toString();
      //++halloween;
      //halloween++;
      //cout << halloween;
      //halloween.toString();

      //FinanceDept yolo;
      //FinanceDept yolo(halloween);
      //yolo = halloween;
      //yolo++;
      //++yolo;
      //yolo - 10.5;
      //yolo * 2.3;
      //if (yolo == halloween) cout << "Da\n"; else cout << "Nu\n";
      //if (yolo <= halloween) cout << "Da\n"; else cout << "Nu\n";
      //yolo.toString();
      //cout << yolo;

      ifstream f("FinanceDeptIn.txt");
      ofstream g("FinanceDeptOut.txt");
      FinanceDept Fedpt;
      f >> Fedpt;
      g << Fedpt;
    */
//======OpManagement Class test runs======
    /*
      OpManagement rofl;
      cin >> rofl;
      //cout << rofl.calcSomething() << endl;
      cout << rofl;

      //cout << rofl[2] << endl;

      //++rofl;
      //cout << rofl;
      //OpManagement lmao = rofl;
      //lmao++;
      //if (lmao == rofl) cout << "da\n"; else cout << "nu\n";
      //if (lmao <= rofl) cout << "da\n"; else cout << "nu\n";
      //rofl - 10.5;
      //rofl * 2.9;
      //cout << rofl << endl;

      //cout << (int)rofl << endl;

      //int resurse[] = {3000, 3000, 3000, 3000, 3000};
      //OpManagement test("Teaca1", 350.5, 'L', 5, resurse, 1, "ff0000");
      //OpManagement test("Teaca", 350.5);
      //OpManagement test;
      //test.toString();
      //OpManagement rofl(test);
      //OpManagement rofl;
      //rofl = test;
      //rofl.toString();
      //cout << rofl;

      ifstream f("OpManagementIn.txt");
      ofstream g("OpManagementOut.txt");
      OpManagement Opmk;
      f >> Opmk;
      cout << Opmk;
      g << Opmk;
    */
//======Employee Class test runs======
    /*
      Employees test;
      cin >> test;
      cout << test;

      //int bird[] = {1, 0, 1, 0, 1};
      //Employees rabla("Ghisoiu", 'M', -35, bird, 1, 3500, "DO");
      //Employees rabla("Ghisoiu", 'M', 35);
      //Employees rabla;
      //rabla.toString();
      //Employees test(rabla);
      //Employees test;
      //test = rabla;
      //cout << test;

      //ifstream f("EmployeesIn.txt");
      //ofstream g("EmployeesOut.txt");
      //Employees esc;
      //f >> esc;
      //cout << esc;
      //g << esc;
    */
//===============Scuffed Menu===============//
    bool open, modif, decider = 1;
    int visualize, ind, dimen, imen;
    float new_expenses;
    cout << "Este compania deschisa in aceasta ora?\n";
    cout << "[0] Inchisa.\n";
    cout << "[1] Deschisa.\n";
    cout << "Introduceti valoarea: ";
    cin >> open;
    cout << endl;
    switch (open)
    {
    case 0:
    {
        cout << "Compania Tzeaca Computer$ nu este deschisa momentan. Reveniti mai tarziu";
        break;
    }
    case 1:
    {
        cout << "\n";
        cout << " ____________________________________________\n";
        cout << "| Bun venit la compania <Tzeaca Computer$!>  |\n";
        cout << "|____________________________________________|\n";
        cout << "\n";
        sleep(1);
        while (decider == 1)
        {
            cout << "Mai jos puteti accesa date despre companie cat si/sau despre angajati.\n";
            sleep(1);
            cout << "[1] Compania.\n";
            sleep(1);
            cout << "[2] Departamentul de finante.\n";
            sleep(1);
            cout << "[3] Departamentul de Operatiuni.\n";
            sleep(1);
            cout << "[4] Angajati.\n";
            sleep(1);
            cout << "Alegeti ce vreti sa vizualizati: ";
            cin >> visualize;
            cout << endl;
            switch (visualize)
            {
            case 1:
            {
                cout << "Introduceti mai jos detaliile companiei cat si o lista cu angajati.\n";
                Company computers;
                cin >> computers;
                cout << "\nDoriti sa mai adaugati sau sa concediati angajati?\n";
                cout << "[1] Adaugare.\n";
                cout << "[2] Stergere.\n";
                cout << "[3] Nu doresc nicio modificare.\n";
                cin >> ind;
                cout << endl;
                switch (ind)
                {
                case 1:
                {
                    cout << "Cati angajati mai vreti sa adaugati in plus: ";
                    cin >> dimen;
                    while(dimen <= 0)
                    {
                        cout << "Nu puteti introduce un numar <= 0. Introduceti un alt numar: ";
                        cin >> dimen;
                    }
                    computers.vector_add(dimen);
                    break;
                }
                case 2:
                {
                    if (computers.vector_capacity() == 1)
                    {
                        cout << "Nu puteti sterge angajati!\n";
                        break;
                    }
                    else
                    {
                        cout << "Cati angajati vreti sa stergeti: ";
                        cin >> imen;
                        while(computers.vector_capacity() - imen < 0)
                        {
                            cout << "Nu puteti sterge mai multi angajati decat sunt.\n";
                            cout << "Introduceti un numar mai mic decat " << computers.vector_capacity() << ": ";
                            cin >> imen;
                        }
                        while(computers.vector_capacity() - imen == 0)
                        {
                            cout << "Nu puteti sterge toti angajatii.\n";
                            cout << "Introduceti un numar mai mic decat " << computers.vector_capacity() << ": ";
                            cin >> imen;
                        }
                        computers.vector_decrease(imen);
                        break;
                    }
                }
                case 3:
                {}
                break;
                }
                cout << endl;
                cout << computers;
                break;
            }
            case 2:
            {
                cout << "Introduceti detaliile legate de Departamentul de Finante:\n";
                FinanceDept fnd;
                cin >> fnd;
                cout << endl;
                cout << "Doriti o modificare a cheltuielilor?\n";
                cout << "[1] Da.\n";
                cout << "[0] Nu.\n";
                cin >> modif;
                switch (modif)
                {
                case 0:
                {}
                break;
                case 1:
                {
                    cout << "Ce valoare vreti sa introduceti: ";
                    cin >> new_expenses;
                    while(new_expenses < 0)
                    {
                        cout << "Nu puteti introduce cheltuieli negative!\n";
                        cout << "Introduceti o valoare noua: ";
                        cin >> new_expenses;
                        cout << endl;
                    }
                    fnd.setExpenses(new_expenses);

                    break;
                }
                }
                float profiterol = fnd.getProfit();
                fnd.setProfit(profiterol - new_expenses);
                cout << fnd;
                cout << endl;
                break;
            }
            case 3:
            {
                cout << "Introduceti detaliile legate de Departamentul de Operatiuni:\n";
                OpManagement opmt;
                cin >> opmt;
                cout << endl;
                cout << opmt;
                cout << endl;
                break;
            }
            case 4:
            {
                cout << "Introduceti detaliile legate de Angajatii companiei:\n";
                int nr;
                list <Employees> EList;
                cout << "Cati angajati doriti sa vizualizati: ";
                cin >> nr;
                for (int i = 0; i < nr; i++)
                {
                    Employees empl;
                    cin >> empl;
                    EList.push_back(empl);
                }
                list <Employees> :: iterator it;
                for(it = EList.begin(); it != EList.end(); ++it) cout << endl << (*it) << endl;
                break;
            }
            } // second switch
            cout << "Vreti sa vizualizati si altceva?\n";
            cout << "[0] Nu.\n";
            cout << "[1] Da.\n";
            cin >> decider;
        } // while
        break;
    } // initial case 1
    } // initial switch
    return 0;
}
