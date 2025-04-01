#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <bitset>

using namespace std;

//Struct school holds typical data on a school as well as a next pointer for linked list storage
struct School
{
    string name, address, city, state, county; //String details for the school

    School(string nameIN, string addressIN, string cityIN, string stateIN, string countyIN): name(std::move(nameIN)),
           address(std::move(addressIN)), city(std::move(cityIN)), state(std::move(stateIN)), county(std::move(countyIN)), next(nullptr) {}

    School* next;
};

//The get hash index will add the ascii value of each character in the name of the school and get the modulo of 100
//from the summed ascii value to place the school in an index
int getHashIndex(string& schoolNameIN)
{
    int asciiIntSum = 0;
    for(const char character : schoolNameIN)
    {
        asciiIntSum += stoi(to_string(static_cast<int>(character)));
    }
    return asciiIntSum % 100;
}

//Class SchoolHashTableHolds methods and array for the hash table of schools
class SchoolHashTable
{
    private:
        //A array of schools size 100 is created all initialized to nullptr
        School* schoolList[100] = {nullptr};
    public:
        //InsertSchool will take a school in, get it's has index with getHashIndex(school name) and place according to
        //linked list traversal in the index it was assigned
        void insertSchool(School* newSchool)
        {
            const int hashIndex = getHashIndex(newSchool->name);

            if (hashIndex == -1) { return; }
            if(schoolList[hashIndex] == nullptr) { schoolList[hashIndex] = newSchool; return;}
            School* temp = schoolList[hashIndex];
            while(temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newSchool;
        }

        //display will traverse through all indexes of the array and if a index has a school it will then traverse
        //that index as it would a linked list until it reaches a nullptr, printing all values of each school
        void display()
        {
            for (auto& i : schoolList)
            {
                if (i != nullptr)
                {
                    cout << i->name << ", " << i->address << ", " << i->city << ", "
                         << i->state << ", " << i->county << endl;
                    School *temporarySchool = i->next;
                    while (temporarySchool != nullptr)
                    {
                        cout << temporarySchool->name << ", " << temporarySchool->address << ", " << temporarySchool->city << ", "
                             << temporarySchool->state << ", " << temporarySchool->county << endl;
                        temporarySchool = temporarySchool->next;
                    }
                }
            }
            cout << endl;
        }

    //Find by name will take a name in and first get its hash index for the name given, it will then go to that index
    //and traverse as you would a linked list checking each name until a match is found, if nullptr is reached school doesnt exist
    void findByName(string schoolName) const
    {
            const School *temporarySchool = schoolList[getHashIndex(schoolName)];
            while (temporarySchool != nullptr)
            {
                if (temporarySchool->name == schoolName)
                {
                    cout << temporarySchool->name << ", " << temporarySchool->address << ", " << temporarySchool->city << ", "
                         << temporarySchool->state << ", " << temporarySchool->county << endl;
                    cout << endl;
                    return;
                }
                temporarySchool = temporarySchool->next;
            }
            cout << "School not found" << endl;
            cout << endl;
    }

    //Delete by name takes a name in and gets it's hash index with the given name and checks to see, it first checks to
    //see if the first index is a null school, meaning nothing is in that index, it will then check if the first index
    //is the toDelete school, if so it will hold it in a new variable and then set the first index to the next school
    //it will then delete the original index to free the memory, afterwards it will traverse the same way it would a
    //linked list and then delete and reassign as needed
    void deleteByName(string schoolName)
    {
            if (schoolList[getHashIndex(schoolName)] == nullptr)
            {
                cout << "School not found" << endl;
                return;
            }

            School *temporarySchool = schoolList[getHashIndex(schoolName)];

            if (temporarySchool->name == schoolName)
            {
                schoolList[getHashIndex(schoolName)] = temporarySchool->next;
                delete temporarySchool;
                return;
            }
            while (temporarySchool->next != nullptr)
            {
                if (temporarySchool->next->name == schoolName)
                {
                    const School *hold = temporarySchool->next;
                    temporarySchool->next = temporarySchool->next->next;
                    delete hold;
                    return;
                }
                temporarySchool = temporarySchool->next;
            }
            cout << "School not found" << endl;
            cout << endl;
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

int main()
{
    SchoolHashTable hashSchoolList;
    CSVReader csv;

    vector<vector<string>> csvSchoolList = CSVReader::readCSV("schools_list.csv");

    vector<string> holdingVector;
    for (auto & i : csvSchoolList) {
        for (const auto & j : i) {
            holdingVector.push_back(j);
        }

        auto* temp = new School(holdingVector.at(0), holdingVector.at(1),
                                          holdingVector.at(2), holdingVector.at(3),
                                          holdingVector.at(4));

        hashSchoolList.insertSchool(temp);
        holdingVector.clear();
    }

    string schoolName;
    while (true)
    {
        cout << "1. List schools." << endl;
        cout << "2. Search for school by name." << endl;
        cout << "3. Delete school by it's name." << endl;
        cout << "4. exit." << endl;

        string choiceHold;
        getline(cin, choiceHold);

        switch (stoi(choiceHold))
        {
            case 1:
                hashSchoolList.display();
            break;
            case 2:
                cout << "School name?: ";
                getline(cin, schoolName);
                hashSchoolList.findByName(schoolName);
            break;
            case 3:
                cout << "School name?: ";
                getline(cin, schoolName);
                hashSchoolList.deleteByName(schoolName);
                cout << endl;
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice." << endl;
        }
    }
}
