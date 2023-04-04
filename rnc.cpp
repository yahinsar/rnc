#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <deque>
#include <cmath>

using namespace std;

string findInStr(string const& str, int n) {
    if (str.length() < n) {
        return str;
    }
    return str.substr(0, n);
}

void helpFunc() {
    cout << "������� ������� c /h. ���������� ���������:";
    cout << "\n\n/d:<�������������> - ��� ������������� ��� �������������� ������������������. ��������� ���� �������������:\n";
    cout << "\n  st � ����������� ����������� � �������� ���������� (���������: a, b);\n  tr � ����������� ������������� (���������: a, b);\n  ex � ����� ���������������� ������������� (���������: a, b);\n  nr � ���������� ������������� (���������: mu, sigma);\n  gm � ����� ������������� (���������: a, b);\n  ln � ������������� ������������� (���������: a, b);\n  ls � ������������� ������������� (���������: a, b);\n  bi � ������������ �������������. (���������: n, p)\n";
    cout << "\n\n/f:<���_�����> - ��� ����� � ������� �������������������";
    cout << "\n\n/p1:<��������1> - 1-� ��������, �����������, ��� ��������� ��� ��������� �������������.";
    cout << "\n\n/p2:<��������2> - 2-� ��������, �����������, ��� ��������� ��� ��������� �������������.";
    cout << "\n\n/h � ���������� � ���������� ���������� ��������� ������ ���������.\n";
}

vector <double> XtoU(vector <double> allElems) {
    int allElemsSize = allElems.size();
    double max = 2.22507e-308;
    for (int i = 0; i < allElemsSize; i++)
    {
        if (allElems[i] > max)
            max = allElems[i];
    }
    max++;
    for (int i = 0; i < allElemsSize; i++)
    {
        allElems[i] = allElems[i] / max;
    }
    return allElems;
}

vector <double> stFunc(string distributionMethod, string inputFileName, string parameter1, string parameter2, bool defaultVec, bool &errorMessage) {
    ifstream inFile(inputFileName);
    string lineFile;
    vector <double> allElems;
    if (!inFile.is_open()) {
        cout << "������ �������� ����� " << inputFileName << endl;
        errorMessage = true;
        return allElems;
    }
    string getlineElem;
    getline(inFile, getlineElem);
    stringstream ss(getlineElem);
    while (getline(ss, getlineElem, ',')) {
        double intElem = stod(getlineElem);
        allElems.push_back(intElem);
    }
    inFile.close();

    vector <double> allU = XtoU(allElems);
    double a = stod(parameter1);
    double b = stod(parameter2);
    for (int i = 0; i < allU.size(); i++)
    {
        allU[i] = (b * allU[i]) + a;
    }

    return allU;
}

vector <double> trFunc(string distributionMethod, string inputFileName, string parameter1, string parameter2, bool defaultVec, bool& errorMessage) {
    ifstream inFile(inputFileName);
    string lineFile;
    vector <double> allElems;
    if (!inFile.is_open()) {
        cout << "������ �������� ����� " << inputFileName << endl;
        errorMessage = true;
        return allElems;
    }
    string getlineElem;
    getline(inFile, getlineElem);
    stringstream ss(getlineElem);
    while (getline(ss, getlineElem, ',')) {
        double intElem = stod(getlineElem);
        allElems.push_back(intElem);
    }
    inFile.close();

    vector <double> allU = XtoU(allElems);
    double a = stod(parameter1);
    double b = stod(parameter2);
    for (int i = 0; i < allU.size() - 1; i++)
    {
        allU[i] = a + (b * (allU[i] + allU[i + 1] - 1));
    }

    return allU;
}

