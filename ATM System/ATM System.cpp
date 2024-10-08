#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

enum enTransactions {
    Quick_Withraw = 1,
    Normal_Withraw = 2,
    Deposit = 3,
    Check_Balace = 4,
    Logout = 5
};

enum enQuick_Withraw {
    twenty = 1,
    fifty = 2 ,
    one_hundred = 3,
    two_hundred = 4,
    four_hundred = 5,
    six_hundred = 6,
    eight_hundred = 7,
    one_thousand = 8,
    Exit = 9
};

struct sClient {
    string Accont_Number;
    string Pincode;
    string Name;
    string Phone;
    double Accont_Balance;
};

bool Invalid_Client = false;

sClient Client;

void LogIn(vector <sClient> vClient);

void ShowChooseTransactions(short choose);

bool CheckNumber(short Number, short from, short to) {
    if (Number >= from && Number <= to) {
        return false;
    }
    return true;
}

short PrintTransactionsScreen() {

    short Choose;
    cout << "====================================================\n";
    cout << "\t\t" << "ATM Main Menue Screen" << endl;
    cout << "====================================================\n";
    cout << "\t" << "[1] Quick Withraw" << endl;
    cout << "\t" << "[2] Normal Withraw" << endl;
    cout << "\t" << "[3] Deposit" << endl;
    cout << "\t" << "[4] Check Balance" << endl;
    cout << "\t" << "[5] Logout" << endl;
    cout << "====================================================\n";
    cout << "Choose what do you want to do ? [1 ato 5] : ";
    cin >> Choose;
    while (CheckNumber(Choose, 1, 5))
    {
        cout << "invalid fonction !!!!!\n\n";
        cout << "please choose another number [1 to 5] : ";
        cin >> Choose;

    }
    return Choose;

}

vector <string> Split(string sentence, string Delim = " ") {

    vector <string> vSentence;
    short pos = 0;
    string s;
    while ((pos = sentence.find(Delim)) != std::string::npos) {
        s = sentence.substr(0, pos);
        if (s != "") {
            vSentence.push_back(s);
        }
        sentence.erase(0, pos + Delim.length());
    }
    if (sentence != "") {
        vSentence.push_back(sentence);
    }
    return vSentence;
}

sClient PrintInformationOfClient(string information, string seperatore = "#//#") {
    sClient Client;
    string s = "";
    vector <string> vClient = Split(information, seperatore);
    Client.Accont_Number = vClient.at(0);
    Client.Pincode = vClient.at(1);
    Client.Name = vClient.at(2);
    Client.Phone = vClient.at(3);
    Client.Accont_Balance = stod(vClient.at(4));
    return Client;
}

vector <sClient> GetinformationFromFileToVector(string NameFile = "MyFile") {

    fstream MyFile;
    vector <sClient> vInformation;
    MyFile.open(NameFile + ".txt", ios::in);
    if (MyFile.is_open()) {
        string Line;
        sClient Client;
        while (getline(MyFile, Line)) {
            if (!Line.empty()) {

                Client = PrintInformationOfClient(Line, "#//#");
                vInformation.push_back(Client);

            }
        }
        MyFile.close();
    }
    return vInformation;
}

vector <string> GetinformationFromFileToVector_string(string NameFile = "MyFile") {

    fstream MyFile;
    vector <string> vInformation;
    MyFile.open(NameFile + ".txt", ios::in);
    if (MyFile.is_open()) {
        string Line;
        while (getline(MyFile, Line)) {
            if (!Line.empty()) {
                vInformation.push_back(Line);
            }
        }
        MyFile.close();
    }
    return vInformation;
}

string PrintInformationOfClient(string seperatore = "#//#") {
    string s = "";
    s += Client.Accont_Number + seperatore + Client.Pincode + seperatore + Client.Name + seperatore + Client.Phone + seperatore + to_string(Client.Accont_Balance);
    return s;
}

void SaveInformationFromvectorInFile(vector <string> vClient, string NameFile = "MyFile") {
    fstream MyFile;
    MyFile.open(NameFile + ".txt", ios::out);
    if (MyFile.is_open()) {
        for (string& i : vClient) {
            if (i != "") {
                MyFile << i << endl;
            }
        }
        MyFile.close();
    }
}

