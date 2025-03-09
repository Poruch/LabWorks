#include <string>
#include <iostream>
#include <set>
#include <Windows.h>

#define MYFILE true

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

    int GetValue(std::string key) {
        int hash = GetHash(key);
        int count = 1;
        while ((keys[hash] != key) && (count != length)) {
            hash++;
            count++;
            hash = hash % length;
        }
        if (count == length)
            return -1;
        return hash;
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

    float operator[](int index) {
        return records[index];
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
bool IsByStep = false;
std::string IsLogic = "<>=!&|";


std::set<char> alf = {
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
    '1','2','3','4','5','6','7','8','9','0','+','-','/','*','=','<','>','{','}','(',')','|','&','!',','
};

struct Tree;

typedef Tree* RefTree;
struct Tree {
    std::string Info;
    RefTree leftChild;
    RefTree rightChild;
};
void SetColor(int textColor)
{
    std::cout << "\033[" << textColor << "m";
}
void ResetColor() { std::cout << "\033[0m"; }

void print(std::string s = "") {
    std::cout << s << std::endl;
}
void print(std::string line, int symbol) {
    for (int i = 0; i < line.length(); i++) {
        if (i == symbol) {
            SetColor(92);
            std::cout << line[i];
            ResetColor();
        }
        else
        std::cout << line[i];
    }
    std::cout << std::endl;
}
void print(char s) {
    std::cout << s << std::endl;
}
std::string readLine() {
    std::string line = "";
    std::getline(std::cin,line);
    return line;
}

float ReadValueF() {
    do {
        std::string line = readLine();   
        if(line != "")
            return std::stof(line);
    } while (true);    
}

RefTree Root;
std::string expresion;
int SN;
char scanSymbol;
std::string BUGREPORT = "";
char ErrorSymbol = ' ';
void CLEARREPORT() {
    BUGREPORT = "";
}


std::set<char> digits = { '0','1','2','3','4','5','6','7','8','9' };
std::set<char> letters = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
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
        if (letters.count(scanSymbol)) {
            BUGREPORT += "Цифры не должны иметь буквы\n";
            ErrorSymbol = scanSymbol;
            return;
        }
    }
}

void FNumber(RefTree& R) {
    Number(R);
    if (scanSymbol == separator) {
        R->Info += scanSymbol;
        NextSymbol();
        Number(R);
        if (scanSymbol == separator) {
            BUGREPORT += "Ошибка записи десятичной дроби\n";
            ErrorSymbol = scanSymbol;
            return;
        }
    }
}


void Factor(RefTree& R);
void Addend(RefTree& R);