vector <double> exFunc(string distributionMethod, string inputFileName, string parameter1, string parameter2, bool defaultVec, bool& errorMessage) {
    ifstream inFile(inputFileName);
    string lineFile;
    vector <double> allElems;
    if (!inFile.is_open()) {
        cout << "������ �������� ����� " << inputFileName << endl;
        errorMessage = true;
        return allElems;
    }
    string getlineElem;
    getline(inFile, getlineElem);
    stringstream ss(getlineElem);
    while (getline(ss, getlineElem, ',')) {
        double intElem = stod(getlineElem);
        allElems.push_back(intElem);
    }
    inFile.close();

    vector <double> allU = XtoU(allElems);
    double a = stod(parameter1);
    double b = stod(parameter2);
    for (int i = 0; i < allU.size() - 1; i++)
    {
        if (allU[i] == 0) {
            cout << "���� �� ��������� ����� U = 0. ������ � ���������� ln(U)" << endl;
            errorMessage = true;
            return allU;
        }
        allU[i] = ((b * (-1)) * log(allU[i])) + a;
    }

    return allU;
}

vector <double> nrFunc(string distributionMethod, string inputFileName, string parameter1, string parameter2, bool defaultVec, bool& errorMessage) {
    ifstream inFile(inputFileName);
    string lineFile;
    vector <double> allElems;
    if (!inFile.is_open()) {
        cout << "������ �������� ����� " << inputFileName << endl;
        errorMessage = true;
        return allElems;
    }
    string getlineElem;
    getline(inFile, getlineElem);
    stringstream ss(getlineElem);
    while (getline(ss, getlineElem, ',')) {
        double intElem = stod(getlineElem);
        allElems.push_back(intElem);
    }
    inFile.close();

    if (allElems.size() % 2 != 0)
        allElems.erase(allElems.end() - 1);

    vector <double> allU = XtoU(allElems);
    double mu = stod(parameter1);
    double sigma = stod(parameter2);
    for (int i = 0; i < allU.size(); i+=2)
    {
        if (allU[i] == 1) {
            cout << "���� �� ��������� ����� U = 1. ������ � ���������� ln(1 - U)" << endl;
            errorMessage = true;
            return allU;
        }
        double U1 = allU[i];
        double U2 = allU[i + 1];
        allU[i] = mu + (sigma * sqrt(-2 * log(1 - U1)) * cos(2 * M_PI * U2)); // Z1
        allU[i + 1] = mu + (sigma * sqrt(-2 * log(1 - U1)) * sin(2 * M_PI * U2)); // Z2
    }

    return allU;
}

vector <double> gmFunc(string distributionMethod, string inputFileName, string parameter1, string parameter2, bool defaultVec, bool& errorMessage) {
    ifstream inFile(inputFileName);
    string lineFile;
    vector <double> allElems;
    if (!inFile.is_open()) {
        cout << "������ �������� ����� " << inputFileName << endl;
        errorMessage = true;
        return allElems;
    }
    string getlineElem;
    getline(inFile, getlineElem);
    stringstream ss(getlineElem);
    while (getline(ss, getlineElem, ',')) {
        double intElem = stod(getlineElem);
        allElems.push_back(intElem);
    }
    inFile.close();

    vector <double> allU = XtoU(allElems);
    double a = stod(parameter1);
    double b = stod(parameter2);
    for (int i = 0; i < allU.size(); i++)
    {
        if (allU[i] == 1) {
            cout << "���� �� ��������� ����� U = 1. ������ � ���������� ln(1 - U)" << endl;
            errorMessage = true;
            return allU;
        }
        allU[i] = a - (b * log(1 - allU[i]));
    }

    return allU;
}

