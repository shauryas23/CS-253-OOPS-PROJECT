#include <bits/stdc++.h>
#include <chrono>
using namespace std;

vector<vector<string>> datatable;
vector<string> oneline;

void readfile(const string& fname) {
    // Clearing global variable
    datatable.clear();

    ifstream file(fname);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream str(line);
            string word;
            vector<string> row;
            while (getline(str, word, ',')) {
                row.push_back(word);
            }
            datatable.push_back(row);
        }
        file.close(); // Close the file after reading
    } else {
        cerr << "Could not open the file: " << fname << endl; // Use cerr for error messages
    }
}
void writefile(const vector<vector<string>>& par, const string& fname) {
    ofstream fout(fname);
    if (fout.is_open()) {
        for (size_t i = 0; i < par.size(); ++i) {
            for (size_t j = 0; j < par[i].size(); ++j) {
                fout << par[i][j];
                if (j != par[i].size() - 1) {
                    fout << ",";
                }
            }
            fout << "\n";
        }
        fout.close(); // Close the file after writing
    } else {
        cerr << "Could not open the file: " << fname << endl; // Use cerr for error messages
    }
}
void writefileappend(const vector<string>& par, const string& fname) {
    ofstream fout(fname, ios::app); // Open the file in append mode
    if (fout.is_open()) {
        for (size_t i = 0; i < par.size(); ++i) {
            fout << par[i];
            if (i != par.size() - 1) {
                fout << ",";
            }
        }
        fout << "\n";
        fout.close(); // Close the file after writing
    } else {
        cerr << "Could not open the file: " << fname << endl; // Use cerr for error messages
    }
}
void printdata(const vector<vector<string>>& par) {
    for (size_t i = 0; i < par.size(); ++i) {
        cout << i + 1 << ". ";
        for (size_t j = 0; j < par[i].size(); ++j) {
            cout << par[i][j];
            if (j != par[i].size() - 1) {
                cout << " | ";
            }
        }
        cout << "\n";
    }
}
void printdata_(const vector<vector<string>>& par) {
    int c = 1;
    for (const auto& x : par) {
        cout << c << ". ";
        cout << x[0] << " | " << x[1] << " | " << x[3] << " | " << x[4] << '\n';
        c++;
    }
}

class User{
    public:
        void main_menu();
        void login();
        void see_all_Cars(string id);
        void rented_Carss(string id);
        void logout();
        virtual void rent_Car(string id, string Carname){}
        void return_Car(string id,string car_numbercode,string type_user);
        void check_available(string id, string Carname);
        virtual int calc_credit_score(string id){}
        void calc_fine(string id);
};