void Deposits(vector <string> vClient, string NameFile = "MyFile") {

    string s = PrintInformationOfClient();
    int Number;
    char tr;
    cout << "\n\nPlease enter deposit amount : ";
    cin >> Number;
    cout << "\n\nAre you sure you want perfrom this transaction ? ( Y / N ) : ";
    cin >> tr;
    cout << endl;
    if (tr == 'Y' || tr == 'y') {
        for (string& C : vClient) {
            if (C == s) {
                Client.Accont_Balance += Number;
                s = PrintInformationOfClient();
                C = s;
            }
        }
        SaveInformationFromvectorInFile(vClient, NameFile);
        cout << "\nDone Successfully new Balance (" << Client.Accont_Balance << ") .\n";
    }
}

short PrintQuickWithdrawScreen() {

    short Choose;
    cout << "====================================================\n";
    cout << "\t\t" << "Quick Withdraw Screen" << endl;
    cout << "====================================================\n";
    cout << "\t" << "[1] 20";
    cout << "\t\t" << "[2] 50" << endl;
    cout << "\t" << "[3] 100";
    cout << "\t\t" << "[4] 200" << endl;
    cout << "\t" << "[5] 400" ;
    cout << "\t\t" << "[6] 600" << endl;
    cout << "\t" << "[7] 800" ;
    cout << "\t\t" << "[8] 1000" << endl;
    cout << "\t" << "[9] Exit" << endl;
    cout << "====================================================\n";
    cout << "Your Balance is : " << Client.Accont_Balance << endl;
    cout << "Choose what do you want to do ? [1 ato 9] : ";
    cin >> Choose;
    while (CheckNumber(Choose, 1, 9))
    {
        cout << "invalid fonction !!!!!\n\n";
        cout << "Your Balance is : " << Client.Accont_Balance << endl;
        cout << "please choose another number [1 to 9] : ";
        cin >> Choose;

    }
    return Choose;

}

short Withraw_Number(short Number) {
    enQuick_Withraw Quick = (enQuick_Withraw)Number;
    switch (Quick)
    {
    case twenty:
        return 20;
        break;
    case fifty:
        return 50;
        break;
    case one_hundred:
        return 100;
        break;
    case two_hundred:
        return 200;
        break;
    case four_hundred:
        return 400;
        break;
    case six_hundred:
        return 600;
        break;
    case eight_hundred:
        return 800;
        break;
    case one_thousand:
        return 1000;
        break;
    case Exit:
        system("cls");
        ShowChooseTransactions(PrintTransactionsScreen());
    }
}

void QuickWithraw(vector <string> vClient, string NameFile = "MyFile") {

    string s = PrintInformationOfClient();
    short Number = Withraw_Number(PrintQuickWithdrawScreen());
    short num;
    char tr;

    while (Number > Client.Accont_Balance) {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.Accont_Balance << endl;
        cout << "Choose what do you want to do ? [1 ato 9] : ";
        cin >> num;
        cout << endl;
        Number = Withraw_Number(num);
    }
    cout << "\n\nAre you sure you want perfrom this transaction ? ( Y / N ) : ";
    cin >> tr;
    cout << endl;
    if (tr == 'Y' || tr == 'y') {
        for (string& C : vClient) {
            if (C == s) {
                Client.Accont_Balance -= Number;
                s = PrintInformationOfClient();
                C = s;
            }
        }
        SaveInformationFromvectorInFile(vClient, NameFile);
        cout << "\nDone Successfully new Balance (" << Client.Accont_Balance << ") .\n";
    }
}

