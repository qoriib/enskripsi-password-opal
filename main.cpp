#include <iostream>

using namespace std;

struct Node {
    char huruf;
    Node *next;
    Node *prev;
};

struct List {
    Node *first;
    Node *last;
};

List *list = new List();

bool isAdmin = true;

Node *createNode(char huruf) {
    Node *newNode = new Node();
    newNode->huruf = huruf;
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

void insertFirst(char huruf) {
    Node *newNode = createNode(huruf);

    if (list->first == NULL) {
        list->first = newNode;
        list->last = newNode;
    } else {
        newNode->next = list->first;
        list->first->prev = newNode;
        list->first = newNode;
    }
}

void insertLast(char huruf) {
    Node *newNode = createNode(huruf);

    if (list->last == NULL) {
        list->first = newNode;
        list->last = newNode;
    } else {
        newNode->prev = list->last;
        list->last->next = newNode;
        list->last = newNode;
    }
}

void deleteLast() {
    Node *tempNode = list->last;

    list->last->prev->next = NULL;
    list->last = list->last->prev;

    delete tempNode;
}

void deleteFirst() {
    Node *tempNode = list->first;

    list->first->next->prev = NULL;
    list->first = list->first->next;

    delete tempNode;
}

void show() {
    cout
        << "================" << endl
        << "Password anda: ";

    if (isAdmin) {
        Node *tempNode = list->first;

        while (tempNode != NULL) {
            cout << tempNode->huruf;

            tempNode = tempNode->next;
        }
    } else {
        Node *tempNode = list->last;

        while (tempNode != NULL) {
            cout << tempNode->huruf;

            tempNode = tempNode->prev;
        }
    }
    
    cout << endl;
}

void encrypt() {
    char hurufDitukar[3];

    // Menghapus 3 terakhir dan menyimpannya
    for (int i = 0; i < 3; i++) {
        hurufDitukar[i] = list->last->huruf;
        deleteLast();
    }

    // Memasukkan 3 terakhir ke depan
    for (int i = 2; i >= 0; i--) {
        insertFirst(hurufDitukar[i]);
    }

    // Menambahkan huruf X dibelakang
    insertLast('X');
}

void decrypt() {
    // Menghapus X atau node terakhir
    deleteLast();

    char hurufDitukar[3];

    // Menghapus 3 terawal dan menyimpannya
    for (int i = 0; i < 3; i++) {
        hurufDitukar[i] = list->first->huruf;
        deleteFirst();
    }

    // Memasukkan 3 terakhir ke belakang
    for (int i = 2; i >= 0; i--) {
        insertLast(hurufDitukar[i]);
    }
}

void input(string password) {
    // Memasukkan semua huruf pada password ke dalam list
    for (int i = 0; i < password.length(); i++) {
        insertLast(password[i]);
    }
}

int main() {
    int pilihan;
    string password;

    cout << "Masukkan password awal: ";
    cin >> password;
    input(password);

    do {
        string role = isAdmin ? "Admin" : "Anonymous";
        
        cout
            << "================" << endl
            << "Role : " << role << endl
            << "================" << endl
            << "1. Tampilkan password" << endl
            << "2. Enkripsi password" << endl
            << "3. Dekripsi password" << endl
            << "4. Ubah role" << endl
            << "5. Keluar" << endl;

        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: show(); break;
            case 2: encrypt(); break;
            case 3: decrypt(); break;
            case 4: isAdmin = !isAdmin; break;
            default: break;
        }
    } while(pilihan != 5);
}