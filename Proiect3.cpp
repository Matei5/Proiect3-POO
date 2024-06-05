#include <iostream>
#include <vector>
#include <algorithm>

// ============================== ENUM ==============================

enum class level{
    executive,
    managerial,
    professional,
    tehnical,
    none
};

// ============================== TEMPLATE ==============================

template<typename T>
class Input {
private:
    T variable;
public:
    Input(T variable) : variable(variable) {
        std::cout << "| [0 or x] Exit | [Single digit number] Singleton lambda use | [Character] Factory, cloning and pointers |\n";
        std::cout << "| Input:";
    }
    ~Input() = default;
};

// ============================== SINGLETON ==============================

template<>
class Input<int> {
private:
    int variable;
    std::vector<int> v;

    static Input<int>* instance;
    Input(int variable) : variable(variable) {
        if(variable == 0) return;
        std::cout << "\n| You chose the singleton way! -- Lambda operations |\n";
        create();
    }
public:
    static Input* getInstance(int variable){
        if(instance == nullptr){
            instance = new Input(variable);
        }
        return instance;
    }
    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;
    ~Input() = default;

    void create(){
        std::cout << "| Numar de elemente:";
        int n; std::cin >> n;

        while(n--!=0){
            int x; std::cin >> x;
            v.push_back(x);
        }

        menu();
    };
    void menu(){
        std::cout << "| 0. Exit | 1. Print | 2. Add x to all | 3. Sort | 4. Reverse sort |\n";
        std::cout << "| 5. Erase even numbers | 6. Erase odd numbers |\n";
        std::cout << "| Input:";
        std::cin >> variable;
        switch(variable){
            case 0:
                return;
            case 1:
                std::for_each(v.begin(), v.end(), [](int n){
                    std::cout << n << " ";
                });
                std::cout << std::endl;
                menu();
                break;
            case 2:
                std::cout << "| x =";
                int x; std::cin >> x;
                std::for_each(v.begin(), v.end(), [x](int& n){
                    n = n + x;
                });
                menu();
                break;
            case 3:
                std::sort(v.begin(), v.end(), [](int n1, int n2){
                    return n1 < n2;
                });
                menu();
                break;
            case 4:
                std::sort(v.begin(), v.end(), [](int n1, int n2){
                    return n1 > n2;
                });
                menu();
                break;
            case 5:
                v.erase(std::remove_if(v.begin(), v.end(),[](int x) {
                    return x % 2 == 0;
                }),v.end());
                menu();
                break;
            case 6:
                v.erase(std::remove_if(v.begin(), v.end(),[](int x) {
                    return x % 2 != 0;
                }),v.end());
                menu();
                break;
            default:
                std::cout << "| Input error!\n";
                menu();
                break;
        }
    }
};

Input<int>* Input<int>::instance = nullptr;

// ============================== FACADE ==============================

class Worker {
private:
    static int ID_seq;
    int ID;
    std::string nume;
    std::string prenume;
    level role;
public:
    void setNume(const std::string& nume_){
        nume = nume_;
    }
    void setPrenume(const std::string& prenume_){
        prenume = prenume_;
    }
    void setRole(const level& role_){
        role = role_;
    }
    void setID(){
        ID = ID_seq++;
    }
    int getID(){
        return ID;
    }

    void afisare(){
        std::cout << "| ID: " << ID << " | " << nume << " " << prenume << " <-> Function: ";
        switch(role){
            case level::executive:
                std::cout << "exectuive\n";
                break;
            case level::managerial:
                std::cout << "managerial\n";
                break;
            case level::professional:
                std::cout << "professional\n";
                break;
            case level::tehnical:
                std::cout << "tehnical\n";
                break;
            default:
                break;
        }
    }

    friend std::ostream& operator<<(std::ostream& out, Worker* W){
        W->afisare();
        return out;
    }

    ~Worker(){};
};

int Worker::ID_seq = 0;

class WorkerBuilder{
protected:
    Worker worker;
public:
    virtual ~WorkerBuilder() = default;

