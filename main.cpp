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
        int roomNo, i = 0, temp = 0, foodNo;
        double foodPrice;

    public:
        char ans;
        void adminLogin();
        void adminOptions();
        void checkIn();
        void checkOut();
        void mMenu();
        void guestList();
        int showMenu();

}ad;

class user : public admin{

    int roomN;  

    public:
        void userLogin();
        void userOptions();
        void viewBill();
        void orderFood();
        void faq();
    
}us;


int main(){

    int ans;
    setConsoleSize(consoleHeight * 8, consoleWidth * 8);
    
    do{
        head();
        cout << centerText("Check-in and Debug Out: Unwind and Code Away!") << endl <<endl << endl;
        cout << centerText("1. User Login") << endl << endl;
        cout << centerText("2. Staff Login") << endl <<endl;
        cout << centerText("3. Exit") << endl << endl <<endl;
        cout << setw(80) << "" << "Enter you choice: ";
        cin >> ans;

        if(ans == 1){
            us.userLogin();
        }
        else if(ans == 2){
            ad.adminLogin();
        }

        else if(ans == 3){
            exit(1);
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
    return string(leftPadding, ' ') + text;
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
        cout << centerText("Enter Choice: ");
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
    oss << put_time(timeInfo, "%d-%m-%y"); // Format: DD-MM-YYY
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

int admin::showMenu() {
    head();

    fstream fout;
    fout.open("menu.csv", ios::in);

    cout << left << setw(10) << "" << setw(20) << "ITEM No." << setw(30) << "FOOD ITEM" << "PRICE" << endl << endl;

    temp = 1;
    string line;
    while (getline(fout, line)) {
        ++temp;
        istringstream iss(line);
        string element;
        while (getline(iss, element, ',')) {
            arr.push_back(element);
        }
        cout << left << setw(10) << "" << setw(20) << arr[0] << setw(30) << arr[1] << stod(arr[2]) << endl << endl;
        arr.clear();
    }
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

void user :: userLogin(){

    head();
            cout << "\t\t\tEnter Room No.: ";

            cin >> roomN;

            ifstream fin("guestList.csv");
            if (!fin.is_open()) {
                cout << "ERROR!!!" << "\t" << "Couldn't open Guest-List, please contact admin." << endl;
                cin.get();
                cin.get();
            }

            bool found = false;
            string line;
            while (getline(fin, line)) {
                istringstream iss(line);
                string element;
                getline(iss, element, ',');
                int currentRoomNo = stoi(element);
                if (currentRoomNo == roomN) {
                    found = true;
                    break;
                }
            }

            fin.close();

            if (found){
                Sleep(3);
            } else {
                head();
                cout << centerText("Room number not found. Please try again or exit.") << endl;
                cin.get();
            }

}

void user :: userOptions(){

        do{
        head();
        cout << left << setw(80) << "" << "1. View Menu" << endl;
        cout << left << setw(80) << "" << "2. Order Food" << endl;
        cout << left << setw(80) << "" << "3. View Bill" << endl;
        cout << left << setw(80) << "" << "4. FAQs" << endl;
        cout << left << setw(80) << "" << "5. Exit" << endl;
        cout << left << setw(80) << "" << "Enter Choice: ";
        cin >> ans;

        switch(ans){
            case '1':{
                showMenu();
                break;
            }
            case '2':{
                orderFood();
                break;
            }
            case '3':{
                viewBill();
                break;
            }
            case '4':{
                faq();
                break;
            }
            default:{
                head();
                cout << "WRONG CHOICE!!!";
                cin.get();
            }
        }}while(ans != '5');
}

void user::orderFood() {
    head();
    cout << centerText("Order Food") << endl << endl;

    // Show the menu to the user
    int menuItems = showMenu();

    // Ask the user to choose an item
    int choice;
    cout << "Enter the item number to order (1-" << menuItems - 1 << "): ";
    cin >> choice;

    // Check if the input is valid
    if (choice < 1 || choice >= menuItems) {
        cout << "Invalid choice. Please try again." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        cin.get();
        return;
    }

    // Get the selected food item and price
    ifstream fin("menu.csv");
    if (!fin.is_open()) {
        cout << "ERROR!!!" << "\t" << "Couldn't open Menu file, please contact admin." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        cin.get();
        return;
    }

    string line;
    int currentItem = 1;
    string foodItem;
    string priceStr;
    double foodPrice = 0.0;

    while (getline(fin, line)) {
        if (currentItem == choice) {
            istringstream iss(line);
            getline(iss, foodItem, ',');
            getline(iss, foodItem, ',');
            getline(iss, priceStr, ',');
            break;
        }
        // currentItem++;
    }
    fin.close();

    // Convert the priceStr to a double using stringstream
    foodPrice = 0.0;
    istringstream issPrice(priceStr);
    if (!(issPrice >> foodPrice)) {
        cout << "Error parsing the food price. Please contact admin." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        cin.get();
        return;
    }

    // Ask the user for the quantity of the item
    int quantity;
    cout << "Enter the quantity: ";
    cin >> quantity;

    // Check if the quantity is valid
    if (quantity <= 0) {
        cout << "Invalid quantity. Please try again." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        cin.get();
        return;
    }

    // Calculate the total cost of the food items
    double totalCost = foodPrice * quantity;

    // Update the food bill for the guest
    ofstream fout("foodBill.csv", ios::app);
    if (!fout.is_open()) {
        cout << "ERROR!!!" << "\t" << "Couldn't open Food Bill file, please contact admin." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        cin.get();
        return;
    }

    fout << roomN << "," << totalCost << endl; // Use the stored roomNumber

    fout.close();

    head();
    cout << centerText("Order Successful!") << endl;
    cout << "You have ordered " << quantity << " " << foodItem << "(s) for a total cost of $" << totalCost << "." << endl;
    cout << "Thank you for ordering!" << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    cin.get();
}

void user::viewBill() {
    head();
    cout << centerText("View Bill") << endl << endl;

    // Read the guest list to find the check-in date
    ifstream fin("guestList.csv");
    if (!fin.is_open()) {
        cout << "ERROR!!!" << "\t" << "Couldn't open Guest-List, please contact admin." << endl;
        cin.get();
        cin.get();
        return;
    }

    bool found = false;
    string line;
    while (getline(fin, line)) {
        istringstream iss(line);
        string element;
        getline(iss, element, ',');
        int currentRoomNo = stoi(element);
        if (currentRoomNo == roomN) {
            getline(iss, roomType, ','); // Skip room type
            getline(iss, inDate, ',');   // Read check-in date
            found = true;
            break;
        }
    }
    fin.close();

    if (!found) {
        cout << "Guest with room number " << roomN << " not found." << endl;
        cin.get();
        cin.get();
        return;
    }

    // Get the current date
    time_t currentTime = time(nullptr);
    tm* timeInfo = localtime(&currentTime);
    ostringstream oss;
    oss << put_time(timeInfo, "%D-%m-%y"); // Format: DD-MM-YYY
    string currentDate = oss.str();

    // Calculate the difference between check-in and current date
    istringstream issInDate(inDate);
    istringstream issCurrentDate(currentDate);
    tm tmInDate = {}, tmCurrentDate = {};
    issInDate >> get_time(&tmInDate, "%d-%m-%y");
    issCurrentDate >> get_time(&tmCurrentDate, "%d-%m-%y");
    time_t timeInDate = mktime(&tmInDate);
    time_t timeCurrentDate = mktime(&tmCurrentDate);
    double daysStayed = difftime(timeCurrentDate, timeInDate) / (60 * 60 * 24);

    // Calculate the total bill based on rent_per_day and food bill
    double rent_per_day = 1000.0; // You can set this to the appropriate value
    double foodBill = 0.0;
    ifstream finFoodBill("foodBill.csv");
    if (finFoodBill.is_open()) {
        string foodBillLine;
        while (getline(finFoodBill, foodBillLine)) {
            istringstream issBill(foodBillLine);
            string roomNoStr;
            double foodCost;
            getline(issBill, roomNoStr, ',');
            issBill >> foodCost;
            int roomNo = stoi(roomNoStr);
            if (roomNo == roomN) {
                foodBill += foodCost;
            }
        }
        finFoodBill.close();
    }

    double totalBill = daysStayed * rent_per_day + foodBill;

    // Display the bill to the user
    head();
    cout << centerText("Your Bill") << endl << endl << endl;
    cout << left << setw(30) << " " << setw(15) << "Room No.: " << roomN << endl;
    cout << left << setw(30) << " " << setw(15) << "Room Type: " << roomType << endl;
    cout << left << setw(30) << " " << setw(15) << "Check-In Date: " << inDate << endl;
    cout << left << setw(30) << " " << setw(15) << "Days Stayed: " << fixed << setprecision(2) << daysStayed << endl;
    cout << left << setw(30) << " " << setw(15) << "Room Rent: $" << fixed << setprecision(2) << daysStayed * rent_per_day << endl;
    cout << left << setw(30) << " " << setw(15) << "Food Bill: $" << fixed << setprecision(2) << foodBill << endl;
    cout << left << setw(30) << " " << setw(15) << "Total Bill: $" << fixed << setprecision(2) << totalBill << endl;

    cin.get();
    cin.get();
}

void user :: faq(){

}