void Expression(RefTree& R) {
    RefTree O = nullptr;
    R = nullptr;
    if (digits.count(scanSymbol) || letters.count(scanSymbol) || scanSymbol == '(' || scanSymbol == '-' || scanSymbol == '+') {
        if (scanSymbol == '-') {
            InsertNode(O, scanSymbol);
            InsertNode(O->leftChild, '0');
            NextSymbol();
            Addend(O->rightChild);
        }
        else if (scanSymbol == '+'){
            InsertNode(O, scanSymbol);
        }
        else
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
    else {
        BUGREPORT += "Error неверное начало выражения\n";
        ErrorSymbol = scanSymbol;
        return;
    }
}


void Addend(RefTree& R) {
    RefTree O = nullptr;
    R = nullptr;
    if (digits.count(scanSymbol) || letters.count(scanSymbol) || scanSymbol == '(' || scanSymbol == '-' || scanSymbol == '+') {
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
    else {
        BUGREPORT += "Error неверное начало слагаемого\n";
        ErrorSymbol = scanSymbol;
        return;
    }
}

void Factor(RefTree& R) {  
    if (scanSymbol == '-') {
        InsertNode(R, scanSymbol);
        InsertNode(R->leftChild, '0');
        NextSymbol();
        if (scanSymbol == '+') {
            BUGREPORT += "После - должен идти либо - либо число или переменная\n";
            ErrorSymbol = scanSymbol;
            return;
        }
        if (scanSymbol == '-')
            Factor(R->rightChild);        
        if (digits.count(scanSymbol)) {
            InsertNode(R->rightChild, scanSymbol);
            NextSymbol();
            FNumber(R->rightChild);
        }
        else if (letters.count(scanSymbol)) {
            InsertNode(R->rightChild, scanSymbol);
            NextSymbol();
            Variable(R->rightChild);
        }
        else if (scanSymbol == '(') {
            NextSymbol();
            if (SN != 0) {
                Expression(R->rightChild);
                if (SN != 0 && scanSymbol == ')')
                    NextSymbol();
                else {
                    BUGREPORT += "Error нет закрывающей скобки\n";
                    ErrorSymbol = scanSymbol;
                    return;
                }
            }
            else {
                BUGREPORT += "Error не верное значение множителя\n";
                ErrorSymbol = scanSymbol;
                return;
            }
        }
    }
    else if(scanSymbol == '+' || digits.count(scanSymbol) || letters.count(scanSymbol) || scanSymbol == '(') {
        while(scanSymbol == '+')
            NextSymbol();
        if(scanSymbol == '-')
        {
            BUGREPORT += "После + должен идти либо + либо число или переменная\n";
            ErrorSymbol = scanSymbol;
            return;
        }
        if (digits.count(scanSymbol)) {
            InsertNode(R, scanSymbol);
            NextSymbol();
            FNumber(R);
        }
        else if (letters.count(scanSymbol)) {
            InsertNode(R, scanSymbol);
            NextSymbol();
            Variable(R);
        }
        else if (scanSymbol == '(') {
            NextSymbol();
            if (SN != 0) {
                Expression(R);
                if (SN != 0 && scanSymbol == ')')
                    NextSymbol();
                else {
                    BUGREPORT += "Error нет закрывающей скобки\n";
                    ErrorSymbol = scanSymbol;
                    return;
                }
            }
            else {
                BUGREPORT += "Error не верное значение множителя\n";
                ErrorSymbol = scanSymbol;
                return;
            }
        }
    }
    else {
        BUGREPORT += "После знака множетеля должно идти значение\n";
        ErrorSymbol = scanSymbol;
        return;
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
            if (table.GetValue(R->Info) == -1) {
                std::cout << "Введите значние переменной " << R->Info << ": >";
                valueOfVar = ReadValueF();
                table.AddPair(R->Info, valueOfVar);
                return valueOfVar;
            }
            else
                return table[table.GetValue(R->Info)];
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

void Comparable(RefTree& R) {
    RefTree O = nullptr;
    R = nullptr;
    Expression(O);   
    if (O == nullptr)
        return;
    if (scanSymbol == '>' || scanSymbol == '<' || scanSymbol == '=') {
        InsertNode(R, scanSymbol);
        NextSymbol();
        if ((R->Info == "<" || R->Info == ">") && scanSymbol == '=') {
            R->Info += scanSymbol;
            NextSymbol();
        }
        if (scanSymbol == '=') {
            R->Info += scanSymbol;
            NextSymbol();
        }
        if (R->Info == "<" && scanSymbol == '>') {
            R->Info += scanSymbol;
            NextSymbol();
        }
        R->leftChild = O;

        Expression(R->rightChild);
    }
    else {
        if (O->Info != "0") {
            InsertNode(R,O->Info);
        }
        else {
            InsertNode(R, '0');
        }
    }
}

bool Compare(RefTree R) {
    if (R == nullptr) {
        BUGREPORT += "Fatal Error compare";
        return false;
    }
    float leftValue = Calculate(R->leftChild);
    float rightValue = Calculate(R->rightChild);

    if (R->Info == "<") {
        return leftValue < rightValue;
    }
    else if(R->Info == ">") {
        return leftValue > rightValue;
    }
    else if (R->Info == "==") {
        return leftValue == rightValue;
    }
    else if (R->Info == "<=") {
        return leftValue <= rightValue;
    }
    else if (R->Info == ">=") {
        return leftValue >= rightValue;
    }
    else if (R->Info == "<>") {
        return leftValue != rightValue;
    }
    else {
        BUGREPORT += "Fatal Error compare";
        return false;
    }
}
bool isCompareOperation(RefTree R) {
    return R->Info == "<" || R->Info == ">" || R->Info == "<=" || R->Info == ">=" || R->Info == "==" || R->Info == "<>";
}

bool LogicCalculate(RefTree R) {
    if (R == nullptr) {
        BUGREPORT += "Fatal Error compare";
        return false;
    }
    if (R->Info == "0")
        return false;
    if (isFNumber(R->Info))
        return true;
    if (isVariable(R->Info)) {
        if(table.GetValue(R->Info) != -1)
            return table[table.GetValue(R->Info)];
        else {
            float valueOfVar = 0;
            std::cout << "Введите значние переменной " << R->Info << ": >";
            std::string line = readLine();
            valueOfVar = std::stof(line);
            table.AddPair(R->Info, valueOfVar);
            return valueOfVar;
        }
    }
    if (isCompareOperation(R)) {
        return Compare(R);
    }    
    else {        
        if (R->Info == "&")
            return LogicCalculate(R->leftChild) && LogicCalculate(R->rightChild);
        else {
            if (R->Info == "|")
                return LogicCalculate(R->leftChild) || LogicCalculate(R->rightChild);
            else {
                if (R->Info == "=")
                    return LogicCalculate(R->leftChild) == LogicCalculate(R->rightChild);
                
            }
        }
    }
}
void LAddend(RefTree& R);
void LFactor(RefTree& R);

void LExpression(RefTree& R) {
    RefTree O = nullptr;
    R = nullptr;
    if (digits.count(scanSymbol) || letters.count(scanSymbol) || scanSymbol == '{' || scanSymbol == '(' || scanSymbol == '!' || scanSymbol == '-' || scanSymbol == '+') {
        if (scanSymbol == '!') {    
            InsertNode(O, '=');
            InsertNode(O->leftChild, '0');
            NextSymbol();
            LAddend(O->rightChild);
        }
        else
            LAddend(O);
        while ((scanSymbol == '|') && (SN != 0)) {
            InsertNode(R, scanSymbol);
            R->leftChild = O;
            NextSymbol();
            if (SN != 0) {
                LAddend(R->rightChild);
                O = R;
            }
            if (R == nullptr)
                R = O;
        }
        if (R == nullptr)
            R = O;
    }
    else {
        BUGREPORT += "Error неверное начало логического выражения\n";
        ErrorSymbol = scanSymbol;
        return;
    }
}

void LAddend(RefTree& R) {
    RefTree O = nullptr;
    R = nullptr;
    if (digits.count(scanSymbol) || letters.count(scanSymbol) || scanSymbol == '{' || scanSymbol == '(' || scanSymbol == '-' || scanSymbol == '!' || scanSymbol == '+') {
        LFactor(O);
        while ((scanSymbol == '&' || scanSymbol == '=') && (SN != 0)) {
            InsertNode(R, scanSymbol);
            R->leftChild = O;
            NextSymbol();
            if (SN != 0) {
                LFactor(R->rightChild);
                O = R;
            }
        }
        if (R == nullptr)
            R = O;
    }
    else {
        BUGREPORT += "Error неверное начало логического слагаемого\n";
        ErrorSymbol = scanSymbol;
        return;
    }
}

void LFactor(RefTree& R) {
    if (scanSymbol == '!') {
        InsertNode(R, '=');
        InsertNode(R->leftChild,'0');
        NextSymbol();
        if (digits.count(scanSymbol) || letters.count(scanSymbol) || scanSymbol == '(' || scanSymbol == '-' || scanSymbol == '+') {
            Comparable(R->rightChild);
        }
        else {
            if (scanSymbol == '{') {
                NextSymbol();
                if (SN != 0) {
                    LExpression(R->rightChild);
                    if (SN != 0 && scanSymbol == '}')
                        NextSymbol();
                    else {
                        BUGREPORT += "Error нет закрывающей логической скобки\n";
                        ErrorSymbol = scanSymbol;
                        return;
                    }
                }
                else {
                    BUGREPORT += "Error не верное значение множителя\n";
                    ErrorSymbol = scanSymbol;
                    return;
                }
            }
        }
    }
    else if (digits.count(scanSymbol) || letters.count(scanSymbol) || scanSymbol == '(' || scanSymbol == '-' || scanSymbol == '+') {
        Comparable(R);
    }
    else {        
        if (scanSymbol == '{') {
            NextSymbol();
            if (SN != 0) {
                LExpression(R);
                if (SN != 0 && scanSymbol == '}')
                    NextSymbol();
                else {
                    BUGREPORT += "Error нет закрывающей логической скобки\n";
                    ErrorSymbol = scanSymbol;
                    return;
                }
            }
            else {
                BUGREPORT += "Error не верное значение множителя\n";
                ErrorSymbol = scanSymbol;
                return;
            }
        }        
    }
}

int main()
{
    setlocale(LC_ALL,"Rus");
    Root = nullptr;
    std::string* lines = 0;
    int len = 0;
    table.AddPair("True", 1);
    table.AddPair("False", 0);
    table.AddPair("true", 1);
    table.AddPair("false", 0);
    table.AddPair("e", 2.7182818284590452353602874713527);
    table.AddPair("E", 2.7182818284590452353602874713527);
    table.AddPair("pi", 3.1415926535897932384626433832795);
    table.AddPair("Pi", 3.1415926535897932384626433832795);

    //print("Загрузить выражения из файла - все вроме 0 вручную - 0");
    bool isFile = false;//stoi(readLine());
    if (isFile) {
        GetProgram("D:\\Repos\\LabWorks\\TOILab#3\\ProgramLogic.txt", lines, len);
        for (int i = 0; i < len; i++) {
            print("ВЫРАЖЕНИЕ " + std::to_string(i + 1));            
            expresion = lines[i];
            ErrorSymbol = ' ';
            std::remove_if(expresion.begin(), expresion.end(), isspace);
            print(expresion);
            bool isLogic = false;
            for (int i = 0; i < 6; i++) {
                isLogic = isLogic || (expresion.find(IsLogic[i]) != std::string::npos);
            }
            SN = 0;
            scanSymbol = expresion[SN];
            if (isLogic)
                LExpression(Root);
            else
                Expression(Root);
            if (scanSymbol == '\0' && Root != nullptr  && BUGREPORT == "") {
                print("Строка синтаксически правильна");
                if (Root != nullptr) {
                    print("Построено дерево для выражения(вывод в форме ОПЗ) :");
                    WriteExpresion(Root);
                    print();
                    print();
                    print("Результат вычисления: >");
                    if (isLogic)
                        if (LogicCalculate(Root))
                            print("True");
                        else
                            print("False");
                    else
                        print(std::to_string(Calculate(Root)));
                }
            }
            else {
                print("Выражение не верно");
                if (SN > 1) {
                    print("Ошибочный символ - ");
                    if (ErrorSymbol != ' ' && ErrorSymbol != '\0')
                        print(ErrorSymbol);
                    else
                        print("Выражение не полное");
                }
                if (BUGREPORT != "") {                    
                    print(BUGREPORT);
                }
                else {
                    print("Нету следующего операнда");
                }
            }     
            CLEARREPORT();
            print("//////////////////////////////////////////////////////////////////////");
        }
    }
    else {
        system("cls");
        int position = 0;
        expresion = "";
        bool isLogic = false;
        print("Начните вводить выражение");
        char symbol = getchar();
        if (alf.count(symbol)) {
            expresion += symbol;
            position++;
        }
        while (true) {         
            ErrorSymbol = ' ';
            
            system("cls");
            if (expresion != "") {
                print("ВЫРАЖЕНИЕ  (Для ввода нужно ввести символы и нажать Enter, для перевижения указателя влево - '[' вправо - ']' для удаления символа на который указывает указатель - '~')");
                print("Операции для цифр: ( * / + - )");
                print("Операции для сравнения: > < >= <= <> ==");
                print("Операции для логических выражений: & | ! {}");
                print(expresion,position - 1);
                
                    
                isLogic = false;
                for (int i = 0; i < 6; i++) {
                    isLogic = isLogic || (expresion.find(IsLogic[i]) != std::string::npos);
                }
                SN = 0;
                scanSymbol = expresion[SN];
                if (isLogic)
                    LExpression(Root);
                else
                    Expression(Root);
               
                if (scanSymbol == '\0' && Root != nullptr && BUGREPORT == "") {
                    print("Строка синтаксически правильна");
                    if (Root != nullptr) {
                        print("Построено дерево для выражения(вывод в форме ОПЗ) :");
                        WriteExpresion(Root);
                        print("Введите пробел для вычисления");
                    }
                }
                else {
                    print("Выражение не верно");
                    if (SN > 1) {
                        print("Ошибочный символ - ");
                        if (ErrorSymbol != ' ' && ErrorSymbol != '\0')
                            print(ErrorSymbol);
                        else
                            print("Выражение не полное");
                    }
                    if (BUGREPORT != "") {
                        print(BUGREPORT);
                    }
                    else {
                        print("Нету следующего операнда");
                    }
                }
                CLEARREPORT();
                print();
            }
            else {
                print("Начните вводить выражение");
            }            
            symbol = getchar();
            std::cout << '\n';
            std::string tmp = "";
            tmp += symbol;
            if (alf.count(symbol)) {
                if (expresion != "") {
                    expresion.insert(position, tmp);
                    position++;
                }
                else {
                    expresion += tmp;
                    position = 1;
                }
                    
            }         
            else if(symbol == '[') {
                position--;
            }
            else if (symbol == ']') {
                if(position < expresion.length())
                position++;
            }
            else if (symbol == '~') {
                expresion.erase(position-1,1);
                if(position > 1)
                    position--;
            }
            else if (symbol == ' ') {
                print();
                print();
                print("Результат вычисления:> ");
                if (isLogic)
                    if (LogicCalculate(Root))
                        print("True");
                    else
                        print("False");
                else
                    print(std::to_string(Calculate(Root)));
                system("pause");
            }
        }
    }
}
