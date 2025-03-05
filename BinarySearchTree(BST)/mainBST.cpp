#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

template <typename T>
struct School
{
    School(T nameIN, T addressIN, T cityIN, T stateIN, T countyIN): name(nameIN),
           address(addressIN), city(cityIN), state(stateIN), county(countyIN), leftChild(nullptr), rightChild(nullptr) {}

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

    vector<vector<string>> csvSchoolList = csv.readCSV("schoolList.csv");

    vector<string> holdingVector;
    for (int i = 0; i < csvSchoolList.size(); i++) {
        for (int j = 0; j < csvSchoolList[i].size(); j++) {
            holdingVector.push_back(csvSchoolList[i][j]);
        }

        School<string>* temp = new School(holdingVector.at(0), holdingVector.at(1), holdingVector.at(2), holdingVector.at(3), holdingVector.at(4));

        schoolList.insert(temp);
        holdingVector.clear();
    }

    School<string>* temp = new School<string>("Belvadeer Highschool", "123 Cherry Ln.", "Gary", "Indiana", "Cook");
    schoolList.insert(temp);
    temp = new School<string>("Peoria Highschool", "321 Cherry Ln.", "Peoria", "Illinois", "Peoria");
    schoolList.insert(temp);

    short input;
    string schoolName;
    while (true)
    {
        cout << "1. List schools." << endl;
        cout << "2. Search for school by name." << endl;
        cout << "3. Delete school by it's name." << endl;
        cout << "4. exit." << endl;

        cin >> input;
        cin.ignore();
        cin.clear();

        switch (input)
        {
            case 1:
                //schoolList.display();
                cout << endl;
                break;
            case 2:
                cout << "School name?: ";
                getline(cin, schoolName);
                cin.ignore();
                cin.clear();
                //schoolList.findByName(schoolName);
                cout << endl;
                break;
            case 3:
                cout << "School name?: ";
                getline(cin, schoolName);
                cin.ignore();
                cin.clear();
                cout << endl;
                //schoolList.deleteByName(schoolName);
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid input." << endl;
        }
    }
}

/*TODO:
 *1. Create Deletion method, handling nodes with no children, one child, or two child nodes
 *2. DisplayInOrder() method
 *3. DisplayPreOrder() method
 *4. DisplayPostOrder() method
 */

