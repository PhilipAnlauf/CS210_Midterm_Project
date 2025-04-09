#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <bitset>
#include <chrono>

using namespace std;

struct School
{
    string name, address, city, state, county; //String details for the school

    School(string nameIN, string addressIN, string cityIN, string stateIN, string countyIN): name(std::move(nameIN)),
           address(std::move(addressIN)), city(std::move(cityIN)), state(std::move(stateIN)), county(std::move(countyIN)), next(nullptr) {}

    School* next;
};

int getHashIndex(string& schoolNameIN)
{
    int asciiIntSum = 0;
    for(const char character : schoolNameIN)
    {
        asciiIntSum += stoi(to_string(static_cast<int>(character)));
    }
    return asciiIntSum % 800;
}
//
class SchoolHashTable
{
    private:
        School* schoolList[1000] = {nullptr};
    public:
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

    auto start = chrono::high_resolution_clock::now();
    //vector<vector<string>> csvSchoolList = csv.readCSV("Illinois_Schools.csv");
    vector<vector<string>> csvSchoolList = csv.readCSV("USA_Schools.csv");

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
    auto end = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Insertion time taken (Hash): " << timeTaken << " microseconds"<< endl;
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
                start = chrono::high_resolution_clock::now();
                hashSchoolList.display();
                end = chrono::high_resolution_clock::now();
                timeTaken = chrono::duration_cast<chrono::microseconds>(end - start).count();
                cout << "Time taken to display (Hash): " << timeTaken << " microseconds" << endl;
            break;
            case 2:
                cout << "School name?: ";
                getline(cin, schoolName);
                start = chrono::high_resolution_clock::now();
                hashSchoolList.findByName(schoolName);
                end = chrono::high_resolution_clock::now();
                timeTaken = chrono::duration_cast<chrono::microseconds>(end - start).count();
                cout << "Time taken to search by name (Hash): " << timeTaken << " microseconds" << endl;
            break;
            case 3:
                cout << "School name?: ";
                getline(cin, schoolName);
                start = chrono::high_resolution_clock::now();
                hashSchoolList.deleteByName(schoolName);
                end = chrono::high_resolution_clock::now();
                timeTaken = chrono::duration_cast<chrono::microseconds>(end - start).count();
                cout << "Time taken to delete by name (Hash): " << timeTaken << " microseconds" << endl;
                cout << endl;
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice." << endl;
        }
    }
}