void Withdraw(vector <string> vClient, string NameFile = "MyFile") {

    string s = PrintInformationOfClient();
    int Number;
    char tr;
    do
    {
        cout << "\n\nPlease enter an amount Multiple of {5} : ";
        cin >> Number;
        cout << endl << endl;

    } while (Number % 5 != 0);

    while (Number > Client.Accont_Balance) {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.Accont_Balance << endl;
        cout << "Please enter another amount : ";
        cin >> Number;
    }
    cout << "\n\nAre you sure you want perfrom this transaction ? ( Y / N ) : ";
    cin >> tr;
    cout << endl;
    if (tr == 'Y' || tr == 'y') {
        for (string& C : vClient) {
            if (C == s) {
                Client.Accont_Balance -= Number;
                s = PrintInformationOfClient();
                C = s;
            }
        }
        SaveInformationFromvectorInFile(vClient, NameFile);
        cout << "\nDone Successfully new Balance (" << Client.Accont_Balance << ") .\n";
    }

}

void CheckBalance() {

    cout << "Your Balance is : " << Client.Accont_Balance << endl;
    cout << endl << endl;

}

void ShowChooseTransactions(short choose) {

    enTransactions Transactions;
    Transactions = (enTransactions)choose;
    switch (Transactions)
    {

    case Quick_Withraw:

        system("cls");
        QuickWithraw(GetinformationFromFileToVector_string("C:\\Users\\HP\\source\\repos\\Bank\\Bank\\Client"), "C:\\Users\\HP\\source\\repos\\Bank\\Bank\\Client");
        cout << endl << endl;
        system("pause");
        system("cls");
        ShowChooseTransactions(PrintTransactionsScreen());
        break;

    case Normal_Withraw:

        system("cls");
        cout << "----------------------------------------------------\n";
        cout << "\t\t" << "Normal Withdraw Screen" << endl;
        cout << "----------------------------------------------------\n";
        Withdraw(GetinformationFromFileToVector_string("C:\\Users\\HP\\source\\repos\\Bank\\Bank\\Client"), "C:\\Users\\HP\\source\\repos\\Bank\\Bank\\Client");
        cout << endl << endl;
        system("pause");
        system("cls");
        ShowChooseTransactions(PrintTransactionsScreen());
        break;

    case Deposit:

        system("cls");
        cout << "----------------------------------------------------\n";
        cout << "\t\t" << "Deposit Screen" << endl;
        cout << "----------------------------------------------------\n";
        Deposits(GetinformationFromFileToVector_string("C:\\Users\\HP\\source\\repos\\Bank\\Bank\\Client") , "C:\\Users\\HP\\source\\repos\\Bank\\Bank\\Client");
        cout << endl << endl;
        system("pause");
        system("cls");
        ShowChooseTransactions(PrintTransactionsScreen());
        break;

    case Check_Balace:

        system("cls");
        cout << "----------------------------------------------------\n";
        cout << "\t\t" << "Check Balance Screen" << endl;
        cout << "----------------------------------------------------\n";
        CheckBalance();
        system("pause");
        system("cls");
        ShowChooseTransactions(PrintTransactionsScreen());
        break;

    case Logout:

        system("cls");
        LogIn(GetinformationFromFileToVector("C:\\Users\\HP\\source\\repos\\Bank\\Bank\\Client"));
        break;

    default:

        break;
    }

}

void LogIn(vector <sClient> vClient) {

    cout << "----------------------------------------------------\n";
    cout << "\t\t" << "Login Screen" << endl;
    cout << "----------------------------------------------------\n";
    short num = 0;
    if (Invalid_Client)
        cout << "\nInvalid Account Number/Pin !\n" << endl;
    cout << "Enter Account Number : ";
    cin >> Client.Accont_Number;
    cout << endl;
    cout << "Enter Password : ";
    cin >> Client.Pincode;
    cout << endl;
    for (const sClient& U : vClient) {
        if (U.Accont_Number == Client.Accont_Number && U.Pincode == Client.Pincode) {       
            Client.Accont_Balance = U.Accont_Balance;
            Client.Name = U.Name;
            Client.Phone = U.Phone;
            system("cls");
            Invalid_Client = false;
            ShowChooseTransactions(PrintTransactionsScreen());
            break;
        }
    }
    Invalid_Client = true;
    system("cls");
    LogIn(vClient);

}

int main()
{
    LogIn(GetinformationFromFileToVector("C:\\Users\\HP\\source\\repos\\Bank\\Bank\\Client"));
}
