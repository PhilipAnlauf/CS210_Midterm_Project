#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;

template <typename T>
struct School
{
    School(T nameIN, T addressIN, T cityIN, T stateIN, T countyIN): name(nameIN), address(addressIN), city(cityIN), state(stateIN), county(countyIN), next(nullptr) {}
    T name, address, city, state, county; //String details for the school

    School* next; // A pointer to the next school struct object
};

template <typename T>
class schoolSinglyLinkedList
{
    private:
        School<T>* head;
    public:
        schoolSinglyLinkedList() : head(nullptr) {}

        ~schoolSinglyLinkedList() {};

        void insertLast(string nameIN, string addressIN, string cityIN, string stateIN, string countyIN)
        {
            //For insert last a new temporary school class is made
            School<T>* newSchool = new School<T>(nameIN, addressIN, cityIN, stateIN, countyIN);

            //If head is null then the linked list is empty and newSchool is assigned as the head
            if (head == nullptr)
            {
                head = newSchool;
            }
            //otherwise program starts at head using the temp and loops through until temp's next is null and assigns
            //the null spot as the newSchool
            else
            {
                School<T>* temp = head;

                while (temp->next != nullptr)
                {
                    temp = temp->next;
                }
                temp->next = newSchool;
            }
        }

        void insertFirst(string nameIN, string addressIN, string cityIN, string stateIN, string countyIN)
        {
            //For insertFirst a new school is made using inputs.
            School<T>* newSchool = new School<T>(nameIN, addressIN, cityIN, stateIN, countyIN);

            //If head is null then the linked list is empty and newSchool is assigned as the head
            if (head == nullptr)
            {
                head = newSchool;
            }
            else
            {
                //Otherwise newSchool's next is assigned to the current head and then newSchool is assigned as the new head
                newSchool->next = head;
                head = newSchool;
            }
        }

        void deleteByName(string nameIN)
        {
            //Temp is assigned as head for use in looping later
            School<T>* temp = head;

            if (head == nullptr)
            {
                //if head is null then array is empty and method ends
                return;
            }
            //Otherwise while temp is still head, if temp is the one to be deleted then...
            if (temp->name == nameIN)
            {
                //... head is assigned as temps next and temp (previous head) is deleted, the method then ends
                head = temp->next;
                delete temp;
                return;
            }
            //Otherwise the program will loop checking if temps next to see if its the school to delete, if so
            //temps next is held in a temporary object called hold, temps next is then assign as temps next next
            //and the school in hold is then deleted and method ends
            while (temp->next != nullptr && temp != nullptr)
            {
                if (temp->next->name == nameIN)
                {
                    School<T>* hold = temp->next;
                    temp->next = temp->next->next;
                    delete hold;
                    return;
                }
                temp = temp->next;
            }
            cout << "No such school." << endl;

        }

        //Display method uses same temp object loop untill reaching a null pointer, printing each school's details
        void display()
        {
            School<T>* temp = head;
            while (temp != nullptr)
            {
                cout << temp->name << ", " << temp->address << ", " << temp->city << ", " << temp->state << ", " << temp->county << endl;
                temp = temp->next;
            }
        }

        //Find by name uses a temp loop starting at head
        void findByName(string nameIN)
        {
            School<T>* temp = head;

            //If head is null array is empty and the method ends
            if (head == nullptr)
            {
                return;
            }
            //otherwise program loops until temp is null
            while (temp != nullptr)
            {
                //if temps name is the wanted name then program displays the schools details and loop ends
                if (temp->name == nameIN)
                {
                    cout << temp->name << ", " << temp->address << ", " << temp->city << ", " << temp->state << ", " << temp->county << endl;
                    return;
                }
                temp = temp->next;
            }
            //If the loop doesn't find the school then it displays as such
            cout << "No such school." << endl;

        }
    
};

//Given class.
class CSVReader
{
    public:
        static vector<vector<string>> readCSV(const string& filename)
        {
            ifstream file(filename);
            vector<vector<string>> data;
            string line, word;

            if (!file.is_open())
            {
                cerr << "Error: Could not open file " << filename << endl;
                return data;
            }

            while (getline(file, line))
            {
                stringstream ss(line);
                vector<string> row;
                while (getline(ss, word, ','))
                {
                    row.push_back(word);
                }
                data.push_back(row);
            }
            file.close();
            return data;
        }
};
//
int main()
{
    schoolSinglyLinkedList<string> schoolList;
    CSVReader csv;

    auto startInsertTime = chrono::high_resolution_clock::now();
    //vector<vector<string>> csvSchoolList = csv.readCSV("Illinois_Schools.csv");
    vector<vector<string>> csvSchoolList = csv.readCSV("USA_Schools.csv");
    vector<string> holdingVector;
    for (int i = 0; i < csvSchoolList.size(); i++) {
        for (int j = 0; j < csvSchoolList[i].size(); j++) {
            holdingVector.push_back(csvSchoolList[i][j]);
        }
        schoolList.insertFirst(holdingVector.at(0), holdingVector.at(1), holdingVector.at(2), holdingVector.at(3), holdingVector.at(4));
        holdingVector.clear();
    }
    auto endInsertTime = chrono::high_resolution_clock::now();
    double timeTakenInsertion = chrono::duration_cast<chrono::microseconds>(endInsertTime - startInsertTime).count();

    short input;
    string schoolName;
    cout << "Time taken for insertion (Normal) " << timeTakenInsertion << " microseconds" << endl;
    while (true)
    {
        cout << "1. List schools." << endl;
        cout << "2. Search for school by name." << endl;
        cout << "3. Delete school by it's name." << endl;
        cout << "4. exit." << endl;

        string choiceHold;
        getline(cin, choiceHold);
        input = stoi(choiceHold);

        auto start = chrono::high_resolution_clock::now(), end = chrono::high_resolution_clock::now();
        auto timeTakenDisplay = 0;
        switch (input)
        {
            case 1:
                start = chrono::high_resolution_clock::now();
                schoolList.display();
                cout << endl;
                end = chrono::high_resolution_clock::now();
                timeTakenDisplay = chrono::duration_cast<chrono::microseconds>(end - start).count();
                cout << "Display time taken to display (Normal): " << timeTakenDisplay << " microseconds" << endl;
                break;
            case 2:
                cout << "School name?: ";
                getline(cin, schoolName);
                start = chrono::high_resolution_clock::now();
                schoolList.findByName(schoolName);
                end = chrono::high_resolution_clock::now();
                timeTakenDisplay = chrono::duration_cast<chrono::microseconds>(end - start).count();
                cout << "Time taken to search by name (Normal): " + to_string(timeTakenDisplay) << " microseconds" << endl;
                break;
            case 3:
                cout << "School name?: ";
                getline(cin, schoolName);
                cout << endl;
                start = chrono::high_resolution_clock::now();
                schoolList.deleteByName(schoolName);
                end = chrono::high_resolution_clock::now();
                timeTakenDisplay = chrono::duration_cast<chrono::microseconds>(end - start).count();
                cout << "Time taken to delete by name (Normal): " + to_string(timeTakenDisplay) << " microseconds" << endl;
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid input." << endl;
        }
    }
}