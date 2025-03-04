#include <string>
#include <iostream>
#include <vector>
#include <set>

struct HashTable {
public:
    HashTable(size_t size) {
        length = size;
        records = new float[size];
        keys = new std::string[size];
        for (size_t i = 0; i < length; i++)
        {
            records[i] = 0;
            keys[i] = "";
        }
    }

    float GetValue(std::string key) {
        int hash = GetHash(key);
        int count = 1;
        while (keys[hash] != key && count != length) {
            hash++;
            count++;
            hash = hash % length;
        }
        if (count == length)
            return -1;
        return records[hash];
    }

    void AddPair(std::string key, float value) {
        int hash = GetHash(key);
        int count = 1;
        while (keys[hash] != "" && count != length) {
            hash++;
            count++;
            hash = hash % length;
        }
        if (count == length)
            return;
        if (keys[hash] == key) {
            return;
        }
        records[hash] = value;
        keys[hash] = key;
    }
private:
    int GetHash(std::string key) {
        int sum = 0;
        for (int i = 0; i < key.length(); i++) {
            sum += abs(key[i]);
        }

        int hash = sum % length;
        return hash;
    }


    size_t length;
    float* records;
    std::string* keys;
};
char separator = ',';
HashTable table = HashTable(100);

std::set<char> alf = {
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
    '1','2','3','4','5','6','7','8','9','0','+','-','/','*','=','<','>'
};

struct Tree;

typedef Tree* RefTree;
struct Tree {
    std::string Info;
    RefTree leftChild;
    RefTree rightChild;
};

void print(std::string s = "") {
    std::cout << s << std::endl;
}

std::string readLine() {
    std::string line = "";
    std::getline(std::cin,line);
    return line;
}

RefTree Root;
std::string expresion;
int SN;
char scanSymbol;

std::set<char> digits = { '0','1','2','3','4','5','6','7','8','9' };
std::set<char>letters = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                          'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' }; 
bool isNumber(std::string line) {    
    for (int i = 0; i < line.length(); i++) {
        if (!digits.count(line[i]))
            return false;
    }
    return true;
}

bool isFNumber(std::string line) {
    int i = 0;
    while (line[i] != separator && i < line.length()) {
        if (!digits.count(line[i]))
            return false;
        i++;
    }
    if (i >= line.length())
        return true;
    i++;
    while (i < line.length()) {
        if (!digits.count(line[i]))
            return false;
        i++;
    }
    return true;
}


bool isVariable(std::string line) {
    return letters.count(line[0]);
}

void InsertNode(RefTree& R, std::string s) {
    R = new Tree();
    R->Info = s;
    R->leftChild = nullptr;
    R->rightChild = nullptr;
}
void InsertNode(RefTree& R, char s) {
    R = new Tree();
    R->Info = s;
    R->leftChild = nullptr;
    R->rightChild = nullptr;
}
void WriteExpresion(RefTree R) {
    if (R != nullptr) {
        WriteExpresion(R->leftChild);
        WriteExpresion(R->rightChild);
        std::cout << " " << R->Info << " ";
    }
}

void NextSymbol() {
    if (SN < expresion.length()) {
        SN++;
        scanSymbol = expresion[SN];
        if(scanSymbol)
    }
    else
        SN = -1;
}

void Variable(RefTree& R) {
    while (letters.count(scanSymbol) || digits.count(scanSymbol)) {
        R->Info += scanSymbol;
        NextSymbol();
    }
}
void Number(RefTree& R) {
    while (digits.count(scanSymbol)) {
        R->Info += scanSymbol;
        NextSymbol();
    }
}

void FNumber(RefTree& R) {
    Number(R);
    if (scanSymbol == separator) {
        R->Info += scanSymbol;
        NextSymbol();
        Number(R);
    }
}


void Factor(RefTree& R);
void Addend(RefTree& R);

void Expresion(RefTree& R) {
    RefTree O = nullptr;
    R = nullptr;
    if (digits.count(scanSymbol) || letters.count(scanSymbol) || scanSymbol == '(') {
        Addend(O);
        while ((scanSymbol == '+' || scanSymbol == '-') && (SN != 0)) {
            InsertNode(R, scanSymbol);
            R->leftChild = O;
            NextSymbol();
            if (SN != 0) {
                Addend(R->rightChild);
                O = R;
            }    
            if (R == nullptr)
                R = O;
        }
        if (R == nullptr)
            R = O;
    }
    else
        std::cout << "Error неверное начало выражения\n";
}


