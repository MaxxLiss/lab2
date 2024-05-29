#ifndef LAB2_DEQUEMENU_H
#define LAB2_DEQUEMENU_H

#include <iostream>

using namespace std;

#include "../Deque/Deque.h"

#define EMPTY if (deque == nullptr) {\
                cout << "Deque is empty.\n";\
                break;}

#define DELETE delete deque;\
                deque = nullptr;

#define PRINT cout << "Deque:\n" << deque << endl;

void startTalker() {
    cout << "\nSelect an option:\n"
            "1. Create a new deque\n"
            "0. Finish program\n"
            ">";
}

void talker() {
    cout << "\nSelect an option:\n"
            "1. Create a new deque\n"
            "2. Print the deque\n"
            "3. Get the first element\n"
            "4. Get the last element\n"
            "5. Get an element by index\n"
            "6. Get the length of the deque\n"
            "7. Append an element\n"
            "8. Prepend an element\n"
            "9. Get subDeque\n"
            "10. Sort\n"
            "0. Finish program\n"
            ">";
}

void dequeMenu() {
    int flag = 1, choice, index;
    float value;
    Deque<float> *deque = nullptr;
    Deque<float> *tmpDeque = nullptr;

    bool created = false;

    while (!created) {
        startTalker();
        cin >> choice;

        switch (choice) {
            case 1:     // New deque
                if (deque != nullptr) { DELETE }
                deque = new Deque<float>;
                created = true;
                break;

            case 0:     // Finish
                flag = 0;
                DELETE
                break;
            default:
                cout << "Wrong value" << endl;
        }
    }

    while (flag) {
        talker();
        cin >> choice;

        switch (choice) {
            case 1:     // New deque
                if (deque != nullptr) { DELETE }
                deque = new Deque<float>;
                break;

            case 2:     // Print the deque
                EMPTY
                cout << "Deque:\n" << deque << endl;
                break;

            case 3:     // First element
                EMPTY
                PRINT
                try {
                    cout << "First element: " << deque->GetFirst() << endl;
                } catch (...) {
                    cout << "Something went wrong" << endl;
                }
                break;

            case 4:     // Last element
                EMPTY
                PRINT
                try {
                    cout << "Last element: " << deque->GetLast() << endl;
                } catch (...) {
                    cout << "Something went wrong" << endl;
                }
                break;

            case 5:     // Element by index
                EMPTY
                PRINT
                cout << "Enter index of element: ";
                cin >> index;
                if (index < 0 || index >= deque->GetLength()) {
                    cout << "Error. Index out of range.\n";
                    break;
                }
                cout << "Element at index " << index << ": " << deque->Get(index) << endl;
                break;

            case 6:     // Length of the deque
                EMPTY
                PRINT
                cout << "Deque length: " << deque->GetLength() << endl;
                break;

            case 7:     // Append
                PRINT
                cout << "Enter value to Append: ";
                cin >> value;
                deque->Append(value);
                PRINT
                break;

            case 8:     // Prepend an element
                PRINT
                cout << "Enter the element to Prepend: ";
                cin >> value;
                deque->Prepend(value);
                PRINT
                break;

            case 9:
                EMPTY
                PRINT
                int s, e;
                cout << "Enter the index of subDeque: ";
                cin >> s >> e;
                Deque<float>* tmp;
                try {
                    tmp = deque->GetSubDeque(s, e);
                } catch (...) {
                    cout << "Something went wrong" << endl;
                    break;
                }
                cout << "SubDeque:\n" << tmp << endl;
                delete tmp;
                break;

            case 10:
                EMPTY
                PRINT
                tmpDeque = Sort(deque);
                cout << "Sorted deque: " << tmpDeque << endl;

                delete tmpDeque;
                break;

            case 0:     // Finish
                flag = 0;
                DELETE
                break;
            default:
                cout << "Wrong value" << endl;
        }

    }
}

#endif //LAB2_DEQUEMENU_H
