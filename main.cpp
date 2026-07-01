#include <iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;

class User{
    public:
        string password;
        string name;
        
        bool passwordcheck(string password){
           int uppercase=0;
           int lowercase=0;
           int digit=0;
           int specialcharacter=0;
           int len=password.length();
           for(int i=0;i<len;i++){
            if(password[i]>='A'&& password[i]<='Z'){
                      uppercase=1; }
            else if(password[i]>='a'&& password[i]<='z'){
                      lowercase=1; }
            else if(password[i]>='0'&& password[i]<='9'){
                      digit=1; }
            else{
              specialcharacter=1; }
            }
        if(uppercase==1 && lowercase==1 && digit==1 && len>=8 && specialcharacter==1)
              return true;
        else
              return false;
        }
    };
class Student:public User{
    public:
        int regno;
        string course;
        int roomno;
    
    bool studentregistration(){
        cout<<"Enter User ID(4 Digit Reg No):";
        cin>>regno;
        cout<<"Enter Password (*Must Satisfy The following Conditions:\nAtleast one upper case letter.\nAtleast one lower case letter.\nAtleast one Digit.\nAtleast one special character.\nminimum length of 8 characters.*):";
        cin>>password;
        if(regno<1000||regno>9999|| !passwordcheck(password)){
            cout<<"Invalid Password/Reg No";
            return false;
        }
        else
           return true;
    }
    
    void allocateroom(){
        cout<<"Enter Name(use '_' if name contains space):";
        cin>>name;
        cout<<"Enter 4-Digit Reg No:";
        cin>>regno;
        cout<<"Enter Course(without space):";
        cin>>course;
    }
};

class Admin:public User{
    public:
       int empid;
    
      bool adminregistration(){
        cout<<"Enter ID(4 Digit Employee ID):";
        cin>>empid;
        cout<<"Enter Password (*Must Satisfy The following Conditions:\nAtleast one upper case letter.\nAtleast one lower case letter.\nAtleast one Digit.\nAtleast one special character.\nminimum length of 8 characters.*):";
        cin>>password;
        if(empid<1000||empid>9999||! passwordcheck(password)){
            cout<<"Invalid Password/Emp ID";
            return false;
        }
        else
           return true;
    }
};

int CountUsers(Student users[], int maxUsers) {
    ifstream fin("data/user.txt");
    int count = 0;
    while (count < maxUsers && fin >> users[count].regno >> users[count].password) {
        count++;
    }
    fin.close();
    return count;
}

void saveUsers(Student users[], int count) {
    ofstream fout("data/user.txt");
    for (int i = 0; i < count; i++) {
        fout << left << setw(20) << users[i].regno << setw(20) << users[i].password << '\n';
    }
    fout.close();
}

int CountAdmins(Admin A[], int maxUsers) {
    ifstream fin("data/Admin.txt");
    int count = 0;
    while (count < maxUsers && fin >> A[count].empid >> A[count].password) {
        count++;
    }
    fin.close();
    return count;
}

void saveAdmins(Admin A[], int count) {
    ofstream fout("data/Admin.txt");
    for (int i = 0; i < count; i++) {
        fout << left << setw(20) << A[i].empid << setw(20) << A[i].password << '\n';
    }
    fout.close();
}

int CountStudents(Student S[], int maxStudents) {
    ifstream fin("data/students.txt");
    int count = 0;
    while (count < maxStudents && fin >> S[count].name >> S[count].regno >> S[count].course >> S[count].roomno) {
        count++;
    }
    fin.close();
    return count;
}

void saveStudents(Student S[], int count) {
    ofstream fout("data/students.txt");
    for (int i = 0; i < count; i++) {
        fout << left << setw(20) << S[i].name
             << setw(20) << S[i].regno
             << setw(20) << S[i].course
             << setw(20) << S[i].roomno << '\n';
    }
    fout.close();
}

void display(Student S[], int i){
    cout << left << setw(20) << S[i].name
                     << setw(20) << S[i].regno
                     << setw(20) << S[i].course
                     << setw(20) << S[i].roomno << '\n';
}