class Customer : public User{
    public:
        void display_Customer_menu(string id);
        void rent_Car(string id, string Carname) override
        {
            datatable.clear();
            int credit_score = 0;
            readfile("peopledata.csv");
            for(int i=0;i<datatable.size();i++)
            {
                if(datatable[i][1]==id)
                {
                    credit_score = stoi(datatable[i][4]);
                }
            }
            int fl = 0;
            int count = 0;
            datatable.clear();
            readfile("rentedcardata.csv");
            for(int i=0;i<datatable.size();i++)
            {
                if(datatable[i][0]==id)
                {
                    count += stoi(datatable[i][4]);
                }
            }
            datatable.clear();
            readfile("cardata.csv");
            int currentprice = 0;
            int check = 0;
            for(int i=0;i<datatable.size();i++)
            {
                if(datatable[i][0]==Carname && datatable[i][4]=="0")
                {
                    count += stoi(datatable[i][2]);
                    currentprice = stoi(datatable[1][2]);
                    check = 1;
                }
            }
            if(check == 0)
            {
                cout<<"Car not available\n";
                return;
            }
            if(count>credit_score)
            {
                cout<<"You cant issue more cars based on your credit score.\n\n";
            }
            else
            {
                int a;
                cout << "The car costs : " << currentprice << "\n";
                cout << "press 1 if you are willing to buy, press 2 if not : ";
                cin >> a;
                cout << "\n";
                if(a == 2)
                {
                    fl = 2;
                }
                else
                {    datatable.clear();
                    readfile("cardata.csv");
                    for(int i=0;i<datatable.size();i++){
                        if(datatable[i][0]==Carname && datatable[i][4]=="0"){
                            fl=1;
                            cout<<"Car is available!\n";
                            datatable[i][4]="1";
                            oneline.clear();
                            oneline.push_back(id);
                            oneline.push_back(Carname);
                            oneline.push_back(datatable[i][3]);
                            oneline.push_back(to_string(time(0)));
                            oneline.push_back(datatable[i][2]);
                            writefileappend(oneline,"rentedcardata.csv");
                            cout<<"Car succesfully rented\n";
                            break;
                        }
                    }
                }
                writefile(datatable,"cardata.csv");
                datatable.clear();
            }
        }
        int calc_credit_score(string id) override
        {
            int fine=0;
            int credit = 0;
                datatable.clear();
                readfile("peopledata.csv");
                for(int i=0;i<datatable.size();i++)
                {
                    if(datatable[i][1]==id)
                    {
                        credit = stoi(datatable[i][4]);
                    }
                }

            datatable.clear();
            readfile("rentedcardata.csv");
            for(int i=0;i<datatable.size();i++){
                if(datatable[i][0]==id){
                    int currenttime = time(0);
                    int oldtime = stoi(datatable[i][3]);
                    if((currenttime-oldtime)/86400>1) fine+=stoi(datatable[i][4])*((currenttime-oldtime)/86400 - 1);
                }
            }
            cout<<"Your credit score is : "<<credit-fine<<"\n";
            datatable.clear(); 
            return fine;  
        }
};

class Employee : public User{
    public:
    
        void display_employee_menu(string id);
        void rent_Car(string id, string Carname) override
        {
            datatable.clear();
            int credit_score = 0;
            readfile("peopledata.csv");
            for(int i=0;i<datatable.size();i++)
            {
                if(datatable[i][1]==id)
                {
                    credit_score = stoi(datatable[i][4]);
                }
            }
            int fl = 0;
            int count = 0;
            int curr = 0;
            datatable.clear();
            readfile("rentedcardata.csv");
            for(int i=0;i<datatable.size();i++)
            {
                if(datatable[i][0]==id)
                {
                    count += stoi(datatable[i][4]);
                }
            }
            datatable.clear();
            readfile("cardata.csv");
            int check = 0;
            for(int i=0;i<datatable.size();i++)
            {
                if(datatable[i][0]==Carname && datatable[i][4]=="0")
                {
                    check = 1;
                    count += stoi(datatable[i][2]);
                    curr = stoi(datatable[i][2]);
                }
            }
            if(check == 0)
            {
                cout<<"Car not available\n";
                return;
            }

            count /= 100;
            count *= 85;
            if(count>credit_score)
            {
                cout<<"You cant issue more cars based on your credit score.\n\n";
            }
            else
            {
                int a;
                curr /= 100;
                curr *= 85;
                cout << "The car costs : " << curr << " with a 15 percent discount\n";
                cout << "press 1 if you are willing to buy, press 2 if not : ";
                cin >> a;
                cout << "\n";
                if(a == 2)
                {
                    fl = 2;
                }
                else
                {
                    readfile("cardata.csv");
                    for(int i=0;i<datatable.size();i++){
                        if(datatable[i][0]==Carname && datatable[i][4]=="0"){
                            fl=1;
                            datatable[i][4]="1";
                            oneline.clear();
                            oneline.push_back(id);
                            oneline.push_back(Carname);
                            oneline.push_back(datatable[i][3]);
                            oneline.push_back(to_string(time(0)));
                            oneline.push_back(datatable[i][2]);
                            writefileappend(oneline,"rentedcardata.csv");
                            cout<<"Car succesfully issued\n";
                            break;
                        }
                    }
                }
                writefile(datatable,"cardata.csv");
                datatable.clear();
            }
        }
        int calc_credit_score(string id) override
        {
            int fine=0;
            int credit = 0;
                datatable.clear();
                readfile("peopledata.csv");
                for(int i=0;i<datatable.size();i++)
                {
                    if(datatable[i][1]==id)
                    {
                        credit = stoi(datatable[i][4]);
                    }
                }

                datatable.clear();
                readfile("rentedcardata.csv");
                for(int i=0;i<datatable.size();i++){
                    if(datatable[i][0]==id){
                        int currenttime = time(0);
                        int oldtime = stoi(datatable[i][3]);
                        if((currenttime-oldtime)/86400>2) fine+=stoi(datatable[i][4])*((currenttime-oldtime)/86400 - 2);
                    }
                }
                cout<<"Your credit score is : "<<credit-fine<<"\n";
                datatable.clear();
                return fine; 
        }
};

