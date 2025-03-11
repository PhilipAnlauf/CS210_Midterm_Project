#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

template <typename T>
struct School
{
    School(T nameIN, T addressIN, T cityIN, T stateIN, T countyIN): name(nameIN),
           address(addressIN), city(cityIN), state(stateIN), county(countyIN),
           leftChild(nullptr), rightChild(nullptr) {}

    T name, address, city, state, county; //String details for the school

    School* leftChild; // A pointer to the schools left child
    School* rightChild; // A pointer to the schools right child
};

template <typename T>
class binarySearchTree
{
    private:
        School<T>* root;
    public:
        binarySearchTree() : root(nullptr) {}

        ~binarySearchTree() {};

        void insert(School<T>* schoolIN)
        {
              if(root == nullptr)
              {
                  root = schoolIN;
                  return;
              }

              School<T>* temp = root;

              while(temp != nullptr)
              {
                   if(schoolIN->name < temp->name)
                   {
                       if(temp->leftChild == nullptr)
                       {
                           temp->leftChild = schoolIN;
                           return;
                       }
                       temp = temp->leftChild;
                   }
                   else if(schoolIN->name > temp->name)
                   {
                       if(temp->rightChild == nullptr)
                       {
                           temp->rightChild = schoolIN;
                           return;
                       }
                       temp = temp->rightChild;
                   }
              }

        }

        void findByName(string& nameIN)
        {
            School<T>* temp = root;
            while(temp != nullptr)
            {
                if(temp->name == nameIN)
                {
                    cout << temp->name << ", " << temp->address << ", " << temp->city << ", " << temp->state << ", "
                         << temp->county << endl;
                    return;
                }
                if(nameIN > temp->name)
                {
                    temp = temp->rightChild;
                }
                else
                {
                    temp = temp->leftChild;
                }
            }
            cout << "No such school" << endl;
        }

        School<T>* getMinimumNode(School<T>* schoolIN)
        {
            while (schoolIN->leftChild != nullptr)
            {
                schoolIN = schoolIN->leftChild;
            }

            return schoolIN;
        }

        School<T>* getMaximumNode(School<T>* schoolIN)
        {
            while (schoolIN->rightChild != nullptr)
            {
                schoolIN = schoolIN->rightChild;
            }

            return schoolIN;
        }

        void deleteNode(string schoolName)
        {
            School<T>* temp = root;
            School<T>* tempParent = nullptr;

            while (temp != nullptr && temp->name != schoolName)
            {
                tempParent = temp;
                if (schoolName > temp->name)
                {
                    temp = temp->rightChild;
                }
                else
                {
                    temp = temp->leftChild;
                }
            }

            if (temp == nullptr)
            {
                cout << "School not found" << endl;
                return;
            }

            //If node has no children
            if (temp->leftChild == nullptr && temp->rightChild == nullptr)
            {
                if (temp == root)
                {
                    root = nullptr;
                }
                if (tempParent->leftChild == temp)
                {
                    tempParent->leftChild = nullptr;
                }
                else if (tempParent->rightChild == temp)
                {
                    tempParent->rightChild = nullptr;
                }
                delete temp;
                return;
            }
            //if node has left child
            if (temp->leftChild != nullptr && temp->rightChild == nullptr)
            {
                School<T>* hold = getMaximumNode(temp->leftChild);
                string nameHold = hold->name;
                temp->address = hold->address;
                temp->city = hold->city;
                temp->state = hold->state;
                temp->county = hold->county;
                deleteNode(hold->name);
                temp->name = nameHold;
                return;
            }
            //if node has right child/has two children
            if (temp->rightChild != nullptr)
            {
                School<T>* hold = getMinimumNode(temp->rightChild);
                string nameHold = hold->name;
                temp->address = hold->address;
                temp->city = hold->city;
                temp->state = hold->state;
                temp->county = hold->county;
                deleteNode(hold->name);
                temp->name = nameHold;
                return;
            }
        }

        void displayInOrder(School<T>* schoolIN)
        {
            if(schoolIN == nullptr)
            {
                return;
            }
            displayInOrder(schoolIN->leftChild);
            cout << schoolIN->name << ", " << schoolIN->address << ", " << schoolIN->city << ", " << schoolIN->state
                 << ", " << schoolIN->county << endl;
            displayInOrder(schoolIN->rightChild);
        }

        void displayPreOrder(School<T>* schoolIN)
        {
            if(schoolIN == nullptr)
            {
                return;
            }
            cout << schoolIN->name << ", " << schoolIN->address << ", " << schoolIN->city << ", " << schoolIN->state
                 << ", " << schoolIN->county << endl;
            displayInOrder(schoolIN->leftChild);
            displayInOrder(schoolIN->rightChild);
        }

        void displayPostOrder(School<T>* schoolIN)
        {
            if(schoolIN == nullptr)
            {
                return;
            }
            displayInOrder(schoolIN->leftChild);
            displayInOrder(schoolIN->rightChild);
            cout << schoolIN->name << ", " << schoolIN->address << ", " << schoolIN->city << ", " << schoolIN->state
                 << ", " << schoolIN->county << endl;
        }

        void display()
        {
            cout << "Display in order:" << endl;
            displayInOrder(root);
            cout << endl;
            cout << "Display pre order:" << endl;
            displayPreOrder(root);
            cout << endl;
            cout << "Display post order:" << endl;
            displayPostOrder(root);
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
    binarySearchTree<string> schoolList;
    CSVReader csv;

    vector<vector<string>> csvSchoolList = csv.readCSV("schools_list.csv");

    vector<string> holdingVector;
    for (int i = 0; i < csvSchoolList.size(); i++) {
        for (int j = 0; j < csvSchoolList[i].size(); j++) {
            holdingVector.push_back(csvSchoolList[i][j]);
        }

        School<string>* temp = new School(holdingVector.at(0), holdingVector.at(1),
                                           holdingVector.at(2), holdingVector.at(3),
                                         holdingVector.at(4));

        schoolList.insert(temp);
        holdingVector.clear();
    }

    short input;
    string schoolName;
    while (true)
    {
        cout << "1. List schools." << endl;
        cout << "2. Search for school by name." << endl;
        cout << "3. Delete school by it's name." << endl;
        cout << "4. exit." << endl;

        string choiceHold;
        getline(cin, choiceHold);

        input = stoi(choiceHold);

        switch (input)
        {
            case 1:
                schoolList.display();
            cout << endl;
            break;
            case 2:
                cout << "School name?: ";
            getline(cin, schoolName);
            schoolList.findByName(schoolName);
            cout << endl;
            break;
            case 3:
                cout << "School name?: ";
            getline(cin, schoolName);
            cout << endl;
            schoolList.deleteNode(schoolName);
            break;
            case 4:
                return 0;
            default:
                cout << "Invalid input." << endl;
        }
    }
}