int CountVacatedStudents(Student vacate[], int maxStudents){
    ifstream fin("data/Vacatedstudentdetails.txt");
    int count = 0;
    while (count < maxStudents && fin >> vacate[count].name >> vacate[count].regno >> vacate[count].course >> vacate[count].roomno) {
        count++;
    }
    fin.close();
    return count;
}

int main(){
    Student S[200];
    Student users[200];
    Student vacate[200];
    Admin A[200];

    int choice;
    int count, found, roomNo;
    int rollno;                //For Search
    bool userlogin = false;
    bool adminlogin=false;
    int userloggedInId = 0;
    string userloginPassword;
    int adminloggedInId = 0;
    string adminloginPassword;

    do {
        cout << "\n-------------------- MENU --------------------\n";
        cout << "1. New Student Registration\n";
        cout << "2. Student Login\n";
        cout << "3. Admin Registration\n";
        cout << "4. Admin Login\n";
        cout << "5. Room Allocation\n";
        cout << "6. Display All Students\n";
        cout << "7. Search Student\n";
        cout << "8. Vacate Room\n";
        cout << "9. Display Vacated Student Details\n";
        cout <<"10. Student Logout\n";
        cout <<"11. Admin Logout\n";
        cout <<"12. Exit\n";
        cout <<"Enter Your Choice: ";
        cin >> choice;
    
    switch (choice) {
        case 1: {
            found = 0;
            count = CountUsers(users, 200);

            if (count >= 200) {
                cout << "Maximum user limit reached.\n";
                break;
            }

            if (!users[count]. studentregistration()) {
                break;
            }

            for (int i = 0; i < count; i++) {
                if (users[i].regno == users[count].regno) {
                    cout << "User already registered.\n";
                    found = 1;
                    break;
                }
            }

            if (found==0) {
                count++;
                saveUsers(users, count);
                cout << "Registration successful!\n";
            }
            break;
        }
        
        case 2: {
            found = 0;
            count = CountUsers(users, 200);
            userlogin = false;

            cout << "ENTER USERID (4-DIGIT REG NO): ";
            cin >> userloggedInId;
            cout << "ENTER PASSWORD: ";
            cin>>userloginPassword;

            for (int i = 0; i < count; i++) {
                if (users[i].regno == userloggedInId && users[i].password == userloginPassword) {
                    found = 1;
                    userlogin = true;
                    cout << "Login successful!\n";
                    break;
                }
            }

            if (!found) {
                cout << "Login failed.\n";
            }
            break;
        }
        
        case 3: {
            found = 0;
            count = CountAdmins(A, 200);

            if (count >= 200) {
                cout << "Maximum user limit reached.\n";
                break;
            }

            if (!A[count].adminregistration()) {
                break;
            }

            for (int i = 0; i < count; i++) {
                if (A[i].empid == A[count].empid) {
                    cout << "Admin already registered.\n";
                    found = 1;
                    break;
                }
            }

            if (found==0) {
                count++;
                saveAdmins(A, count);
                cout << "Registration successful!\n";
            }
            break;
        }
        
        case 4: {
            found = 0;
            count = CountAdmins(A, 200);
            adminlogin = false;

            cout << "ENTER USERID (4-DIGIT EMPLOYEE ID): ";
            cin >> adminloggedInId;
            cout << "ENTER PASSWORD: ";
            cin>>adminloginPassword;

            for (int i = 0; i < count; i++) {
                if (A[i].empid == adminloggedInId && A[i].password == adminloginPassword) {
                    found = 1;
                    adminlogin = true;
                    cout << "Login successful!\n";
                    break;
                }
            }

            if (found==0) {
                cout << "Login failed.\n";
            }
            break;
        }
        
        case 5: {
             found=0;
             
             if (!userlogin) {
                cout << "Access denied. Login required.\n";
                break;
            }

            count = CountStudents(S, 200);
            if (count >= 200) {
                cout << "No rooms available.\n";
                break;
            }

            Student newStudent;
            newStudent.allocateroom();

            if (newStudent.regno != userloggedInId) {
                cout << "Error: Logged-in user ID and entered regno do not match.\n";
                break;
            }

            for (int i = 0; i < count; i++) {
                if (S[i].regno == newStudent.regno && S[i].roomno != 0) {
                    cout << "Room already allocated for this regno.\n";
                    found = 1;
                    break;
                }
            }
            if (found == 1) {
                found = 0;
                break;
            }

            int availableIndex = -1;
            for (int i = 0; i < count; i++) {
                if (S[i].roomno == 0) {
                    availableIndex = i;
                    break;
                }
            }

            if (availableIndex != -1) {
                S[availableIndex] = newStudent;
                S[availableIndex].roomno = availableIndex + 1;
                cout << "Allocated Room: " << S[availableIndex].roomno << '\n';
            } else {
                S[count] = newStudent;
                S[count].roomno = count + 1;
                cout << "Allocated Room: " << S[count].roomno << '\n';
                count++;
            }

            saveStudents(S, count);
            break;
        }
        
        case 6: {
            if(!adminlogin) {
                cout<<"Access Denied.Admin Login Required."<<"\n";
                break;
            }
            
            count = CountStudents(S, 200);
            cout << left << setw(20) << "Name" << setw(20) << "Regno" << setw(20) << "Course" << setw(20) << "Room No" << '\n';
            for (int i = 0; i < count; i++) {
                display(S,i);
            }
            break;
        }
        
        case 7: {
            if(!adminlogin) {
                cout<<"Access Denied.Admin Login Required."<<"\n";
                break;
            }
            
            found = 0;
            count = CountStudents(S, 200);
            cout << "Enter Regno to search: ";
            cin >> rollno;

            for (int i = 0; i < count; i++) {
                if (S[i].regno == rollno) {
                    cout << "Student Data Found\n";
                    cout << left << setw(20) << "Name" << setw(20) << "Regno" << setw(20) << "Course" << setw(20) << "Room No" << '\n';
                    display(S, i);
                    found = 1;
                    break;
                }
            }

            if (!found) {
                cout << "No records found.\n";
            }
            break;
        }
        
        case 8: {
            if (!userlogin) {
                cout << "Access denied. Login required.\n";
                break;
            }

            found = 0;
            count = CountStudents(S, 200);

            if (count == 0) {
                cout << "No rooms are occupied yet.\n";
                break;
            }

            int regnoInput;
            cout << "Enter regno: ";
            cin >> regnoInput;
            cout << "Enter room no. to vacate: ";
            cin >> roomNo;

            for (int i = 0; i < count; i++) {
                if (regnoInput == userloggedInId && S[i].regno == regnoInput && S[i].roomno == roomNo) {
                    ofstream fout;
                    fout.open("data/Vacatedstudentdetails.txt",ios::app);
                    fout << left << setw(20) << S[i].name
                         << setw(20) << S[i].regno
                         << setw(20) << S[i].course
                         << setw(20) << S[i].roomno << '\n';
                    fout.close();
                    S[i].roomno = 0;
                    found = 1;
                    cout << "Room vacated successfully.\n";
                    break;
                }
            }

            if (found) {
                saveStudents(S, count);
            } else {
                cout << "No room found or regno mismatch.\n";
            }
            break;
        }
        
        case 9: {
            if(!adminlogin) {
                cout<<"Access Denied.Admin Login Required."<<"\n";
                break;
            }
            
            count = CountVacatedStudents(vacate, 200);
            cout << left << setw(20) << "Name" << setw(20) << "Regno" << setw(20) << "Course" << setw(20) << "Room No" << '\n';
            for (int i = 0; i < count; i++) {
                cout << left << setw(20) << vacate[i].name
                     << setw(20) << vacate[i].regno
                     << setw(20) << vacate[i].course
                     << setw(20) << vacate[i].roomno << '\n';
            }
            break;
        }
        
        case 10: {
           if (!userlogin) {
        cout << "No student is currently logged in.";
        break;
    } 
        userlogin = false;
        userloggedInId = 0;
        userloginPassword = "";
        cout << "Student logged out successfully.";
        
    break;
}

       case 11: {
          if (!adminlogin) {
        cout << "No admin is currently logged in.";
        break;
    } 
        adminlogin = false;
        adminloggedInId = 0;
        adminloginPassword = "";
        cout << "Admin logged out successfully.";

    break;
   }

        case 12: {
          cout << "Exiting program...";
          break;
   }

        default:
            cout << "Invalid choice.\n";
}
} while (choice != 12);

    return 0;
}