class Manager : public User{
    public:
        void display_manager_menu(string id);
        void see_all_users(string id);
        void see_all_Cars(string id);
        void add_user(string id);
        void update_user(string id);
        void delete_user(string id);
        void add_Car(string id);
        void update_Car(string id);
        void delete_Car(string id);
        void rented_to_user(string id,string uid);
        void rented_Cars(string id,string car_number);
        void Show_duedate(string car_number_no);
};

void Customer :: display_Customer_menu(string id){
    cout<<"---------------------------------------------------------------------\n";
    cout<<"---------------------------------------------------------------------\n";
    cout<<"\nYou have been logged in as Customer\n";
    cout<<"Press 1 to see all the Cars\n";
    cout<<"Press 2 to view Cars rented by you\n";
    cout<<"Press 3 to check if a Car is available for rent or not\n";
    cout<<"Press 4 to view your credit score\n";
    cout<<"Press 5 to view your fines\n";
    cout<<"Press 6 to rent a Car\n";
    cout<<"Press 7 to return a Car\n";
    cout<<"Press l to logout\n";
    cout<<"Press e to exit\n";
    cout<<"---------------------------------------------------------------------\n";
    cout<<"---------------------------------------------------------------------\n";
    char c;
    std::cin>>c;
    string Car_name,car_numbercode;
    Customer s;
    switch(c){
        case '1':
            s.see_all_Cars(id);
            s.display_Customer_menu(id);
            break;
        case '2':
            s.rented_Carss(id);
            s.display_Customer_menu(id);
            break;
        case '3':
            cout<<"Enter the name of the Car you want to check : ";
            std::cin.ignore();
            getline(std::cin,Car_name);
            s.check_available(id,Car_name);
            s.display_Customer_menu(id);
            break;
        case '4':
            s.calc_credit_score(id);
            s.display_Customer_menu(id);
            break;
        case '6':
            cout<<"Enter the name of the Car you want to issue : ";
            std::cin.ignore();
            getline(std::cin,Car_name);
            s.rent_Car(id,Car_name);
            s.display_Customer_menu(id);            
            break;
        case '7':
            cout<<"Enter the number the Car you want to return : ";
            std::cin>>car_numbercode;
            s.return_Car(id,car_numbercode, "1");
            s.display_Customer_menu(id);
            break;          
        case 'l':
            logout();
            break;
        case 'e':
            cout << "Exiting the system...";
            exit(1);
            break;
        case '5':
            s.calc_fine(id);
            s.display_Customer_menu(id);
            break;
    }
}

