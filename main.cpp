#include <bits/stdc++.h>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <fstream>
#include <chrono>
#include <ctime>

using namespace std;

const int consoleWidth = 80, consoleHeight = 200;

class admin;
class user;
void head();
void setConsoleSize(int width, int height);                 // Function to set the console window size
string centerText(const string& text);           //Function to center the text


class admin{

    string pass;

    protected:
        vector<string> arr;
        string element;
        string name, cont, addr, roomType, inDate, outDate, bill, foodItem;
        int roomNo, i = 0, temp = 0, foodPrice, foodNo;

    public:
        char ans;
        void adminLogin();
        void adminOptions();
        void checkIn();
        void checkOut();
        void mMenu();
        void guestList();

}ad;

class user : public admin{

    public:
        void userLogin();
        int showMenu();
        int bill;
        void viewBill();
    
}us;


int main(){

    int ans;
    setConsoleSize(consoleHeight * 8, consoleWidth * 8);
    
    do{
        head();
        cout << centerText("Check-in and Debug Out: Unwind and Code Away!") << endl <<endl;
        cout << centerText("1. User Login") << endl;
        cout << centerText("2. Staff Login") << endl;
        cout << centerText("3. Exit") << endl;
        cout << setw(80) << "" << "Enter you choice: ";
        cin >> ans;

        if(ans == 1){

        }
        else if(ans == 2){
            ad.adminLogin();
        }

        else{
            head();
            cout << "WRONG CHOICE!!!";
            cin.get();
        }
    }while(ans != 3);
    cin.get();  //waits for user input as to keep program running and not exiting after showing output
    cin.get();
}   

void setConsoleSize(int width, int height) {
    HWND console = GetConsoleWindow();
    RECT rect;
    GetWindowRect(console, &rect);

    MoveWindow(console, rect.left, rect.top, width, height, TRUE);
    SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_SIZEBOX);
}

string centerText(const string& text) {
    int totalPadding = consoleHeight - text.length();
    int leftPadding = totalPadding / 2;
    int rightPadding = totalPadding - leftPadding;
    return string(leftPadding, ' ') + text + string(rightPadding, ' ');
}

void head(){
    system("CLS");
    cout << "**************************************************************************************************************************************************************************************************" << endl;
    cout << centerText("THE DEBUGGING DEN") << endl;
    cout << "**************************************************************************************************************************************************************************************************" << endl << endl;
}

