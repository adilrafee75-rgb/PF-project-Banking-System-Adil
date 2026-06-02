/* 
----------- Project by TECH SPINE -----------

Ahmad Zahid     ---------------    BITF25A003
M Huzaifa Shah  ---------------    BITF25A036
Adil Raffe      ---------------    BITF25A051

*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// GLOBAL for Accounts
const int MAX_ACCOUNTS = 10000;
int pin[MAX_ACCOUNTS];
int balance[MAX_ACCOUNTS];
int totalAccounts = 0, option = 0, notedIndex = 0, back = 0, toCompare = 9999;
string name[MAX_ACCOUNTS];
string surname[MAX_ACCOUNTS];
string cnic[MAX_ACCOUNTS];
string email[MAX_ACCOUNTS];
string phone[MAX_ACCOUNTS]; 
string address[MAX_ACCOUNTS];
string account[MAX_ACCOUNTS];
string accountNumber[MAX_ACCOUNTS];

// GLOBAL for Admin Panel
string bankCode = "AZtech12SPINE03"; 

// GLOBAL for Games
char box[3][3]={{'1','2','3'},
                {'4','5','6'},
                {'7','8','9'}};

char currentPLayer='X';
int count=1;
int playAgain=0;

string firstPlayer,secondPlayer;
string F_NAME;
string S_NAME;
string c_PLAYER_NAME;

// All Functions Prototype
int length(int);
void setPin();
void loadAccounts();
bool createNewAccount();
void saveData();
void toContinue();
string toHigherStr(string);
void ticTacToe();
void refreshTicTacToe();
void funTime();
void numberGuess();
void display();
void playerTurn();
bool checkWin();
bool checkDraw();
void assignAccountNumber();
bool loginToAccount();
void afterLogin();
void accountDetails();
void accountSettings();
void updateRecord();
void deleteAccount();
void adminPanel();
void accountsList();
void deposit();

int length(int pin) //Digit Counter 
{
    int count = 0;
    if (pin == 0)
    {
        count = 1;
    }
    else
    {
        while (pin > 0)
        {
            pin /= 10;
            count++;
        }
        
    }
    return count;
}

string toHigherStr(string tempStr)
{
    int i = 0;

    while (tempStr[i] != '\0')
    {
        if (tempStr[i] >= 97 && tempStr[i] <= 122)
        {
            tempStr[i] = tempStr[i] - 32;
        }
        i++;       
    }
    
    return tempStr;
}

void assignAccountNumber()
{
    int tempNum = 0, flag = 0, count = 0;
    string tempStr;
    
    do
    {
        count = 0;
        int digit = 0;
        flag = 0, tempNum = 0;
        for (int i = 0; i < 9; i++)
        {   
            digit = rand() % 10;
            if (count == 0)
            {
                while (digit == 0)
                {
                    digit = rand() % 10;
                }
                count = 1;
            }
            
            tempNum = (tempNum * 10) + digit;
        }
        tempStr = to_string(tempNum);
        for (int j = 0; j < totalAccounts; j++)
        {
            if (tempStr == accountNumber[j])
            {
                flag = 1;
                break;
            }
            
        }
        
    } while (flag == 1);
    
    accountNumber[totalAccounts - 1] = tempStr;
}

void loadAccounts()
{
    ifstream fin;

    fin.open("Accounts.txt");
    if (fin)
    {
        while (getline(fin, accountNumber[totalAccounts], '|') && totalAccounts < MAX_ACCOUNTS)
        {
            string tempPin;
            getline(fin, name[totalAccounts], '|');
            getline(fin, surname[totalAccounts], '|');
            getline(fin, cnic[totalAccounts], '|');
            getline(fin, email[totalAccounts], '|');
            getline(fin, phone[totalAccounts], '|');
            getline(fin, address[totalAccounts], '|');
            getline(fin, tempPin, '|');
            pin[totalAccounts] = stoi(tempPin);
            getline(fin, account[totalAccounts]);

            totalAccounts++;
        }
        
        fin.close();
    }
    
}

void toContinue()
{
    int choice = 0;
    do
    {
        cout << "\n\n                                                                     You want to:" << "\n\n";
        cout << "                                                                     1. Go back to main" << "\n";
        cout << "                                                                     2. Exit" << "\n\n";
        cout << "                                                                     Enter your choice: ";
        cin >> choice;
    } while (choice != 1 && choice != 2);
    if (choice == 2)
    {
        option = 5;
    }
    cout << "\n\n\n";
}

void saveData()
{
    totalAccounts++;
    assignAccountNumber();

    //Acounts handling in files
    ofstream fout;
    int status = 0;
    fout.open ("Accounts.txt");
    if (fout)
    {
        for (int i = 0; i < totalAccounts; i++)
        {
            fout << accountNumber[i] <<  "|" << name[i] << "|" << surname[i] << "|" << cnic[i] << "|" << email[i] << "|" << phone[i] << "|" << address[i] << "|" << pin[i] << "|" << account[i] << "\n";      
        }
        
        fout.close();
        cout << "                                      Congrats! Your account have been registered successfully..." << "\n\n\n";
        cout << "                                      Your Account Number is: " << accountNumber[totalAccounts - 1] << "\n\n\n";
        status = 1;
    }
    else
    {
        cout << "\n\n\n                   ERROR! in managing account details..." << "\n";
        cout << "                   Please contact the helpline or try again...\n\n\n";
    }
    if (status == 1)
    {
        toContinue();                   
    }

}

void setPin() // Setting up the PIN
{
    int pinVerify = 0;

    do
    {
        
        if (pin[notedIndex] != pinVerify)
        {
            cout << "\n\n\n                   Not matched with the previous PIN... TRY AGAIN! " << "\n\n\n";
        }
        cout << "                                                         Please enter a four digit PIN:             |                             "; 
        cin >> pin[notedIndex]; 
        if (length(pin[notedIndex]) == 4)
        {
            cout << "                                                         Please Re-enter the PIN:                   |                             ";
            cin >> pinVerify; 
        }
        else
        {
            cout << "\n\n                   PIN can only contain four digits... TRY AGAIN! " << "\n\n\n";
            pin[notedIndex] = 0; 
            pinVerify = 0;
        }
                    
    } while (pin[notedIndex] != pinVerify || length(pin[notedIndex]) != 4);

}

bool createNewAccount()
{
    cout << "                                                                     ==============================================================" << "\n";
    cout << "                                                                     ||            C R E A T E   N E W   A C C O U N T           ||   " << "\n";
    cout << "                                                                     ==============================================================" << "\n\n\n";

    // Taking the user details
    cout << "                   Please fill in the following details: " << "\n\n";
    cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << "\n";
    cout << "                                                                                          PERSONAL INFORMATION" << "\n";
    cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << "\n\n\n";
    
    cin.ignore(1000, '\n');
    while (name[totalAccounts] == "")
    {
        cout << "                                                         First Name:                                |                             ";
        getline(cin, name[totalAccounts]);
        if (name[totalAccounts] == "")
        {
            cout << "                                                         Please enter the First name:               |                             ";
            getline(cin, name[totalAccounts]);
        }
    }
    cout << "\n";
    cout << "                                                         Surname (optional - Press enter to Skip):  |                             ";
    getline(cin, surname[totalAccounts]);
    if (surname[totalAccounts] == "")
    {
        surname[totalAccounts] = "N/A";
        //cout << surname[totalAccounts];
    }
    cout << "\n";
    cout << "                                                         CNIC number:                               |                             ";
    getline(cin, cnic[totalAccounts]);
    while (cnic[totalAccounts] == "")
    {
        cout << "                                                         Please enter the CNIC:                     |                             ";
        getline(cin, cnic[totalAccounts]);
    }
    cout << "\n\n\n";
    cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << "\n";
    cout << "                                                                                          CONTACT INFORMATION" << "\n";
    cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << "\n\n\n";
    cout << "                                                         Email (optional - Press enter to Skip):    |                             ";
    getline(cin, email[totalAccounts]);
    if (email[totalAccounts] == "")
    {
        email[totalAccounts] = "N/A";
    }
    cout << "\n";
    cout << "                                                         Phone Number:                              |                             ";
    getline(cin, phone[totalAccounts]);
    while (phone[totalAccounts] == "")
    {
        cout << "                                                         Please enter the Phone Number:             |                             ";
        getline(cin, phone[totalAccounts]);
    }
    cout << "\n";
    cout << "                                                         Address:                                   |                             ";
    getline(cin, address[totalAccounts]);
    while (address[totalAccounts] == "")
    {
        cout << "                                                         Please enter the Address:                  |                             ";
        getline(cin, address[totalAccounts]);
    }
    cout << "\n\n\n";
    cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << "\n";
    cout << "                                                                                         SECURITY INFORMATION" << "\n";
    cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << "\n\n\n";
    
    notedIndex = totalAccounts;
    setPin();

    cout << "\n\n\n";
    cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << "\n";
    cout << "                                                                                          ACCOUNT INFORMATION" << "\n";
    cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << "\n\n\n";
    int select = 0;
    
    do
    {
        cout << "                                                                    Your account should be:\n\n";
        cout << "                                                                    1. Current\n";
        cout << "                                                                    2. Saving\n\n";
        cout << "                                                                    Enter your choice: ";
        cin >> select;
        if (select == 1)
        {
            account[totalAccounts] = "Current";
        }
        else if (select == 2)
        {
            account[totalAccounts] = "Saving";
        }
        else
        {
            cout << "\n\n                   Please select 1 or 2...\n\n\n";
        }
        
    } while (select != 1 && select != 2);
    
    cout << "\n\n\n                                                         Account Type:                              |                             " << account[totalAccounts] << "\n\n\n";

    int confirm = 0;
    do
    {
        cout << "                                                                     Are you sure, you have filled the above information correctly ?\n\n";
        cout << "                                                                     1. YES\n";
        cout << "                                                                     2. NO\n\n";
        cout << "                                                                     Enter your choice: ";
        cin >> confirm;
        if (confirm == 1)
        {
           saveData();
           return false;
        }
        else if (confirm == 2)    
        {
            cout << "\n\n\n";
            return true;
        }
        else
        {
            cout << "\n\n                   Kindly enter 1 or 2 only...\n\n\n";
        }
            
    } while (confirm != 1 && confirm != 2);
    
}

bool loginToAccount()
{
    cout << "                                                                    ==============================================================" << "\n";
    cout << "                                                                    ||               L O G I N   T O   A C C O U N T            ||   " << "\n";
    cout << "                                                                    ==============================================================" << "\n\n\n";
    int flag = 0, tempPin = 0;
    string tempAccountNum;
    do
    {
        cout << "                                                                    Enter your Account Number: ";
        cin >> tempAccountNum; 
        
        for (int i = 0; i < totalAccounts; i++)
        {
            if (tempAccountNum == accountNumber[i])
            {
                flag = 1;
                notedIndex = i;
                break;
            }
            
        }

        if (flag == 0)
        {
            cout << "\n\n                   SORRY! No account found with that Account number...\n\n\n";
            toContinue();
            return false;
        }

        int attempt = 0;
        if (flag == 1)    
        {
            do
            {
                cout << "                                                                    Enter your PIN: ";
                cin >> tempPin;

                if (tempPin == pin[notedIndex])
                {
                    return true;
                    break;
                }
                else
                {
                    cout << "\n\n                   Invalid PIN! Try Again... You have " << 4 - attempt << " attempts left !!!\n";
                }
                attempt++;

            } while (attempt < 5);
            
            return false;
        }

    } while (flag != 1 && option != 5);

}

void afterLogin()
{
    int choice = 0, amount = 0;
    string tempAccountNum;
    cout << "\n\n\n";

    cout << "                                                                    ==============================================================" << "\n";
    cout << "                                                                    ||      W E L C O M E   T O   Y O U R   A C C O U N T       ||" << "\n";
    cout << "                                                                    ==============================================================" << "\n\n\n";
    do
    {
        cout << "                                                                    1. Account Balance\n";
        cout << "                                                                    2. Send Money\n";
        cout << "                                                                    3. ATM Withdraw\n";
        cout << "                                                                    4. Account Details\n";
        cout << "                                                                    5. Account Settings\n";
        cout << "                                                                    6. Log out\n\n";
        cout << "                                                                    Enter your choice: ";
        cin >> choice;
        cout << "\n\n\n";

        if (choice == 1)
        {
            cout << "\n\n                                                                    Your Account Balance is:                 " << balance[notedIndex] << "\n\n\n"; 
        }
        else if (choice == 2)
        {
            cout << "\n\n                                                                    Enter the Account Number:                 ";
            cin >> tempAccountNum;

            for (int i = 0; i < totalAccounts; i++)
            {
                if (tempAccountNum == accountNumber[i])
                {
                    toCompare = i;
                    break;
                }
                
            }
            if (toCompare != 9999)
            {
                if (toCompare == notedIndex)
                {
                    cout << "\n\n                 You can't send money to yourself...\n\n\n";
                }
                else
                {
                    cout << "\n\n                                                                    Enter the amount you want to send:                ";
                    cin >> amount;

                    if (amount >= balance[notedIndex])
                    {
                        balance[toCompare] += amount;
                        cout << "\n\n                 Transection is successful...\n\n\n";
                    }
                    else
                    {
                        cout << "\n\n                 Transection failed due to Unsufficient Funds...\n\n\n";
                    }
                    
                }
                
            }
            else
            {
                cout << "\n\n                Account is not found in this bank...\n\n\n";
            }
            
        }
        else if (choice == 3)
        {
            
        }
        else if (choice == 4)
        {
            accountDetails();
            toContinue();
        }
        else if (choice == 5)
        {
            accountSettings();
        }
        else if (choice == 6)
        {
            toContinue();
        }
        else
        {
            cout << "\n\n                   Please enter a valid choice from 1 to 5...\n\n\n";
        }
        
    } while (option != 5 && choice != 6);

    back = 0;
}

void accountDetails()
{
    cout << "                                                                    ==============================================================" << "\n";
    cout << "                                                                    ||                A C C O U N T   D E T A I L S             ||   " << "\n";
    cout << "                                                                    ==============================================================" << "\n\n\n";
    cout << "                                                                    Account Number:                 |               " << accountNumber[notedIndex];
    cout << "\n                                                                    Name:                           |               " << name[notedIndex];
    cout << "\n                                                                    Surname:                        |               " << surname[notedIndex];
    cout << "\n                                                                    CNIC:                           |               " << cnic[notedIndex];
    cout << "\n                                                                    Associated E-Mail:              |               " << email[notedIndex];
    cout << "\n                                                                    Mobile Number:                  |               " << phone[notedIndex];
    cout << "\n                                                                    Address:                        |               " << address[notedIndex];
    cout << "\n                                                                    Account Type:                   |               " << account[notedIndex] << "\n\n\n";         
}

void accountSettings()
{
    int choice = 0, subChoice = 0, select = 0;
    do
    {
        cout << "                                                                    You want to: \n\n";
        cout << "                                                                    1. Change Account Information\n";
        cout << "                                                                    2. Delete Account\n\n";
        cout << "                                                                    Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            do
            {
                cout << "\n\n\n                                                                    Which type of Information you want to change: \n\n";
                cout << "                                                                    1. Personal\n";
                cout << "                                                                    2. Contact\n";
                cout << "                                                                    3. Security\n";
                cout << "                                                                    4. Exit\n\n";
                cout << "                                                                    Enter your choice: ";
                cin >> subChoice;
                if (subChoice == 1)
                {
                    do
                    {
                        select = 0;
                        cout << "\n\n\n                                                                    You want to change: \n\n";
                        cout << "                                                                    1. Name\n";
                        cout << "                                                                    2. Surname\n";
                        cout << "                                                                    3. CNIC\n";
                        cout << "                                                                    4. Exit\n\n";
                        cout << "                                                                    Enter your choice: ";
                        cin >> select;
                        
                        if (select == 1)
                        {
                            cout << "                                                    Enter the name:                 ";
                            cin.ignore();
                            getline (cin, name[notedIndex]);
                
                            while (name[notedIndex] == "")
                            {
                                cout << "\n\n\n                   Name cannot be left empty...\n\n\n";
                                cout << "                                                    Enter the name:                 ";
                                getline (cin, name[notedIndex]);
                            }
                            toContinue();
                            
                        }
                        else if (select == 2)
                        {
                            cout << "                                                    Enter the Surname:                 ";
                            cin.ignore();
                            getline (cin, surname[notedIndex]);
                            cout << "\n\n";
                            if (surname[notedIndex] == "")
                            {
                                surname[notedIndex] = "N/A";
                            }
                            toContinue();
                            
                        }
                        else if (select == 3)
                        {
                            cout << "                                                    Enter the CNIC:                 ";
                            cin.ignore();
                            getline (cin, cnic[notedIndex]);
                            cout << "\n\n";
                            while (cnic[notedIndex] == "")
                            {
                                cout << "\n\n\n                   CNIC cannot be left empty...\n\n\n";
                                cout << "                                                    Enter the CNIC:                 ";
                                getline (cin, cnic[notedIndex]);
                            }
                            toContinue();

                        }
                        else 
                        {
                            cout << "\n\n\n                   Please select 1, 2 or 3 only...\n\n\n";
                        }
                        
                    } while (select != 1 && select != 2 && select != 3 && option != 5);
                    
                }
                else if (subChoice == 2)
                {
                    do
                    {
                        select = 0;
                        cout << "\n\n                                                                    You want to change: \n\n";
                        cout << "                                                                    1. Mobile Number\n";
                        cout << "                                                                    2. E-Mail\n";
                        cout << "                                                                    3. Address\n\n";
                        cout << "                                                                    Enter your choice: ";
                        cin >> select;
                        cout << "\n\n\n";
                        
                        if (select == 1)
                        {
                            cout << "                                                                    Enter the Mobile number:                 ";
                            cin.ignore();
                            getline (cin, phone[notedIndex]);
                            cout << "\n\n";
                            while (phone[notedIndex] == "")
                            {
                                cout << "\n\n\n                   Mobile Number cannot be left empty...\n\n\n";
                                cout << "                                                                    Enter the Mobile Number:                 ";
                                getline (cin, phone[notedIndex]);
                            }
                            toContinue();
                            
                        }
                        else if (select == 2)
                        {
                            cout << "                                                                    Enter the E-Mail:                 ";
                            cin.ignore();
                            getline (cin, email[notedIndex]);
                            cout << "\n\n";
                            if (email[notedIndex] == "")
                            {
                                email[notedIndex] = "N/A";
                            }
                            toContinue();
                            
                        }
                        else if (select == 3)
                        {
                            cout << "                                                                    Enter the Address:                 ";
                            cin.ignore();
                            getline (cin, address[notedIndex]);
                            cout << "\n\n";
                            while (address[notedIndex] == "")
                            {
                                cout << "\n\n\n                   Address cannot be left empty...\n\n\n";
                                cout << "                                                                    Enter the Address:                 ";
                                getline (cin, address[notedIndex]);
                            }
                            toContinue();

                        }
                        else 
                        {
                            cout << "\n                   Please select 1, 2 or 3 only...\n\n\n";
                        }
                        
                    } while (select != 1 && select != 2 && select != 3 && option != 5);

                }
                else if (subChoice == 3)
                {
                    int tempPin = 0, attempts = 0;
                    do
                    {
                        cout << "                                                                    Enter the PIN:                 ";
                        cin >> tempPin;
                        
                        if (tempPin == pin[notedIndex])
                        {
                            setPin();
                            break;   
                        }
                        attempts++;

                    } while (attempts < 5);

                }

            } while (subChoice != 1 && subChoice != 2 && subChoice != 3 && option != 5);
            
            updateRecord();
        }
        else if (choice == 2)
        {
            cout << "\n\n\n                                                                    Are you sure you want to delete the account...\n\n";
            cout << "                                                                                       1. YES\n";
            cout << "                                                                                       2. NO\n\n";
            cout << "                                                                                       Enter you choice: ";
            cin >> subChoice;

            if (subChoice == 1)
            {
                name[notedIndex] = "";
                surname[notedIndex] = "";
                cnic[notedIndex] = "";
                phone[notedIndex] = "";
                email[notedIndex] = "";
                address[notedIndex] = "";
                pin[notedIndex] = 0;
                
                deleteAccount();
            }
            
        }
        
    } while (choice != 1 && choice != 2 && option != 5 && back != 1);

}

void deleteAccount()
{
    totalAccounts--;

    for (int i = notedIndex; i < totalAccounts; i++)
    {
        name[i] = name[i + 1];
        surname[i] = surname[i + 1];
        cnic[i] = cnic[i + 1];
        phone[i] = phone[i + 1];
        email[i] = email[i + 1];
        address[i] = address[i + 1];
        pin[i] = pin[i + 1];
        account[i] = account[i + 1];
        accountNumber[i] = accountNumber[i + 1];

    }
    updateRecord();
    cout << "\n\n\n                   Your Account have been deleted...\n\n\n";
    back = 1;
}

void updateRecord()
{
    ofstream fout;
    int status = 0;
    fout.open ("Accounts.txt");
    if (fout)
    {
        for (int i = 0; i < totalAccounts; i++)
        {
            fout << accountNumber[i] << "|" << name[i] << "|" << surname[i] << "|" << cnic[i] << "|" << email[i] << "|" << phone[i] << "|" << address[i] << "|" << pin[i] << "|" << account[i] << "\n";      
        }
        
        fout.close();
        cout << "\n                   Congrats! Your account have been updated successfully...\n\n\n";
    }
    else
    {
        cout << "\n\n\n                   ERROR! in managing account details...\n";
        cout << "                   Please contact the helpline or try again...\n\n\n";
    }

}


void funTime()
{
    int GameChoice;
    cout << "                                                                    ==============================================================" << "\n";
    cout << "                                                                    ||                   P L A Y   Z O N E                      ||" << "\n";
    cout << "                                                                    ==============================================================" << "\n";
    
    cout << setw(65) <<"Game Categories ." << "\n";
    cout << setw(72) <<"1. Number Guessing Game."<< "\n";
    cout << setw(64) <<"2. Tic Tac toe ."<< "\n\n";

    cout << setw(83) <<"Enter gameNumber you want to play: ";
    cin >> GameChoice;

    if (GameChoice == 1)
    {
        numberGuess();
    }
    
    else if(GameChoice == 2)
    {
        ticTacToe();
    }

}

void numberGuess()
{

    cout <<  "                                                                    ===============================================================" << "\n";
    cout <<  "                                                                    || W E L C O M E  T O  N U M B E R  G U E S S I N G  G A M E ||" << "\n";
    cout <<  "                                                                    ===============================================================" << "\n";
    
    int number_of_guesses=0;
    int rand_Number;
    rand_Number = rand() % 100 + 1;
    int guess;
    do
    {
        cout << setw(50) << "Guess the number: ";
        cin >> guess;
        cout << "\n";
        number_of_guesses++;
        if(guess>rand_Number)
        {
            cout << setw(50) << "Guess is too high.Enter lower number please. " <<endl;
            cout << "\n";
        }
        else if (guess<rand_Number)
        {
            cout << setw(50) << "Guess is too low. Enter higher number please. " <<endl;
            cout << "\n";
        }
        else
        {
            cout <<setw(49) << "Congrats! You Guessed the number in " << number_of_guesses << " attempts." << endl;
        }

    }while(guess!=rand_Number);

    toContinue();
}

void ticTacToe()
{
    cout <<  "                                                                    ==============================================================" << "\n";
    cout <<  "                                                                    ||       W E L C O M E   T O   T I C   T A C  T O E         ||" << "\n";
    cout <<  "                                                                    ==============================================================" << "\n";

    cout << "\n";
    cin.ignore(1000,'\n');

    cout <<setw(74) << "Enter first Player Name : ";
    getline(cin,firstPlayer);

    F_NAME = firstPlayer;

    cout << setw(75) << "Enter Second Player Name : ";
    getline(cin,secondPlayer);


    cout << "\n";
    S_NAME = secondPlayer;

    c_PLAYER_NAME = firstPlayer;

    display();

    while(true)
    {
        playerTurn();

        if(checkWin())
        {
            if(currentPLayer=='X')
            {
                cout << setw(55) << "Congrats " << S_NAME << " you win the game." << endl;
            }
            else
            {
                cout << setw(55) << "Congrats " << F_NAME << " you win the game." << endl;
            }
            break;
        }
        if(checkDraw())
        {
            cout << setw(60) << "It's a draw!" << endl;
            break;
        }

    }

    refreshTicTacToe();
    toContinue();

}
 


void display()
{
    for(int i =0;i<3;i++)
    {
        cout << setw(49);
        for(int j=0;j<3;j++)
        {
            {

                cout << box[i][j] << setw(5);
                if(j<2)
                {
                    cout << "|  ";
                }
            }
        }
        cout << "\n";
        if(i<2)
        {
            cout << setw(65) << " ----|-----|-----  " << "\n";
        }

    }

}

void playerTurn()
{
    int position;
    int rows,cols;

    cout << setw(54) << c_PLAYER_NAME << " it's you're turn . Please Enter a position: ";
    cin >> position;
    
    cout << "\n";

    switch (position)
    {
    case 1:
        rows=0;
        cols=0;
        break;
    case 2:
        rows=0;
        cols=1;
        break;
    case 3:
        rows=0;
        cols=2;
        break;
    case 4:
        rows=1;
        cols=0;
        break;
    case 5:
        rows=1;
        cols=1;
        break;
    case 6:
        rows=1;
        cols=2;
        break;
    case 7:
        rows=2;
        cols=0;
        break;
    case 8:
        rows=2;
        cols=1;
        break;
    case 9:
        rows=2;
        cols=2;
        break;
    default:
        break;
    }
    if(position<1 || position>9 || box[rows][cols]=='X' || box[rows][cols]=='O')
    {
        cout << setw(71) << "Invalid move. Try again." << endl;
        playerTurn();
        return;
    }

    box[rows][cols]=currentPLayer;

    if(currentPLayer=='X')
    {
        currentPLayer='O';
        c_PLAYER_NAME=secondPlayer;

    }
    else
    {
        currentPLayer='X';
        c_PLAYER_NAME=firstPlayer;
    }
    
    display();
    cout << "\n";

}

bool checkWin()
{ 
    // check rows whether they are equal or not

    for(int i=0;i<3;i++)
    {
        if(box[i][0]==box[i][1] && box[i][1]==box[i][2])
        {
            return true;
        }
    }

    // check colums whether they are equal or not

    for(int i=0;i<3;i++)
    {
        if(box[0][i]==box[1][i] && box[1][i]==box[2][i])   
        {
            return true;
        }
    }

    // check dioganols whether they are equal or not

    if(box[0][0]==box[1][1] && box[1][1]==box[2][2])
    {
        return true;
    }

    if(box[0][2]==box[1][1] && box[1][1]==box[2][0])
    {
        return true;
    }
    return false;   
}

bool checkDraw()
{
    // It's check that rows ,colums and diagonal are not of same category.

    for(int i=0;i<3;i++)
    {

        for(int j=0;j<3;j++)
        {
            if(box[i][j]!='X' && box[i][j]!='O')
            {
                return false;
            }

        }

    }

    return true;
}


void refreshTicTacToe()
{
    char newBox[3][3]={{'1','2','3'},
                        {'4','5','6'},
                        {'7','8','9'}};

    for(int i =0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            box[i][j]=newBox[i][j];
        }
    }
    currentPLayer = 'X';
    c_PLAYER_NAME = firstPlayer;
}

void deposit()
{
    int flag = 0;
    string tempAccountNum;

    cout << "\n                                                                    Enter the Account Number of the Account in which you want to deposit money: ";
    cin >> tempAccountNum;
                        
    for (int i = 0; i < totalAccounts; i++)
    {
        if (tempAccountNum == accountNumber[i])
        {
            flag = 1;
            notedIndex = i;
            break;
        }
        
    }

    if (flag == 0)
    {
        cout << "\n\n                   SORRY! No account found with that Account number...\n\n\n";
    }
    else
    {
        int amount;

        cout << "                                                                    Enter the amount to deposite: ";
        cin >> amount;
        balance[notedIndex] += amount;
        cout << "\n\n                   The entered amount is added in the given account...\n\n\n";
    }

}

void accountsList()
{
    cout << "                                                                     ==============================================================" << "\n";
    cout << "                                                                     ||                 A C C O U N T S   L I S T                ||   " << "\n";
    cout << "                                                                     ==============================================================" << "\n\n\n";
    
    cout << "\n\n\n";

    for (int i = 0; i < totalAccounts; i++)
    {
        cout << "ACCOUNT NUMBER: " << accountNumber[i] << " | " << "NAME: " << setw(10) << name[i] << " | " << "MOBILE NUMBER: " << setw(15) << phone[i] << " | " << "BALANCE: " << setw(10) << balance[i] << "\n";   
    }
    
    cout << "\n\n\n";
}

void adminPanel ()
{
    string code;
    int attempt = 0, choice = 0;
    do
    {
        cout << "Enter the Bank code: ";
        cin >> code;

        if (code == bankCode)
        {
            cout << "                                                                     ==============================================================" << "\n";
            cout << "                                                                     ||        W E L C O M E   T O   A D M I N   P A N E L       ||   " << "\n";
            cout << "                                                                     ==============================================================" << "\n\n\n";
            do
            {
                cout << "\n\n\n                                                                    1. Deposit balance\n";
                cout << "                                                                    2. Accounts list\n";
                cout << "                                                                    3. Delete Account\n";
                cout << "                                                                    4. Change Bank Code\n";
                cout << "                                                                    5. Exit\n\n";

                cout << "                                                                    Enter your choice: ";
                cin >> choice;
                cout << "\n\n\n";

                if (choice == 1)
                {
                    deposit();
                    toContinue();
                }
                else if (choice == 2)
                {
                    accountsList();
                    toContinue();
                }
                else if (choice == 3)
                {
                    int flag = 0;
                    string tempAccountNum;

                    cout << "\n                                                                    Enter the Account Number of the Account you want to delete: ";
                    cin >> tempAccountNum;
                                       
                    for (int i = 0; i < totalAccounts; i++)
                    {
                        if (tempAccountNum == accountNumber[i])
                        {
                            flag = 1;
                            notedIndex = i;
                            break;
                        }
                        
                    }

                    if (flag == 0)
                    {
                        cout << "\n\n                   SORRY! No account found with that Account number...\n\n\n";
                    }
                    else
                    {
                        deleteAccount();
                        back = 0;
                    }
                    
                    toContinue();
                }
                else if (choice == 4)
                {
                    cout << "Enter the Previous Bank Code: ";
                    cin >> code;
                    if (code == bankCode)
                    {
                        cout << "Enter the New Code: ";
                        cin >> bankCode;

                        while (bankCode == "")
                        {
                            cout << "\n\n\nBank Code cannot be empty...\n\n\n";

                            cout << "Enter the New Code: ";
                            cin >> bankCode;
                        }
                        
                    }
                    
                    toContinue();
                }
                else if (choice == 5)
                {
                    toContinue();
                }
                else
                {
                    cout << "\n\n\n                   Please enter a valid choice from 1 to 5...\n\n\n";
                }
                
            } while (choice != 5 && option != 5);
            
        }
    
    } while (attempt < 5 && option != 5);
    
}

int main ()
{
    srand(time(0));
    loadAccounts();

    do
    {
        // Primary Interface or Menu
        cout << "                                                                    ==============================================================" << "\n";
        cout << "                                                                    ||                B A N K I N G    S Y S T E M              || " << "\n";
        cout << "                                                                    ==============================================================" << "\n\n\n";
        cout << "                                                                    1. Create New Account" << "\n";
        cout << "                                                                    2. Login to Account" << "\n";
        cout << "                                                                    3. Admin Panel" << "\n";
        cout << "                                                                    4. Fun Time" << "\n";
        cout << "                                                                    5. Exit" << "\n\n\n";

        cout << "                                                                    Please select an option: ";
        cin >> option;
        cout << "\n\n\n"; 

        // Create Account
        if (option == 1)
        {
            bool a = false;
            a = createNewAccount();
            while (a == true)
            {
                a = createNewAccount();
                name[notedIndex] = "";
                surname[notedIndex] = "";
                cnic[notedIndex] = "";
                phone[notedIndex] = "";
                email[notedIndex] = "";
                address[notedIndex] = "";

            }
                  
        }   
        else if(option == 2)
        {
            if (loginToAccount())
            {
                afterLogin();
            }
            
        }
        else if (option == 3)
        {
            adminPanel();
        }
        
        else if (option == 4)
        {
            funTime();
        }
        
    } while (option != 5);

    return 0;
}