void Employee :: display_employee_menu(string id){
    cout<<"---------------------------------------------------------------------\n";
    cout<<"---------------------------------------------------------------------\n";
    cout<<"\nYou have been logged in as Customer\n";
    cout<<"Press 1 to see all the Cars\n";
    cout<<"Press 2 to view Cars rented by you\n";
    cout<<"Press 3 to check if a Car is available for rent or not\n";
    cout<<"Press 4 to view your credit score\n";
    cout<<"Press 5 to view your fines\n";
    cout<<"Press 6 to rent a Car\n";
    cout<<"Press 7 to return a Car\n";
    cout<<"Press l to logout\n";
    cout<<"Press e to exit\n";
    cout<<"---------------------------------------------------------------------\n";
    cout<<"---------------------------------------------------------------------\n";
    char c;
    std::cin>>c;
    string Car_name,car_numbercode;
    Employee s;
    switch(c){
        case '1':
            s.see_all_Cars(id);
            s.display_employee_menu(id);
            break;
        case '2':
            s.rented_Carss(id);
            s.display_employee_menu(id);
            break;
        case '3':
            cout<<"Enter the name of the Car you want to check : ";
            std::cin>>Car_name;
            s.check_available(id,Car_name);
            s.display_employee_menu(id);
            break;
        case '4':
            s.calc_credit_score(id);
            s.display_employee_menu(id);
            break;
        case '6':
            cout<<"Enter the name of the Car you want to issue : ";
            std::cin>>Car_name;
            s.rent_Car(id,Car_name);
            s.display_employee_menu(id);            
            break;
        case '7':
            cout<<"Enter the number of the Car you want to return : ";
            std::cin>>car_numbercode;
            s.return_Car(id,car_numbercode,"2");
            s.display_employee_menu(id);
            break;
        case 'l':
            logout();
            break;
        case 'e':
            cout << "Exiting the system...";
            exit(1);
            break;
        case '5':
            s.calc_fine(id);
            s.display_employee_menu(id);
            break;
    }
}

