#include <iostream>
#include<queue>
#include<vector>
#include <unordered_map>
#include<fstream>
using namespace std;


struct Event {
    string title;
    string date;
    vector<string>participants;
};




unordered_map<int, Event> events;
queue<int>notificationQueue;



void processNotification(){
    
    if(notificationQueue.empty()){
        cout<<"\nno pending notifications..\n";
        return;
    }
    cout<<"\nProcessing notifications..\n";
    while(!notificationQueue.empty()){
        int id = notificationQueue.front();
        notificationQueue.pop();
        if(events.find(id) != events.end()){
        cout << "notifying event :" << events[id].title<<endl;
    }
    else{
        cout<<"Event no longer exits\n";
    }
}
}
// Add Event
void addEvent() {
    int id;
    string title, date;

    cout << "Enter Event ID: ";
    cin >> id;
  if(id<=0){
      cout << "invalid id!must be +";
      return;
  }
    cin.ignore(); // clear buffer

    cout << "Enter Event Title: \n";
    getline(cin, title);

    cout << "Enter Event Date: \n";
    getline(cin, date);
    if(title.empty() || date.empty()){
        cout << "title and date cannot be empty\n";
        return;
    }
    if(events.find(id)!= events.end()){
        cout << "Event id already exits!\n";
        return;
    }
    events[id] = {title, date};
    notificationQueue.push(id);
    cout << "Event Added Successfully and queued for notification!\n";
}

// Show Events
void showEvents(){
    if(events.empty()) {
        cout << "No events available.\n";
        return;
    }
    cout << "\n========EVENT DETAILS===========\n";

    for (auto &e : events) {
        cout << "\nID: " << e.first<<endl;
        cout << "\nTitle: " << e.second.title<<endl;
        cout << "\nDate: " << e.second.date<<endl;
        cout << " participants:"<<e.second.participants.size()<<endl;
        cout << "\n---------------------\n";
    }
}
void searchEvent(){
    int id;
    cout << "enter event id to search:";
    cin >> id;
    cout << "\n ======SEARCH RESULT ==========\n";
    if(events.find(id) != events.end()){
        cout << "\nevent found\n";
        cout << "title:"<<events[id].title << endl;
        cout << "date:" << events[id].date << endl;
        }
        else{
            cout<< " event not found.\n";
        }
}
void deleteEvent(){
    int id;
    cout << "enter event id to delete:";
    cin >> id;
    if(events.find(id) != events.end()){
        events.erase(id);
        cout << "event deleted succesfully.\n";
    }
    else{
        cout << "event not found.\n";
    }
}
void registerStudent(){
    int id;
    string name;
    cout<<"enter event id:";
    cin >> id;
    cin.ignore();
    if(events.find(id) == events.end()){
        cout << "event not found.\n";
        return;
    }
    cout << "enter student name:";
    getline(cin,name);
    if(name.empty()){
        cout << "Name cannot be empty!\n";
        return;
    }
    for(auto &p: events[id].participants){
        if(p==name){
            cout << "already registered\n";
            return;
        }
    }
    
    events[id].participants.push_back(name);
    cout<< "Student registerd successfully\n";
}

void showParticipants(){
    int id;
    cout << "enter event id:";
    cin >> id;
    cout << "\n=======PARTICIPANTS============\n";
    if ( events.find(id) == events.end()){
        cout << "event not found.\n";
        return;
    }
    auto &list = events[id].participants;
    if(list.empty()){
        cout << "no participants yet.\n";
        return;
    }
    cout <<"\nparticipants:\n";
    for(auto &name : list){
        cout << "-" << name << endl;
    }
}
void showTotalEvents(){
    cout << "\ntotal events:"<<events.size()<<endl;
}

    

void showMostPopularEvent() {
    if (events.empty()) {
        cout << "No events available.\n";
        return;
    }

    int maxCount = 0;
    string popularEvent = "";

    for (auto &e : events) {
        int count = e.second.participants.size();
        if (count > maxCount) {
            maxCount = count;
            popularEvent = e.second.title;
        }
    }

    cout << "Most Popular Event: " << popularEvent 
         << " (" << maxCount << " participants)\n";
}
void saveToFile(){
    ofstream file("events.txt");
    for(auto &e : events){
        file << e.first << endl;
        file << e.second.title<<endl;
        file << e.second.date<<endl;
        file<<e.second.participants.size()<<endl;
        for(auto &p : e.second.participants){
            file << p << endl;
        }
    }
    file.close();
}
void loadFromFile() {
    ifstream file("events.txt");

    if (!file) return;

    int id, count;
    string title, date, name;

    while (file >> id) {
        file.ignore();

        getline(file, title);
        getline(file, date);

        file >> count;
        file.ignore();

        Event e;
        e.title = title;
        e.date = date;

        for (int i = 0; i < count; i++) {
            getline(file, name);
            e.participants.push_back(name);
        }

        events[id] = e;
    }

    file.close();
}

int main() {
    loadFromFile();
    int choice;

    while (true) {
        cout << "\n===== CampusConnect =====\n";
        cout << "1. Add Event\n";
        cout << "2. Show Events\n";
        cout << "3. process Notification\n";
        cout << "4. search event\n";
        cout << "5.delete event\n";
        cout << "6.Register student\n";
        cout << "7.show participants\n";
        cout << "8.show total events\n";
        cout << "9.show most popular events\n";
        cout << "10.Exit\n";
        cout << "Enter choice: ";
        if(!(cin >> choice)){
            cout << "invalid input!please enter a number.\n";
            cin.clear();
            cin.ignore(1000,'\n');
            continue;
        }

        switch (choice) {
            case 1:
                addEvent();
                break;   
            case 2:
                showEvents();
                break;
            case 3:
                processNotification();
               break;
            case 4:
                searchEvent();
                break;
            case 5:
                deleteEvent();
                break;
            case 6:
               registerStudent();
              break;
            case 7:
               showParticipants();
               break;
            case 8:
               showTotalEvents();
                break;
           case 9:
                showMostPopularEvent();
                break;
          case 10:
               saveToFile();
               cout<<"thank you for using Campus Connect!\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}