void admin :: adminLogin(){

    head();
    cout << "\t\t\tEnter Login:";
    cin >> pass;
    //Sleep(100);
    ifstream fin("pass.txt");

    fin.open("pass.txt");

    if(!fin.is_open())
        cout << "ERROR!!!" << "\t" << "Couldn't confirm password, please contact admin.";
    
    string line((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());

    if(pass == line){
        cout <<centerText("Correct...");
        Sleep(5);
        adminOptions();
        }
    
    else{
        cout <<centerText("WRONG PASSWORD") << endl;
        Sleep(5);
        cout << centerText("EXITING");
        Sleep(3000);
        cout << ".";
        Sleep(3000);
        cout << ".";
        Sleep(3000);
        cout << ".";
        Sleep(3000);
        cout << ".";
        Sleep(3000);
        exit(1);
    }
}

void admin :: adminOptions(){

        do{
        head();
        cout << centerText("1. Guest Check-in")<<endl;
        cout << centerText("2. Guest Check-out")<<endl;
        cout << centerText("3. Manage Menu")<<endl;
        cout << centerText("4. Display Guest-List")<<endl;
        cout << centerText("5. Exit")<<endl;
        cout << "\t\t\t\t\tEnter Choice: ";
        cin >> ans;

        switch(ans){
            case '1':{
                checkIn();
                break;
            }
            case '2':{
                checkOut();
                break;
            }
            case '3':{
                mMenu();
                break;
            }
            case '4':{
                guestList();
                break;
            }
            default:{
                head();
                cout << "WRONG CHOICE!!!";
                cin.get();
            }
        }}while(ans != '5');
}

void admin :: checkIn(){
    head();
    fstream fout;
    
     // Get the current time
    time_t currentTime = time(nullptr);
    // Convert the current time to a string in the desired format
    tm* timeInfo = localtime(&currentTime);
    ostringstream oss;
    oss << put_time(timeInfo, "%D-%m-%y"); // Format: DD-MM-YYY
    inDate = oss.str();

    cin.get();

    fout.open("room.txt",ios::in);
    fout >> roomNo;
    fout.close();

    fout.open("room.txt", ios::out | ios::trunc);
    fout << roomNo + 1;
    fout.close();

    cout << "Room No.: " << roomNo << endl;
    
    cout << "Enter Room Type: ";
    getline(cin,roomType);

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Address: ";
    getline(cin, addr);

    cout << "Enter Contact No: ";
    getline(cin, cont);

    bill = outDate = "Not Avail.";

    fout.open("guestList.csv", ios::out | ios::app);

    if(!fout.is_open())
        cout << "ERROR!!!" << "\t" << "Couldn't open Guest-List, please contact admin.";

    fout << roomNo << "," << roomType << "," << inDate << "," << outDate << "," << name << "," << addr << "," << cont << "," << bill << "\n";

    fout.close();
}

void admin :: checkOut(){

}

int user :: showMenu(){

    head();

    fstream fout;

    fout.open("menu.csv", ios :: in);

    cout << left << setw(10) << "" << setw(20) << "ITEM No." << setw(30) << "FOOD ITEM" << "PRICE" << endl << endl;

    temp = 1;

    string line;
    while (getline(fout, line)){ // Read each line from the file
        ++temp;
        istringstream iss(line);
        string element;
        while (getline(iss, element, ',')) {
            arr.push_back(element); // Print each element
            ++i;
        }
        cout << left << setw(10) << "" << setw(20) << arr[0] << setw(30) << arr[1] << arr[2] << endl << endl;
        i = 0;
        arr.clear();
    }
    i = 0;
    fout.close();

    return temp;
}

void admin :: mMenu(){

    cin.ignore();

    temp = us.showMenu();

    fstream fout;

    cout << endl << endl << endl << left << setw(80) << "" << "1. Code a Dish :: Add" << endl << setw(80) << "" << "2. Menu Malfunction? Debug :: Delete" <<endl<<endl;
    cout << left << setw(80) << "" << "Enter your Choice: ";
    cin >> ans;

    fout.open("menu.csv", ios :: in | ios :: out | ios :: app);

    switch(ans){
        case '1':{

            cout << endl << endl << "Item No.: " << temp << endl;

            cin.ignore();

            cout << "Enter Food Name: ";
            getline(cin, foodItem);

            cout << endl << "Enter Price: ";
            cin >> foodPrice;

            fout << temp << "," << foodItem << "," << foodPrice << "\n";
            
            break;
        }

        case '2':{
            cout << endl << endl << "Enter Item No.: ";
            cin >> foodNo;

            vector<string> tempData;
            string line;

            // Read the file and store data in tempData excluding the line to delete
            while (getline(fout, line)) {
                istringstream iss(line);
                string element;
                getline(iss, element, ',');
                int currentFoodNo = stoi(element);
                if (currentFoodNo != foodNo) {
                    // Modify the item number in the line to maintain the order
                    line.replace(0, element.size(), to_string(tempData.size() + 1));
                    tempData.push_back(line);
                }
            }

            fout.close();

            fout.open("menu.csv", ios::out | ios::trunc);
            for (const string& data : tempData) {
                fout << data << endl;
            }

            cout << "Item No. " << foodNo << " has been debugged from the menu." << endl;
            break;
        }

        default :
            cout << "Wrong Choice!!!";
    }

    fout.close();
   
}

void admin :: guestList(){

    head();

    fstream fout;
    fout.open("guestList.csv", ios :: in);

    if(!fout.is_open())
        cout << "ERROR!!!" << "\t" << "Couldn't open Guest-List, please contact admin.";
    
    cout << left << setw(10)<< "" << setw(20) << "Room No." << setw(21)  << "Room Type" << setw(15) << "Check-In" << setw(15) << "Check-Out" << setw(20) << "Guest Name" << setw(60) << "Address" << setw(20) << "Contact No." << setw(20) << "Total Bill" << endl << endl;

    string line;

    while (getline(fout, line)){ // Read each line from the file
        istringstream iss(line);
        string element;
        while (getline(iss, element, ',')) { // Split the line by tab ('\t')
            arr.push_back(element); // Print each element
            ++i;
        }
        cout << left << setw(10)<< "" << setw(20) << arr[0] << setw(21) << arr[1] << setw(15) << arr[2] << setw(15) << arr[3] << setw(20) << arr[4] << setw(60) << arr[5] << setw(20) << arr[6] <<setw(20) << arr[7] << endl;
        
        arr.clear();
        i = 0;
    }
    cin.get();
    cin.get();
    fout.close();
}