void User :: main_menu(){
    char c;
    cout<<"---------------------------------------------------------------------\n";
    cout<<"---------------------------------------------------------------------\n";
    cout<<"1. Press 1 to log in : \n";
    cout<<"2. Press any other key to exit\n";
    cout<<"---------------------------------------------------------------------\n";
    cout<<"---------------------------------------------------------------------\n";
    std::cin >> c;
    if(c=='1')
    { //logs in a user 
        User u;
        u.login();
    }
    else
    {
        cout<<"Exiting the system...";
        exit(1);
    }
}
void User :: login(){

    string id,password;
    cout<<"Enter your id : ";
    std::cin>>id;
    cout<<"Enter the password : ";
    std::cin>>password;
    vector<string> words_in_a_row;
    string line_in_csv,word;
    fstream file("peopledata.csv",ios::in);
    int count=0;
    if(file.is_open()){
        while(getline(file,line_in_csv)){
            words_in_a_row.clear();
            stringstream str(line_in_csv);
            while(getline(str,word,',')) words_in_a_row.push_back(word);
            if(words_in_a_row[1]==id){
                count=1;
                if(words_in_a_row[2]==password){
                    count++;
                    break;
                }
                else{
                    while(password!=words_in_a_row[2]){
                        cout<<"You entered the wrong password. Press 1 to reenter the password and 2 to exit\n";
                        char c;
                        std::cin>>c;
                        if(c=='1'){
                            cout<<"Enter the password : ";
                            std::cin>>password;
                            if(password==words_in_a_row[2]) count++;
                        }
                        else if(c=='2'){
                            cout<<"Exiting...";
                            return;
                        }
                        else{
                            cout<<"Please enter a valid input.\n";
                        }
                    }
                    if(count==2) break;
                }
            }
            if(count==2) break;            
        }
        if(count==0){
            cout<<"User not found\n";
            User u;
            u.main_menu();
        }
        if(count==2){

            Customer s;
            Employee p;
            Manager l;

            if(words_in_a_row[3]=="1"){
                s.display_Customer_menu(words_in_a_row[1]);
            }
            else if(words_in_a_row[3]=="2"){
                p.display_employee_menu(words_in_a_row[1]);
            }
            else{
                l.display_manager_menu(words_in_a_row[1]);
            }
        }
    }
}
void User :: see_all_Cars(string id){
    datatable.clear();
    cout<<"In the data below, 0 means that the Car is not rented and 1 means that the Car is already rented.\n";
    readfile("cardata.csv");
    printdata(datatable);
    datatable.clear();
}
void User :: return_Car(string id,string car_numbercode,string type_user){
    cout << "enter percentage damage to the car : ";
    int damage = 0;
    cin >> damage;
    while(damage < 0 || damage > 100)
    {
        cout << "percentage can only be between 0 and 100, enter again : ";
        cin >> damage;
    }
    int fine = 0;
    int car_value = 0;
    datatable.clear();
    readfile("cardata.csv");
    for(int i = 0; i < datatable.size(); i++)
    {
        if(datatable[i][3] == car_numbercode)
            car_value = stoi(datatable[i][2]);
    }
    datatable.clear();
    int fl=0;
    readfile("rentedcardata.csv");
    for(int i=0;i<datatable.size();i++)
    {
        if(datatable[i][2]==car_numbercode && datatable[i][0]==id)
        {
            fl=1;

            for(int i=0;i<datatable.size();i++)
            {
                if(datatable[i][0]==id)
                {
                    int currenttime = time(0);
                    int oldtime = stoi(datatable[i][3]);
                    if((currenttime-oldtime)/86400>1) fine += ((car_value*((currenttime-oldtime)/86400 - 1))/stoi(type_user));
                }
            }

            datatable.erase(datatable.begin()+i,datatable.begin()+i+1);
            cout<<"Car was issued by you and is now being returned\n";
            writefile(datatable,"rentedcardata.csv");
            datatable.clear();
            readfile("cardata.csv");
            for(int i=0;i<datatable.size();i++)
            {
                if(datatable[i][3]==car_numbercode) datatable[i][4]="0";
            }
            writefile(datatable,"cardata.csv");

            datatable.clear();
            readfile("peopledata.csv");
            for(int i=0;i<datatable.size();i++)
            {
                if(datatable[i][1]==id)
                {
                    int cred = stoi(datatable[1][4]);
                    cred -= fine;
                    int64_t temporary = damage*car_value;
                    temporary /= 100;
                    if(damage == 0)
                    {
                        temporary = (0 - (car_value/2));
                    }
                    cred -= temporary;
                    string str = to_string(cred);
                    datatable[i][4]=str;
                } 
            }
            writefile(datatable,"peopledata.csv");
            break;
        }
    }
    if(fl==0) cout<<"Invalid details!\n";

    datatable.clear();
}
void User :: rented_Carss(string id){
    int count=1;
    datatable.clear();
    readfile("rentedcardata.csv");
    for(int i=0;i<datatable.size();i++)
    {
        if(datatable[i][0]==id){
            cout<<count<<". ";
            count++;
            for(int k=0;k<datatable[i].size()-1;k++)
                cout<<datatable[i][k]<<" | ";
            time_t stamp = stoi(datatable[i][3]);
            tm *dateformat = localtime(&stamp);  
            cout<< dateformat->tm_mday<<"/"<<1 + dateformat->tm_mon<<"/"<<1900 + dateformat->tm_year<<"\n";
        }
    }
    if(count==0) 
        cout<<"You haven't rented any Cars.\n";
    datatable.clear();
}
void User :: check_available(string id,string Carname){
    datatable.clear();
    int checker=0;
    readfile("cardata.csv");
    for(int i=0;i<datatable.size();i++){
        if(datatable[i][0]==Carname && datatable[i][4]=="0")
        {
            checker=1;
            cout<<"Car is available!\n";
            for(auto j:datatable[i])
                cout<<j<<" | ";
            cout<<"\n";
            break;
        }
    }
    if(checker==0) cout<<"Car not available\n";
    datatable.clear();
}
void User :: logout()
{
    cout<<"logging out...\n";
    User u;
    u.main_menu();
}
void User :: calc_fine(string id)
{
    datatable.clear();
    readfile("peopledata.csv");
    int fine = 0;
    for(int i = 0; i < datatable.size(); i++)
    {
        if(datatable[i][1] == id)
            fine = 5000 - stoi(datatable[i][4]);
    }

    if(fine > 0)
        cout << "your fine is : " << fine << "\n";
    else
        cout << "your fine is : 0\n";
}