vector <double> lnFunc(string distributionMethod, string inputFileName, string parameter1, string parameter2, bool defaultVec, bool& errorMessage) {
    ifstream inFile(inputFileName);
    string lineFile;
    vector <double> allElems;
    if (!inFile.is_open()) {
        cout << "������ �������� ����� " << inputFileName << endl;
        errorMessage = true;
        return allElems;
    }
    string getlineElem;
    getline(inFile, getlineElem);
    stringstream ss(getlineElem);
    while (getline(ss, getlineElem, ',')) {
        double intElem = stod(getlineElem);
        allElems.push_back(intElem);
    }
    inFile.close();

    if (allElems.size() % 2 != 0)
        allElems.erase(allElems.end() - 1);

    vector <double> allU = XtoU(allElems);
    double a = stod(parameter1);
    double b = stod(parameter2);
    for (int i = 0; i < allU.size(); i += 2)
    {
        if (allU[i] == 1) {
            cout << "���� �� ��������� ����� U = 1. ������ � ���������� ln(1 - U)" << endl;
            errorMessage = true;
            return allU;
        }
        double U1 = allU[i];
        double U2 = allU[i + 1];
        double Z1 = a + (b * sqrt(-2 * log(1 - U1)) * cos(2 * M_PI * U2));
        double Z2 = a + (b * sqrt(-2 * log(1 - U1)) * sin(2 * M_PI * U2));
        double bminZ1 = b - Z1;
        if (bminZ1 > 43) {
            cout << "�������� b - Z1 ������ 43. ����� �� ������� double � ���������� exp(b - Z1)" << endl;
            errorMessage = true;
            return allU;
        }
        double bminZ2 = b - Z2;
        if (bminZ1 > 43) {
            cout << "�������� b - Z2 ������ 43. ����� �� ������� double � ���������� exp(b - Z2)" << endl;
            errorMessage = true;
            return allU;
        }
        allU[i] = a + exp(bminZ1);
        allU[i + 1] = a + exp(bminZ2);
    }

    return allU;
}

vector <double> lsFunc(string distributionMethod, string inputFileName, string parameter1, string parameter2, bool defaultVec, bool& errorMessage) {
    ifstream inFile(inputFileName);
    string lineFile;
    vector <double> allElems;
    if (!inFile.is_open()) {
        cout << "������ �������� ����� " << inputFileName << endl;
        errorMessage = true;
        return allElems;
    }
    string getlineElem;
    getline(inFile, getlineElem);
    stringstream ss(getlineElem);
    while (getline(ss, getlineElem, ',')) {
        double intElem = stod(getlineElem);
        allElems.push_back(intElem);
    }
    inFile.close();

    vector <double> allU = XtoU(allElems);
    double a = stod(parameter1);
    double b = stod(parameter2);
    for (int i = 0; i < allU.size(); i += 2)
    {
        if (allU[i] == 1) {
            cout << "���� �� ��������� ����� U = 1. ������ � ���������� U/(1 - U). ������� �� 0." << endl;
            errorMessage = true;
            return allU;
        }
        else if (allU[i] == 0) {
            cout << "���� �� ��������� ����� U = 0. ������ � ���������� ln(U/(1 - U))" << endl;
            errorMessage = true;
            return allU;
        }
        allU[i] = a + (b * log(allU[i] / (1 - allU[i])));
    }

    return allU;
}

double Cnk(double n, double k) {
    double nfact = 1;
    for (int i = 1; i <= n; i++) {
        nfact = nfact * i;
    }
    double nminkfact = 1;
    for (int i = 1; i <= n - k; i++) {
        nminkfact = nminkfact * i;
    }
    double kfact = 1;
    for (int i = 1; i <= k; i++) {
        kfact = kfact * i;
    }
    double res = nfact / (nminkfact * kfact);
    return res;
}

double funcBiF(double y, double n, double p) {
    double resSum = 0;
    for (int k = 0; k <= y; k++)
    {
        resSum = resSum + (Cnk(n, k) * pow(p, k) * pow(1 - p, n - k));
    }
    return resSum;
}

vector <double> biFunc(string distributionMethod, string inputFileName, string parameter1, string parameter2, bool defaultVec, bool& errorMessage) {
    ifstream inFile(inputFileName);
    string lineFile;
    vector <double> allElems;
    if (!inFile.is_open()) {
        cout << "������ �������� ����� " << inputFileName << endl;
        errorMessage = true;
        return allElems;
    }
    string getlineElem;
    getline(inFile, getlineElem);
    stringstream ss(getlineElem);
    while (getline(ss, getlineElem, ',')) {
        double intElem = stod(getlineElem);
        allElems.push_back(intElem);
    }
    inFile.close();

    vector <double> allU = XtoU(allElems);
    double n = stod(parameter1); //n
    double p = stod(parameter2); //p
    if (p > 1 || p < 0) {
        cout << "������. �������� p2 �� ����� ���� > 1 ��� < 0, �.�. ��� �����������." << endl;
        errorMessage = true;
        return allElems;
    }
    for (int i = 0; i < allU.size(); i++)
    {
        double y = 0;
        for (int j = 0; j <= n; j++)
        {
            if (allU[i] > funcBiF(y, n, p)) {
                y++;
                if (j == n) {
                    cout << "������. �� ������� ������ y = (0,...,n), ��� ������� U <= F(y)" << endl;
                    errorMessage = true;
                    return allElems;
                }
            }
            else
                break;
        }
        allU[i] = y;
    }

    return allU;
}

