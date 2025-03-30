#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <bitset>

using namespace std;

struct School
{
    string name, address, city, state, county; //String details for the school

    School(string nameIN, string addressIN, string cityIN, string stateIN, string countyIN): name(std::move(nameIN)),
           address(std::move(addressIN)), city(std::move(cityIN)), state(std::move(stateIN)), county(std::move(countyIN)), next(nullptr) {}

    School* next;
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

int getHashIndex(string& schoolNameIN)
{
      int asciiIntSum = 0;
      for(const char character : schoolNameIN)
      {
            asciiIntSum += stoi(to_string(static_cast<int>(character)));
      }
      return asciiIntSum % 100;
}

void insertSchool(School* newSchool, School* schoolListIN[])
{
    int hashIndex = getHashIndex(newSchool->name);

    if (hashIndex == -1) { return; }
    if(schoolListIN[hashIndex] == nullptr) { schoolListIN[hashIndex] = newSchool; return;}
    School* temp = schoolListIN[hashIndex];
    while(temp->next != nullptr)
    {
      temp = temp->next;
    }
    temp->next = newSchool;
}

int main()
{
    School* schoolList[100] = {nullptr};
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

        insertSchool(temp, schoolList);
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

        School* temporarySchool;
        bool temporaryBoolean;

        switch (stoi(choiceHold))
        {
            case 1:
                for (auto& i : schoolList)
                {
                    if (i != nullptr)
                    {
                        cout << i->name << ", " << i->address << ", " << i->city << ", "
                             << i->state << ", " << i->county << endl;
                        temporarySchool = i->next;
                        while (temporarySchool != nullptr)
                        {
                            cout << temporarySchool->name << ", " << temporarySchool->address << ", " << temporarySchool->city << ", "
                                 << temporarySchool->state << ", " << temporarySchool->county << endl;
                            temporarySchool = temporarySchool->next;
                        }
                    }
                }
                cout << endl;
            break;
            case 2:
                temporaryBoolean = false;
                cout << "School name?: ";
                getline(cin, schoolName);
                temporarySchool = schoolList[getHashIndex(schoolName)];
                while (temporarySchool != nullptr)
                {
                    if (temporarySchool->name == schoolName)
                    {
                        cout << temporarySchool->name << ", " << temporarySchool->address << ", " << temporarySchool->city << ", "
                             << temporarySchool->state << ", " << temporarySchool->county << endl;
                        temporaryBoolean = true;
                        cout << endl;
                        break;
                    }
                    temporarySchool = temporarySchool->next;
                }
                if (temporaryBoolean) { break; }
                cout << "School not found" << endl;
                cout << endl;
            break;
            case 3:
                cout << "School name?: ";
                getline(cin, schoolName);
                cout << endl;

                break;

        }
    }
}