void Manager :: display_manager_menu(string id){
    cout<<"---------------------------------------------------------------------\n";
    cout<<"---------------------------------------------------------------------\n";
    cout<<"\nWelcome "<<id<<"! You are logged in as Manager.\n\n";
    cout<<"Press 1 to add a user\n";
    cout<<"Press 2 to update a user\n";
    cout<<"Press 3 to delete a user\n";
    cout<<"Press 4 to add a Car\n";
    cout<<"Press 5 to update a Car\n";
    cout<<"Press 6 to delete a Car\n";
    cout<<"Press 7 to see all Cars rented to a particular user\n";
    cout<<"Press 8 to see which Car is rented to which user\n";
    cout<<"Press 9 to view all users\n";
    cout<<"Press 0 to view all Cars\n";
    cout<<"Press d to show due date of a Car\n";
    cout<<"Press l to logout\n";
    cout<<"Press e to exit\n";
    cout<<"---------------------------------------------------------------------\n";
    cout<<"---------------------------------------------------------------------\n";
    char c;
    std::cin>>c;
    Manager l;
    User u;
    string car_number,uid;
    switch(c){
        case '1':
            l.add_user(id);
            l.display_manager_menu(id);
            break;
        case '2':
            l.update_user(id);
            l.display_manager_menu(id);
            break;
        case '3':
            l.delete_user(id);
            l.display_manager_menu(id);
            break;
        case '4':
            l.add_Car(id);
            l.display_manager_menu(id);
            break;
        case '5':
            l.update_Car(id);
            l.display_manager_menu(id);
            break;
        case '6':
            l.delete_Car(id);
            l.display_manager_menu(id);
            break;
        case '7':
            cout<<"Enter the id of the user : ";
            std::cin>>uid;
            l.rented_to_user(id,uid);
            l.display_manager_menu(id);
            break;
        case '8':
            cout<<"Enter the car number : ";
            std::cin>>car_number;
            l.rented_Cars(id,car_number);
            l.display_manager_menu(id);
            break;
        case '9':
            l.see_all_users(id);
            l.display_manager_menu(id);
            break;
        case '0':
            l.see_all_Cars(id);
            l.display_manager_menu(id);
            break;
        case 'd':
            cout<<"Enter the car number : ";
            std::cin>>car_number;
            l.Show_duedate(car_number);
            l.display_manager_menu(id);
            break;
        case 'l':
            logout();
            l.display_manager_menu(id);
            break;
        case 'e':
            exit(1);
    }
}
void Manager :: Show_duedate(string car_number){
    datatable.clear();
    string uid;
    time_t stamp;

    // Read rented cars data
    readfile("rentedcardata.csv");

    // Search for the car number in the rented cars data
    bool foundCar = false;
    for (int i = 0; i < datatable.size(); i++) {
        if (datatable[i][2] == car_number) {
            foundCar = true;
            uid = datatable[i][0];
            stamp = stoi(datatable[i][3]);
            break;
        }
    }
    datatable.clear();

    int days = 0;

    // Read all people data
    readfile("peopledata.csv");

    // Find the rental days for the user
    for (int i = 0; i < datatable.size(); i++) {
        if (datatable[i][1] == uid) {
            days = (datatable[i][3] == "1") ? 1 : 2;
            break;
        }
    }

    // Calculate due date
    stamp += days * 86400;
    tm *due_time = localtime(&stamp);

    // Output result
    if (!foundCar)
        cout << "Car was not rented!\n";
    else {
        cout << "Due date of the car is: ";
        cout << due_time->tm_mday << "/" << 1 + due_time->tm_mon << "/" << 1900 + due_time->tm_year << "\n";
    }
}
void Manager :: see_all_users(string id){
    datatable.clear();
    readfile("peopledata.csv");
    cout<<"Below are all the users. 1 at the end means a Customer, 2 means a Employee and 3 means a Manager \n\n";
    printdata_(datatable);
    datatable.clear();
}
void Manager :: see_all_Cars(string id){
    datatable.clear();
    readfile("cardata.csv");
    cout<<"The data is given in the form of Car name,author,pubisher,car_number number,and is_issued(1 if Car is issued).\n\n";
    printdata(datatable);
    datatable.clear();
}
void Manager :: add_user(string id){
    cout << "Please enter the details of the new user:\n";
    string _name, _id, _password, _type;
    cout << "Enter name: ";
    cin >> _name;
    cout << "Enter id: ";
    cin >> _id;
    cout << "Enter password: ";
    cin >> _password;
    cout << "Enter type of the user (1 for Customer, 2 for Employee, 3 for Manager): ";
    cin >> _type;

    fstream fout("peopledata.csv", ios::out | ios::app);
    fout << _name << "," << _id << "," << _password << "," << _type << "," << "5000" << '\n';
    cout << "New user has been added.\n";
}
void Manager :: add_Car(string id){
    cout<<"Please enter the details of the new Car : \n";
    string title,company,price,numb;
    cout<<"Enter car name: ";
    std::cin.ignore();
    getline(std::cin,title);
    cout<<"Enter manufacturing company : ";
    std::cin>>company;
    cout<<"Enter price : ";
    std::cin>>price;
    cout<<"Enter car number : ";
    std::cin>>numb;
    fstream fout("cardata.csv",ios::out | ios::app);
    fout<<title<<","<<company<<","<<price<<","<<numb<<",0"<<'\n';
    cout<<"New Car has been added.\n";
}
void Manager :: delete_Car(string id){
    string car_numberno;
    cout<<"Enter the car_number number of the Car : ";
    std::cin>>car_numberno;
    datatable.clear();
    int found=0;
    readfile("cardata.csv");
    for(int i=0;i<datatable.size();i++){
        if(datatable[i][3]==car_numberno){
            found=1;
            datatable.erase(datatable.begin()+i,datatable.begin()+i+1);
            break;
        }
    }
    writefile(datatable,"cardata.csv");

    datatable.clear();
    readfile("rentedcardata.csv");
    for(int i=0;i<datatable.size();i++)
    {
        if(datatable[i][2]==car_numberno)
        {
            datatable.erase(datatable.begin()+i,datatable.begin()+i+1);
            break;
        }
    }
    writefile(datatable,"rentedcardata.csv");

    datatable.clear();

    if(found==0) cout<<"Car not found.\n";
}
void Manager :: delete_user(string id){
    string uid;
    cout<<"Enter the user id of the user : ";
    std::cin>>uid;
    datatable.clear();
    int found=0;
    readfile("peopledata.csv");
    for(int i=0;i<datatable.size();i++){
        if(datatable[i][1]==uid){
            found=1;
            datatable.erase(datatable.begin()+i,datatable.begin()+i+1);
            break;
        }
    }
    writefile(datatable,"peopledata.csv");
    datatable.clear();
    vector<string> car_numbers;
    readfile("rentedcardata.csv");
    for(int i=0;i<datatable.size();i++){
        if(datatable[i][0]==uid){
            car_numbers.push_back(datatable[i][2]);
            datatable.erase(datatable.begin()+i,datatable.begin()+i+1);
            break;
        }
    }
    writefile(datatable,"rentedcardata.csv");
    datatable.clear();

    readfile("cardata.csv");
    for(int i=0;i<datatable.size();i++){
        for(int j=0;j<car_numbers.size();j++){
            if(car_numbers[j]==datatable[i][3]){
                datatable[i][4]="0";
            }
        }
    }
    writefile(datatable,"cardata.csv");
    if(found==0) cout<<"User not found.\n";
}
void Manager :: update_user(string id){
    string upid;
    cout<<"Enter the id of the user you want to update : ";
    std::cin>>upid;
    cout<<"Enter the serial number of the field you want to update : \n";
    cout<<"1. Password\n";
    cout<<"2. Name of the User\n";
    char c;
    std::cin>>c;
    datatable.clear();
    int fl=0;
    readfile("peopledata.csv");
    for(int i=0;i<datatable.size();i++){
        if(datatable[i][1]==upid){
            fl=1;
            string new_field;
            cout<<"Enter the new value of the field : ";
            std::cin.ignore();
            getline(std::cin,new_field);
            if(c=='1'){
                datatable[i][2]=new_field;
            }
            else if(c=='2'){
                datatable[i][0]=new_field;
            }
            else{
                cout<<"Invalid input!\n\n";
            }
            break;
        }
    }
    cout<<"User updated\n";
    writefile(datatable,"peopledata.csv");
    datatable.clear();
    if(fl==0) cout<<"User was not found.\n\n";
}
void Manager :: update_Car(string id){
    string car_number_no;
    cout<<"Enter the car_number number of the Car you want to update : ";
    std::cin>>car_number_no;
    cout<<"Enter the serial number of the field you want to update : \n";
    cout<<"1. Name of the Car\n";
    cout<<"2. Name of the Author\n";
    cout<<"3. Name of the Publisher\n";
    char c;
    std::cin>>c;
    datatable.clear();
    int fl=0;
    string new_field;
    readfile("cardata.csv");
    for(int i=0;i<datatable.size();i++){
        if(datatable[i][3]==car_number_no){
            fl=1;
            cout<<"Enter the new value of the field : ";
            std::cin.ignore();
            getline(std::cin,new_field);
            if(c=='1'){
                datatable[i][0]=new_field;
            }
            else if(c=='2'){
                datatable[i][1]=new_field;
            }
            else if(c=='3'){
                datatable[i][2]=new_field;
            }
            else{
                cout<<"Invalid input!\n\n";
            }
            break;
        }
    }
    writefile(datatable,"cardata.csv");
    datatable.clear();
    
    readfile("rentedcardata.csv");
    for(int i=0;i<datatable.size();i++){
        if(datatable[i][2]==car_number_no){
            fl=1;
            if(c=='1'){
                datatable[i][1]=new_field;
            }
            break;
        }
    }
    cout<<"Car updated\n";
    writefile(datatable,"rentedcardata.csv");

    if(fl==0) cout<<"Car was not found.\n\n";
}
void Manager :: rented_to_user(string id,string uid){
    vector <string> car_numbers;
    datatable.clear();
    int count=1;
    readfile("rentedcardata.csv");
    for(int i=0;i<datatable.size();i++){
        if(datatable[i][0]==uid){
            car_numbers.push_back(datatable[i][2]);
        }
    }
    datatable.clear();
    if(car_numbers.size()==0) cout<<"No Car is issued to this user.\n\n";
    else{
        readfile("cardata.csv");
        for(int d=0;d<car_numbers.size();d++){
            for(int i=0;i<datatable.size();i++){
                if(datatable[i][3]==car_numbers[d]){
                    cout<<count<<". ";
                    count++;
                    for(auto y:datatable[i]){
                        if(y!=datatable[i].back())
                            cout<<y<<" | ";
                        else
                            cout<<y<<"\n";
                    }
                }
            }
        }
        datatable.clear();
    }
}
void Manager :: rented_Cars(string id,string car_number){
    datatable.clear();
    int coun=0;
    readfile("rentedcardata.csv");
    for(int i=0;i<datatable.size();i++){
        coun=1;
        if(datatable[i][2]==car_number){
            cout<<"Car "<<car_number<<": "<<datatable[i][1]<<" is rented to: "<<datatable[i][0]<<"\n";
        }
    }
    if(coun==0) cout<<"Car has not been issued to anyone.\n\n";
}

int main(){
    User tempo;
    tempo.main_menu();
    return 0;
}