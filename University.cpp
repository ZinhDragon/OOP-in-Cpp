#include <iostream>
#include <cstring>
#include <list>
#include <iterator>
#include <iomanip>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Lecturer{
public:
    string name;
    int ID;
    string room;
    Lecturer(){}
    Lecturer(string name, int ID, string room){
        this->name = name;
        this->ID = ID;
        this->room = room;
    }
    void print(){
        cout<<left<<setfill('.')<<setw(20)<<"\tLecturer Name"<<right<<setfill('.')<<setw(10)<<this->name<<".."<<this->ID<<".."<<this->room<<endl;

    }
    int getID(){
        return this->ID;
    }
    ~Lecturer(){};
};

class Club{
public:
    string name;
    int locatedBuilding;
    string phoneNumber;
    Club(){};
    Club(string name, int locatedBuilding, string phoneNumber){
        this->name = name;
        this->locatedBuilding = locatedBuilding;
        this->phoneNumber = phoneNumber;
    };
    ~Club(){};
    void print(){
        cout<<left<<setfill('.')<<setw(30)<<"\t\tClub Name"<<this->name<<endl;
        cout<<left<<setfill('.')<<setw(30)<<"\t\tLocated at building no."<<this->locatedBuilding<<endl;
        cout<<left<<setfill('.')<<setw(30)<<"\t\tPhone number"<<this->phoneNumber<<endl;
        cout<<endl;
    };
};

class Campus{
public:
    list<Club> listOfClub;
    string name;
    string address;
    double distance;
    int n = 0;
    Campus(){};
    Campus(string name, string address, double distance){
        this->name = name;
        this->address = address;
        this->distance = distance;
    };
    //void addClub(Club club){

    void addClub(string name, int locatedBuilding, string phoneNumber){
        listOfClub.push_back(Club(name, locatedBuilding, phoneNumber));
        n++;
    };
    void removeClub(int pos){
        list<Club>::iterator it = listOfClub.begin();
        advance(it, pos);
        it = listOfClub.erase(it);
        n--;
    }
    void printClub(){
        for(list<Club>::iterator iter = listOfClub.begin(); iter != listOfClub.end(); iter++){
            iter->print();
        }
    }
    void print(){
        cout<<left<<setfill('.')<<setw(30)<<"\tCampus Name"<<this->name<<endl;
        cout<<left<<setfill('.')<<setw(30)<<"\tAddress"<<this->address<<endl;
        cout<<left<<setfill('.')<<setw(30)<<"\tDistance to the city center"<<this->distance<<endl;
        cout<<"\t"<<this->n<<" Clubs >>>>"<<endl;
        printClub();
    }
    ~Campus(){};

};

class University{
private:
    vector<Lecturer> listOfLecturer;
public:
    vector<int> setOfID;
    list<Campus> listOfCampus;
    string name;
    int n = 0;
    University(){}
    University(string name){
        this->name = name;
    }
    void addCampus(Campus campus){
        listOfCampus.push_back(campus);
    }
    int j = 0;
    void addLecturer(Lecturer lecturer){
        listOfLecturer.push_back(lecturer);
        setOfID.push_back(lecturer.getID());
        if((j > 0)&&(checkDuplication(listOfLecturer.at(j).getID()))){
            listOfLecturer.erase(listOfLecturer.begin() + j);
            j--;
        }
        j++;
    }

    bool checkDuplication(int numCheck){
        for(int ID: setOfID){
            if(numCheck == ID){
                return true;
            } else {
                return false;
            }
        }
    }
    void printLecturer(){
        for(Lecturer lect:listOfLecturer){
            lect.print();
        }
    }
    void print(){
        cout<<left<<setfill('.')<<setw(30)<<"University Name"<<this->name<<endl;
        cout<<"List of "<<this->j<<" Lecturer(/s) >>>>"<<endl;
        printLecturer();
        int i = 1;
        for(list<Campus>::iterator iter = listOfCampus.begin(); iter != listOfCampus.end(); iter++){
            cout<<"Campus no."<<i<<" >>>>"<<endl;
            iter->print();
            i++;
        }
    }

    ~University(){};
};



template <typename T>
void printUni(vector<T*> vect){
    int i = 1;
    for(T* uni: vect){
        cout<<"[#"<<i<<"]"<<"Sample"<<endl;
        uni->print();
        i++;
    }
}

int main(){
    cout<<"Copyrighted Code by ZinhDragon"<<endl;
    //
    Lecturer lec1("Vinh", 18691,"A_303");
    Lecturer lec2("Quang",17766,"B_329");
    Lecturer lec3("Micheal",15623,"C_393");
    Lecturer lec4("Beth",19314,"H_111");
    Lecturer lec5("Samatha",15342,"B_111");
    //
    Campus campus1("Computer Science","B101",15.3);
    campus1.addClub("Artificial Intelligence", 3, "0918356029");
    campus1.addClub("Programming",4,"0942694608");
    //
    Campus campus2("Mechanical Engineering","A304", 10.3);
    campus2.addClub("Robotic", 12, "0949558528");
    campus2.addClub("Machine Fixing",8,"0913415552");
    campus2.addClub("Electric",9,"092310234");
    //
    University myUni("Vietnamese-German University");
    myUni.addCampus(campus1);
    myUni.addCampus(campus2);
    myUni.addLecturer(lec1);
    myUni.addLecturer(lec2);
    myUni.addLecturer(lec1);
    myUni.addLecturer(lec3);

    //
    Campus campus3("Computer Technique","1001",64.3);
    campus3.addClub("Computer Fixing",5,"0113342345");
    campus3.addClub("Computer Architecture",19,"0193433334");
    campus3.addClub("CPU Analysis",88, "03493759913");
    campus3.addClub("Virus Detector",5,"0113342345");
    University otherUni("International Eastern University");
    otherUni.addCampus(campus3);
    otherUni.addLecturer(lec4);
    otherUni.addLecturer(lec5);
    vector<University*> vect;
    vect.push_back(&myUni);
    vect.push_back(&otherUni);

    printUni(vect);
    return 0;
}

