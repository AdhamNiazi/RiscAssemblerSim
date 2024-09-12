#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <map>

using namespace std;

void printMap(map<string, int>& labelMap)
{
    map<string, int>::iterator itr;
    cout << "*** LABEL LIST ***" << endl;
    for (itr = labelMap.begin(); itr != labelMap.end(); itr++)
    {
        cout << setw(8) << left << itr->first;
        cout << setw(2) << right << setfill('0') << itr->second
             << setfill(' ') << endl;
    }
}
void printVec(vector<string>& vec, vector<unsigned int>& hexVec)
{
    cout << "*** MACHINE PROGRAM ***" << endl;
    for (int i = 0; i < vec.size(); i++)
    {
        cout << setw(2) << right << setfill('0') << i <<":";
        cout << setw(2) << right << hex << uppercase <<  hexVec[i] << "  ";
        cout << vec[i];
        if (i != vec.size() -1)
            cout << endl;
    }
}
bool checkIfLabel(string str)
{
    int i = 0;
    while (i < str.length() && str[i] != ';')
    {
        if (str[i] == ':')
            return true;
        i++;
    }
    return false;
}
string getLabel(string str, map<string, int>& labelMap)
{
    map<string, int>::iterator itr;
    string str2;
    int i = 0;
    //get to the start of the label in case of whitespace before label;
    while (str[i] == ' ')
        i++;
    while (str[i] != ':')
    {
        str2.push_back(str[i]);
        
        if (str[i] == ' ')
        {
            cout << "ERROR: LABELS CANNOT HAVE SPACES" << endl;
            exit(-1);
        }
        i++;
    }
    for (itr = labelMap.begin(); itr != labelMap.end(); itr++)
        {
            if (str2 == itr->first)
            {
                cout << "DUPLICATE LABEL DETECTED";
                exit(-1);
            }
        }
    return(str2);
}
bool checkLabelLine(string str)
{
    int i = 0;
    while (str[i] != ':')
        i++;
    if(i < str.length())
        i++;
    while (i < str.length() && i != ';')
    {
        if (str[i] != ' ')
            return true;
        i++;
    }
    return false;
}
string clearComments(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ';')
            str.erase(i, str.length());
    }
    return str;
}
bool stringWhiteSpace(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != ' ')
            return false;
    }
    return true;
}
bool checkEmptyString(string str)
{
    bool allSpace;
    if (str.empty())
        return true;
    else
    {
        allSpace = stringWhiteSpace(str);
        if (allSpace)
            return true;
    }
    return false;

}
string clearLabels(string str)
{

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ':')
            str.erase(0, i + 1);
    }
    return str;
}
string clearFrontBackSpace(string str)
{
    int i = 0;
    while (i < str.length() && str[i] == ' ')
        i++;
    str.erase(0, i);
    i = str.length();
    while (i > 0 && str[i] == ' ')
        i--;
    str.erase(i, str.length());
    return(str);
}
string clearWhiteSpace(string str)
{
    string str2;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != ' ')
            str2.push_back(str[i]);
    }
    return str2;
}
string lowerCase(string str)
{
    for (int i = 0; i < str.length(); i++)
        str[i] = tolower(str[i]);
    return str;
}
bool validateInput(string str)
{
    bool isEmptyString;
    str = clearComments(str);
    str = clearWhiteSpace(str);
    isEmptyString = checkEmptyString(str);
    if (!isEmptyString)
        return true;
    return false;
}
int getRegisters(string inst) {
    if (inst == "r0")
        return 0;
    else if (inst == "r1")
        return 1;
    else if (inst == "r2")
        return 2;
    else if (inst == "r3")
        return 3;
    else
    {
        cout << "INVALID REGISTER ADRESS" << endl;
        exit(-1);
    }
}
int getLabelLoc(string str, map<string, int>& labelMap, int PC)
{
    map<string, int>::iterator itr;
    itr = labelMap.find(str);
    if (itr == labelMap.end())
    {
        cout << "Label \"" << str 
             << "\" on instruction line " << PC << endl;
        exit(-1);
    }
    return (itr->second);
}
unsigned int translateInst(string str, map<string, int>& labelMap, int PC)
{
    string inst;
    int rn, rm, rd;
    unsigned int total = 00000000;
    stringstream st(str);
    st >> inst;
    if (inst == "add")
    {
        total = 0;
        total <<= 2;
        st >> inst;
        rd = getRegisters(inst);
        st >> inst;
        rn = getRegisters(inst);
        st >> inst;
        rm = getRegisters(inst);
        total += rn;
        total <<= 2;
        total += rm;
        total <<= 2;
        total += rd;
    }
    else if (inst == "and")
    {
        total += 1;
        total <<= 2;
        st >> inst;
        rd = getRegisters(inst);
        st >> inst;
        rn = getRegisters(inst);
        st >> inst;
        rm = getRegisters(inst);
        total += rn;
        total <<= 2;
        total += rm;
        total <<= 2;
        total += rd;
    }
    else if (inst == "not")
    {
        total += 2;
        total <<= 2;
        st >> inst;
        rd = getRegisters(inst);
        st >> inst;
        rn = getRegisters(inst);
        total += rn;
        total <<= 4;
        total += rd;
    }
    else if (inst == "bnz")
    {
        total += 3;
        total <<= 6;
        st >> inst;
        rd = getLabelLoc(inst, labelMap, PC);
        total += rd;
    }
    else
    {
        cout << "INVALID OPERAND" << endl;
        exit(-1);
    }
    return total;
}
int main(int argc, char* argv[])
{
    cout << "Your command line prompt> ";
    for (int i = 0; i < argc; i++)
    {
        cout << argv[i] << " ";
    }
    cout << endl;
    vector<string> stringVec;
    vector<unsigned int> hexVec;
    map<string, int> labelMap;
    int PC = 0;
    unsigned int total;
    bool isLabel, insPresent, validInst;
    string stringIn = "", labelName = "";
    bool lSet = false;
    string l = "NULL";
    if (argc >= 4)
    {
        l = argv[3];
        if (l == "-l")
            lSet = true;
    }
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        cout << "Error Opening Input File" << endl;
        exit(-1);                          
    }
    while (!inputFile.eof())
    {
        getline(inputFile, stringIn);
        validInst = validateInput(stringIn);
        if (validInst)
        {
            isLabel = checkIfLabel(stringIn);
            if (isLabel)
            {
                stringIn = clearWhiteSpace(stringIn);
                stringIn = clearComments(stringIn);
                labelName = getLabel(stringIn, labelMap);
                insPresent = checkLabelLine(stringIn);
                labelMap.insert(pair<string, int>(labelName, PC));
                if (insPresent)
                    PC++;
            }
            else
                PC++;
        }
    }
    inputFile.close();
    ifstream file2In(argv[1]);
    if (!file2In.is_open())
    {
        cout << "Error Opening Input File" << endl;
        exit(-1);
    }
    PC = 0;
    ofstream outFile;
    outFile.open(argv[2]);
    if (!outFile.is_open())
    {
        cout << "ERROR OPENING OUTPUT FILE" << endl;
        exit(-1);
    }
    outFile << "v2.0 raw";
    bool isEmptyString;
    while (!file2In.eof())
    {
        getline(file2In, stringIn);
        validInst = validateInput(stringIn);
        if (validInst)
        {
            stringIn = clearComments(stringIn);
            stringIn = clearLabels(stringIn);
            stringIn = clearFrontBackSpace(stringIn);
            stringIn = lowerCase(stringIn);
            isEmptyString = checkEmptyString(stringIn);
            if (!isEmptyString)
            {
                stringVec.push_back(stringIn);
                total = translateInst(stringIn, labelMap, PC);
                hexVec.push_back(total);
                outFile << endl << hex << setw(2) << setfill('0')
                        << uppercase << total;
            }
            PC++;
        }
    }
    if (lSet)
    {
        printMap(labelMap);
        printVec(stringVec, hexVec);
    }
    file2In.close();
    outFile.close();
    return 0;
}