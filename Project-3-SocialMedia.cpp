#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

class User {
public:
    string firstName;
    string lastName;
    int age;
    string gender;

    User() {};

    User(string firstName, string lastName, int age, string gender) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->age = age;
        this->gender = gender;
    }
};

map<string, User> mapUserName;
map<string, set<string>> Friends;

void addUser(string userName, User user) {
    if (mapUserName.find(userName) == mapUserName.end()) {
        mapUserName[userName] = user;
    } else {
        cout << "UserName Already Taken\n";
    }
}

void makeThemFriend(string userName1, string userName2) {
    if (mapUserName.find(userName1) != mapUserName.end() && mapUserName.find(userName2) != mapUserName.end()) {
        Friends[userName1].insert(userName2);
        Friends[userName2].insert(userName1);
    } else {
        cout << "One or both usernames do not exist\n";
    }
}

void displayAllUsers() {
    for (auto i : mapUserName) {
        cout << "UserName: " << i.first << ", Name: " << i.second.firstName << " " << i.second.lastName << "\n";
    }
}

void displayAllFriendships() {
    for (auto i : Friends) {
        cout << i.first << " is friends with: ";
        for (auto j : i.second) {
            cout << j << " ";
        }
        cout << "\n";
    }
}

int main() {
    int choice;
    while (true) {
        cout << "1. Add User\n2. Make Friends\n3. Display All Users\n4. Display All Friendships\n5. Exit\n";
        cin >> choice;
        
        if (choice == 1) {
            string userName, firstName, lastName, gender;
            int age;
            cout << "Enter UserName: ";
            cin >> userName;
            cout << "Enter First Name: ";
            cin >> firstName;
            cout << "Enter Last Name: ";
            cin >> lastName;
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Gender: ";
            cin >> gender;
            User newUser(firstName, lastName, age, gender);
            addUser(userName, newUser);
        } else if (choice == 2) {
            string userName1, userName2;
            cout << "Enter First UserName: ";
            cin >> userName1;
            cout << "Enter Second UserName: ";
            cin >> userName2;
            makeThemFriend(userName1, userName2);
        } else if (choice == 3) {
            displayAllUsers();
        } else if (choice == 4) {
            displayAllFriendships();
        } else if (choice == 5) {
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}