#include <iostream>

using namespace std;

struct School
{
    School(string nameIN, string addressIN, string cityIN, string stateIN, string countyIN): name(nameIN), address(addressIN), city(cityIN), state(stateIN), county(countyIN), next(nullptr) {}
    string name, address, city, state, county; //String details for the school

    School* next; // A pointer to the next school struct object
};

class schoolSinglyLinkedList
{
    private:
        School* head;
    public:
        schoolSinglyLinkedList() : head(nullptr) {}

        void insertLast(string& nameIN, string& addressIN, string& cityIN, string& stateIN, string& countyIN)
        {
            School* newSchool = new School(nameIN, addressIN, cityIN, stateIN, countyIN);

            if (head == nullptr)
            {
                head = newSchool;
            }
            else
            {
                School* temp = head;

                while (temp->next != nullptr)
                {
                    temp = temp->next;
                }
                temp->next = newSchool;
            }
        }

        void insertFirst(string nameIN, string addressIN, string cityIN, string stateIN, string countyIN)
        {
            School* newSchool = new School(nameIN, addressIN, cityIN, stateIN, countyIN);

            if (head == nullptr)
            {
                head = newSchool;
            }
            else
            {
                newSchool->next = head;
                head = newSchool;
            }
        }

        void deleteByName(string nameIN)
        {
            School* temp = head;

            //First check if empty
            //Then check if head is the nameIN

            //loop check next

            if (head == nullptr)
            {
                return;
            }
            if (temp->name == nameIN)
            {
                head = temp->next;
                delete temp;
                return;
            }
            while (temp->next != nullptr)
            {
                if (temp->next->name == nameIN)
                {
                    School* hold = temp->next;
                    temp->next = temp->next->next;
                    delete hold;
                    return;
                }
            }

        }

        //TODO: PROPERLY DISPLAY DETAILS OF THE SCHOOLS
        void display()
        {
            School* temp = head;
            while (temp != nullptr)
            {
                cout << temp->name << endl;
                temp = temp->next;
            }
        }

        //TODO: ADD A FIND BY NAME METHOD, REUSE DELETE BY NAME BUT JUST PRINT INSTEAD OF DELETE
    
};


int main()
{
    schoolSinglyLinkedList schooList;

    schooList.insertFirst("Belvadeer Highschool", "123 Cherry Ln.", "Gary", "Indiana", "Cook");
    schooList.insertFirst("Peoria Highschool", "321 Cherry Ln.", "Peoria", "Illinois", "Peoria");
    schooList.insertFirst("Applewood Highschool", "123 Apple Ln.", "Chicago", "Illinois", "Cook");
    schooList.deleteByName("Peoria Highschool");
    schooList.display();

}