    void setNume(const std::string& read) {
        worker.setNume(read);
    }
    void setPrenume(const std::string& read) {
        worker.setPrenume(read);
    }
    void setID(){ worker.setID();}
    virtual void setRole() = 0;

    Worker getWorker(){ return worker;}
};

class ExecutiveBuilder : public WorkerBuilder{
public:
    void setRole() override {
        worker.setRole(level::executive);
    }
};
class ManagerialBuilder : public WorkerBuilder{
public:
    void setRole() override {
        worker.setRole(level::managerial);
    }
};
class ProfessionalBuilder : public WorkerBuilder{
public:
    void setRole() override {
        worker.setRole(level::professional);
    }
};
class TehnicalBuilder : public WorkerBuilder{
public:
    void setRole() override {
        worker.setRole(level::tehnical);
    }
};

class Recruiter {
private:
    WorkerBuilder* builder;
public:
    Recruiter() { builder = nullptr;}
    void setBuilder(WorkerBuilder* read) { builder = read;}

    WorkerBuilder* getBuilder(){
        return builder;
    }

    Worker create(){
        std::string read;
        std::cout << "| Nume:";
        std::cin >> read;
        builder->setNume(read);
        std::cout << "| Prenume:";
        std::cin >> read;
        builder->setPrenume(read);
        builder->setRole();
        builder->setID();
        return builder->getWorker();
    };



    ~Recruiter(){ delete builder;}
};

template<>
class Input<char> {
private:
    char variable;

public:
    Input(char variable) : variable(variable) {
        if(variable == 'x') return;
        std::cout << "\n| You chose the builder way!\n";
        menu();
    }
    ~Input() = default;

    void menu(){
        Recruiter recruiter;

        std::vector<Worker*> angajator;

        while(variable != 'x') {
            std::cout << "\n| x. Exit |\n| Set builder ->  ";
            std::cout << "| a. Executive | b. Managerial | c. Professional | d. Tehnical |\n";
            std::cout << "| e. Angajeaza | f. Sterge angajat | g. Afiseaza vector |\n";
            std::cout << "| Input:";
            std::cin >> variable;

            if (variable== 'x') return;
            else if (variable == 'a') {
                auto *builder = new ExecutiveBuilder();
                recruiter.setBuilder(builder);
            } else if (variable == 'b') {
                auto *builder = new ManagerialBuilder();
                recruiter.setBuilder(builder);
            } else if (variable == 'c') {
                auto *builder = new ProfessionalBuilder();
                recruiter.setBuilder(builder);
            } else if (variable == 'd') {
                auto *builder = new TehnicalBuilder;
                recruiter.setBuilder(builder);
            }
            else if (variable == 'e') {
                if(recruiter.getBuilder() == nullptr){
                    std::cout << "Trebuie sa alegi un builder mai intai!\n";
                    continue;
                }
                std::cout << std::endl;
                auto *toAdd = new Worker();
                *toAdd = recruiter.create();
                angajator.push_back(toAdd);
            }
            else if (variable == 'f') {
                std::cout << "| ID: ";
                int x; std::cin >> x;

                angajator.erase(std::remove_if(angajator.begin(),angajator.end(),[&x](Worker* W){
                    return W->getID() == x;
                }), angajator.end());
            }
            else if (variable == 'g') {
                std::cout << std::endl;
                for_each(angajator.begin(),angajator.end(), [](Worker* W){
                   std::cout << W;
                });
            }
            else {
                std::cout << "| Bad input!\n";
                continue;
            }

        }

    }
};


// ============================== NOT CLASSES ==============================

void menu(){

    Input start = Input("Start");
    std::string aux; std::cin >> aux;

    if(aux.length() > 1)
    {
        std::cout << "| Just a letter or number please!\n";
        menu();
    }
    char x = aux[0];

    if(49 <= x && x <= 57) {
        Input<int> *program = Input<int>::getInstance((int) x - 48);
        return;
    }

    Input program = Input(x);



}

int main(){

    menu();

    return 0;
}