void Addend(RefTree& R) {
    RefTree O = nullptr;
    R = nullptr;
    if (digits.count(scanSymbol) || letters.count(scanSymbol) || scanSymbol == '(') {
        Factor(O);
        while ((scanSymbol == '*' || scanSymbol == '/') && (SN != 0)) {
            InsertNode(R,scanSymbol);
            R->leftChild = O;
            NextSymbol();
            if (SN != 0) {
                Factor(R->rightChild);
                O = R;
            }            
        }
        if (R == nullptr)
            R = O;
    }
    else
        std::cout << "Error неверное начало слагаемого\n";
}

void Factor(RefTree& R) {
    if (digits.count(scanSymbol)) {
        InsertNode(R,scanSymbol);
        NextSymbol();
        FNumber(R);        
    }
    else {
        if (letters.count(scanSymbol)) {
            InsertNode(R,scanSymbol);
            NextSymbol();
            Variable(R);
        }
        else {
            if (scanSymbol == '(') {
                NextSymbol();
                if (SN != 0) {
                    Expresion(R);
                    if (SN != 0 && scanSymbol == ')')
                        NextSymbol();
                    else
                        std::cout << "Error нет закрывающей скобки\n";
                }
                else
                    std::cout << "Error не верное значение множителя\n";
            }
        }
    }
}

float Calculate(RefTree R) {
    float valueOfVar = 0;
    if (R == nullptr)
        return 0;
    if (isFNumber(R->Info)) {
        return std::stof(R->Info);
    }
    else {
        if (isVariable(R->Info)) {
            print();
            if (table.GetValue(R->Info) == -1) {
                std::cout << "Введите значние переменной " << R->Info << ": >";
                valueOfVar = std::stof(readLine());
                table.AddPair(R->Info, valueOfVar);
                return valueOfVar;
            }
            else
                return table.GetValue(R->Info);
        }
        else {
            if (R->Info == "+")
                return Calculate(R->leftChild) + Calculate(R->rightChild);
            else {
                if (R->Info == "-")
                    return Calculate(R->leftChild) - Calculate(R->rightChild);
                else {
                    if (R->Info == "*")
                        return Calculate(R->leftChild) * Calculate(R->rightChild);
                    else                        
                        return Calculate(R->leftChild) / Calculate(R->rightChild);
                }
            }
        }
    }

}

#include <fstream>
void GetProgram(std::string fileName,std::string*& lines,int& len) {
    std::ifstream file(fileName);
    len = 0;
    std::string s;
    if (file.is_open()) {
        while (std::getline(file, s)) {
            (len)++;
        }
    }
    if (len == 0)
        throw "Не удалось открыть файл или он пустой";
    file.close();
    file = std::ifstream(fileName);
    delete lines;
    lines = new std::string[len];
    
    int i = 0;
    while (i < len) {
        std::getline(file, s);
        lines[i] = s;
        i++;
    }
    
    file.close();
}


int main()
{
    setlocale(LC_ALL,"Rus");
    Root = nullptr;
    std::string* lines = 0;
    int len = 0;
    GetProgram("D:\\Repos\\LabWorks\\TOILab#3\\Program.txt",lines,len);
    for (int i = 0; i < len; i++) {
        print("ВЫРАЖЕНИЕ " + std::to_string(i + 1));
        expresion = lines[i];
        std::remove_if(expresion.begin(), expresion.end(), isspace);
        SN = 0;
        scanSymbol = expresion[SN];
        Expresion(Root);
        if (SN == -1) {
            print("Строка синтаксически правильна");
        }
        else {
            print("Строка синтаксически правильна");
        }

        if (Root != nullptr) {
            print("Построено дерево для выражения(вывод в форме ОПЗ) :");
            WriteExpresion(Root);
            print();
            print();
            print("Результат вычисления: >");
            print(std::to_string(Calculate(Root)));
        }
        print("//////////////////////////////////////////////////////////////////////");
    }
}