vector <double> setMethod(string distributionMethod, string inputFileName, string parameter1, string parameter2, bool defaultVec, bool &errorMessage) {
    vector <double> distributionResVec;
    if (distributionMethod == "st")
        distributionResVec = stFunc(distributionMethod, inputFileName, parameter1, parameter2, defaultVec, errorMessage);
    else if (distributionMethod == "tr")
        distributionResVec = trFunc(distributionMethod, inputFileName, parameter1, parameter2, defaultVec, errorMessage);
    else if (distributionMethod == "ex")
        distributionResVec = exFunc(distributionMethod, inputFileName, parameter1, parameter2, defaultVec, errorMessage);
    else if (distributionMethod == "nr")
        distributionResVec = nrFunc(distributionMethod, inputFileName, parameter1, parameter2, defaultVec, errorMessage);
    else if (distributionMethod == "gm")
        distributionResVec = gmFunc(distributionMethod, inputFileName, parameter1, parameter2, defaultVec, errorMessage);
    else if (distributionMethod == "ln")
        distributionResVec = lnFunc(distributionMethod, inputFileName, parameter1, parameter2, defaultVec, errorMessage);
    else if (distributionMethod == "ls")
        distributionResVec = lsFunc(distributionMethod, inputFileName, parameter1, parameter2, defaultVec, errorMessage);
    else if (distributionMethod == "bi")
        distributionResVec = biFunc(distributionMethod, inputFileName, parameter1, parameter2, defaultVec, errorMessage);

    return distributionResVec;
}

int main(int argc, char* argv[])
{
    /*
            ��������� ��� �������������� ������������������ ��� 
            � ������ ������������������ ��� � �������� ��������������.
    */
    setlocale(LC_ALL, "Rus");
    string distributionMethod;
    string inputFileName = "rncInput.dat";
    string parameter1;
    string parameter2;
    bool defaultVec = true;
    for (int i = 0; argv[i]; i++)
    {
        string checkStr = string(argv[i]);
        if (findInStr(checkStr, 2) == "/h") {
            helpFunc();
            return 0;
        }
        if (checkStr.length() > 2) {
            string ifStr = findInStr(checkStr, 3);
            string subStr = checkStr.substr(3, checkStr.length());
            if (ifStr == "/d:") {
                distributionMethod = subStr;
            }
            if (ifStr == "/f:") {
                inputFileName = subStr;
            }
            if (ifStr == "/p1") {
                parameter1 = checkStr.substr(4, checkStr.length());
            }
            if (ifStr == "/p2") {
                parameter2 = checkStr.substr(4, checkStr.length());
            }

        }
    }
    bool errorMessage = false;
    vector <double> rncRes = setMethod(distributionMethod, inputFileName, parameter1, parameter2, defaultVec, errorMessage);
    if (errorMessage)
        return 0;
    string outputFileName = distributionMethod + "Output.dat";
    ofstream outFile(outputFileName);
    for (int i = 0; i < rncRes.size(); i++)
    {
        if (i == rncRes.size() - 1)
            outFile << (long long)rncRes[i];
        else
            outFile << (long long)rncRes[i] << ",";
    }
    outFile.close();
    cout << "\nDistribution method: " << distributionMethod << endl;
    cout << "Parameter 1: " << parameter1 << endl;
    cout << "Parameter 2: " << parameter2 << endl;
    cout << "Input File: " << inputFileName << endl;
    cout << "Input File: " << outputFileName << endl;
    return 0;
}