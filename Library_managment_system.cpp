//  Library Managment system

#include<iostream>
#include<fstream>
#include<iomanip>
#include<conio.h>
#include<ctime>
#include<vector>
#include<string>
using namespace std;

const string BOOKS_FILE = "library_books.txt";
const string MEMBERS_FILE = "library_members.txt";
const string TRANSACTIONS_FILE = "book_transactions.txt";
const string HISTORY_FILE = "transaction_history.txt";
const float FEE_RATE = 2.50;

struct Book {
    string name;
    string author;
    string catagory;
    int quantity;
    int tagnumber;
    double price;
};

struct Date {
    int day, month, year;
};

class Members {
public:
    string members_name;
    int members_id;
    string phone_number, members_address;
    Members() {};
    Members(string name, int id, string phone, string address) {
        members_name = name;
        members_id = id;
        phone_number = phone;
        members_address = address;
    };

};
class Transactions : public Members {
public:
    string book_title;
    double book_price;
    Date borrow_date, return_date;
    Transactions() {};
    Transactions(string name, int id, string phone, string address, Date borrowdate, Date returndate, string title, double price)
        : Members(name, id, phone, address),
        book_price(price),
        book_title(title),
        borrow_date(borrowdate),
        return_date(returndate) {}
};

class History {
public:
    string member_name;
    string book_name;
    Date return_date, borrow_date;
    string book_status;
    History() {};
    History(string memberName, string bookName, Date borrowdate = {}, Date returndate = {}, string status = "") {
        member_name = memberName;
        book_name = bookName;
        borrow_date = borrowdate;
        return_date = returndate;
        book_status = status;
    };
};

void display();
int menuChoice();
void add(vector<Book>& library_books, int& totalbooks);
void members(vector<Members>& library_members, const vector<Transactions>& book_transactions, int& total_members, int& deleted_members);
void details(vector<Book>& library_books, int totalbooks);
void search(vector<Book>& library_books, int& totalbooks, vector<Members>& library_members);
void borrow(vector<Book>& library_books, int totalbooks, vector<Transactions>& book_transactions, const vector<Members>& library_members, vector<History>& transaction_history);
void report(vector<Transactions> books_transactions, vector<Members>& library_members, int totalfees, int totalbooks, vector<History>& transaction_history, int totalmembers);
void returnBook(vector<Transactions>& book_transactions, vector<Book>& library_books, vector<History>& transaction_history);
void calculateFees(vector<Transactions>& book_transactions, vector<Book>& library_books, int& totalfees, vector<History>& transaction_history);

void saveBooksToFile(const vector<Book>& books);
void loadBooksFromFile(vector<Book>& books, int& totalbooks);
void saveMembersToFile(const vector<Members>& members, int& library_members, int total_fees, int deleted_members);
void loadMembersFromFile(vector<Members>& members, int& library_membres, int& total_fees, int& deleted_members);
void saveTransactionsToFile(const vector<Transactions>& transactions);
void loadTransactionsFromFile(vector<Transactions>& transactions);
void saveTransactionHistoryToFile(const vector<History>& transaction_history);
void loadTransactionHistoryFromFile(vector<History>& transaction_history);


int main() {

    int books_total = 0;
    int total_fees = 0;
    int total_members = 0;
    int deleted_members = 0;
    vector<Book> library_books;
    vector<Members> library_members;
    vector<Transactions> book_transactions;
    vector<History> transaction_history;

    loadBooksFromFile(library_books, books_total);
    loadMembersFromFile(library_members, total_members, total_fees, deleted_members);
    loadTransactionsFromFile(book_transactions);
    loadTransactionHistoryFromFile(transaction_history);

    while (true) {
        display();
        int choice = menuChoice();
        switch (choice) {
        case 1:
            add(library_books, books_total);
            break;
        case 2:
            members(library_members, book_transactions, total_members, deleted_members);
            getch();
            break;
        case 3:
            details(library_books, books_total);
            getch();
            break;
        case 4:
            search(library_books, books_total, library_members);
            getch();
            break;
        case 5:
            borrow(library_books, books_total, book_transactions, library_members, transaction_history);
            getch();
            break;
        case 6:
            returnBook(book_transactions, library_books, transaction_history);
            getch();
            break;
        case 7:
            calculateFees(book_transactions, library_books, total_fees, transaction_history);
            getch();
            break;
        case 8:
            report(book_transactions, library_members, total_fees, books_total, transaction_history, total_members);
            getch();
            break;
        case 9:
            saveBooksToFile(library_books);
            saveMembersToFile(library_members, total_members, total_fees, deleted_members);
            saveTransactionsToFile(book_transactions);
            saveTransactionHistoryToFile(transaction_history);
            cout << "All Data is saved to file successfully.\n";
            cout << "Have a good day!!! \n";
            cout << "Exiting... \n";
            exit(1);
            break;

        }


    }
    return 0;
}

void display() {

    cout << "------------------------------------------------\n";
    cout << "----------------Welcome to LMS------------------\n";
    cout << "------------------------------------------------\n";
    cout << "1. Add and Remove Books  \n";
    cout << "2. Member Adminstration  \n";
    cout << "3. Display all available books \n";
    cout << "4. Search for a Book  \n";
    cout << "5. Borrow a Book  \n";
    cout << "6. Return a Book  \n";
    cout << "7. Calculate fees \n";
    cout << "8. Generate  Report \n";
    cout << "9. Exit  \n";
    cout << "------------------------------------------------\n";
}

int menuChoice() {
    int choice;
    while (true) {
        cout << "Your choice: ";
        cin >> choice;
        if (cin.fail() || cin.peek() != '\n' || !(choice >= 1 && choice <= 9)) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid input \n";
            cout << "Please, Enter your choice from the menu(1-9): \n";
        }
        else {
            break;
        }
    }
    return choice;
}

void add(vector<Book>& library_books, int& totalbooks) {

    char to_go_menu, tocontinue;
    cout << "Enter q to go back to the menu: \n";
    to_go_menu = getch();
    if (tolower(to_go_menu) == 'q') {
        return;
    }

    int choice;
    cout << "------------------------------\n";
    cout << "1. To add new books. \n";
    cout << "2. To remove old books. \n";
    cout << "------------------------------\n";

    while (true) {
        cout << "Your choice: ";
        cin >> choice;
        if (cin.fail() || cin.peek() != '\n' || !(choice >= 1 && choice <= 2)) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid input!! \n";
            cout << "Enter a valid choice from the menu(1-2). ";
        }
        else {
            break;
        }
    }

    if (choice == 1) {
        do {

            int size;
            while (true) {
                cout << "Enter the number of books you want to add: ";
                cin >> size;
                if (cin.fail() || cin.peek() != '\n' || size < 1) {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Invalid input!! \n";
                    cout << "Enter a valid number. \n";
                }
                else {
                    break;
                }
            }

            size += totalbooks;
            Book newBook;

            for (int i = totalbooks; i < size; i++) {

            lebel:
                cin.ignore();
                cout << "\nEnter the name of the book #" << i + 1 << ": ";
                getline(cin, newBook.name);
                cout << "Enter Author's name: ";
                getline(cin, newBook.author);

                bool exists = false;
                for (auto& book : library_books) {
                    if (book.name == newBook.name && book.author == newBook.author) {
                        exists = true;
                        cout << "Book already exists. Updating quantity.\n";
                        while (true) {
                            cout << "Enter new quantity: ";
                            cin >> newBook.quantity;
                            if (cin.fail() || cin.peek() != '\n' || newBook.quantity < 0) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                cout << "Invalid input \n";
                                cout << "Please, Enter a valid quantity: \n";
                            }
                            else {
                                break;
                            }
                        }
                        char confirm;
                        cout << "Do you want to confirm the update(y/n): \n";
                        confirm = getch();
                        if (confirm == 'y') {
                            book.quantity += newBook.quantity;
                            cout << "Book's quantity is updated sucessfully!!! \n";
                            break;
                        }
                        else {
                            cout << "Book's quantity update was not sucessfull!! \n";
                            cout << "Do you want to go back to the menu(y/n): \n";
                            to_go_menu = getch();
                            if (tolower(to_go_menu) == 'y') {
                                return;
                            }
                            goto lebel;
                        }
                    }
                }
                if (!exists) {
                    cout << "Enter the Book's catagory: ";
                    getline(cin, newBook.catagory);

                    while (true) {
                        cout << "Enter quantity: ";
                        cin >> newBook.quantity;
                        if (cin.fail() || cin.peek() != '\n' || newBook.quantity <= 0) {
                            cin.clear();
                            cin.ignore(100, '\n');
                            cout << "Invalid input \n";
                            cout << "Please, Enter a valid quantity: \n";
                        }
                        else {
                            break;
                        }
                    }

                    while (true) {
                        cout << "Enter tag number: ";
                        cin >> newBook.tagnumber;
                        if (cin.fail() || cin.peek() != '\n' || newBook.tagnumber < 0) {
                            cin.clear();
                            cin.ignore(100, '\n');
                            cout << "Invalid input \n";
                            cout << "Please, Enter a 3 digit tagnumber: \n";
                        }
                        else {
                            break;
                        }
                    }

                    while (true) {
                        cout << "Enter the price: ";
                        cin >> newBook.price;
                        if (cin.fail() || cin.peek() != '\n' || newBook.price < 0) {
                            cin.clear();
                            cin.ignore(100, '\n');
                            cout << "Invalid input \n";
                            cout << "Please, Enter a valid price. \n";
                        }
                        else {
                            break;
                        }
                    }

                    char confirm;
                    cout << "Do you want to confirm the addition(y/n): \n";
                    confirm = getch();

                    if (tolower(confirm) == 'y') {
                        library_books.push_back(newBook);
                        totalbooks++;
                    }
                    else {
                        cout << "Book addition was not successfull! \n";
                        cout << "Do you want to go back to the menu(y/n): \n";
                        to_go_menu = getch();
                        if (tolower(to_go_menu) == 'y') {
                            return;
                        }
                        goto lebel;
                    }

                }
            }


            cout << "Do you want to continue adding books(y/n): \n";
            tocontinue = getch();

        } while (tolower(tocontinue) == 'y');
    }
    else if (choice == 2) {
        do {

            cin.ignore(100, '\n');
            string title;
            int tagnum, quantity;
            bool isFound = false;
            cout << "Enter the old book title: ";
            getline(cin, title);
            cout << "Enter the tag number: ";
            cin >> tagnum;
            cout << "Enter the quantity of " << title << "you want to remove: ";
            cin >> quantity;

            for (auto& old_book : library_books) {
                if (old_book.name == title && old_book.tagnumber == tagnum) {
                    isFound = true;
                    char confirm;
                    cout << "Do you want to confirm the removal(y/n): \n";
                    confirm = getch();
                    if (confirm == 'y') {
                        old_book.quantity -= quantity;
                        cout << "----------------------------------------\n";
                        cout << "The old book removal was sucessfull!!! \n";
                        cout << "----------------------------------------\n";
                        break;
                    }
                    else {
                        cout << "Old book removal was not sucessfull!! \n";
                        cout << "Do you want to go back to the menu(y/n): \n";
                        to_go_menu = getch();
                        if (tolower(to_go_menu) == 'y') {
                            return;
                        }
                        break;
                    }
                }
            }

            if (!isFound) {
                cout << "The book is not found!!! \n";
            }

            cout << "Do you want to continue removing old books(y/n): \n";
            tocontinue = getch();

        } while (tolower(tocontinue) == 'y');

    }
}
 
void members(vector<Members>& library_members, const vector<Transactions>& book_transactions, int& total_members, int& deleted_members) {

    char to_go_menu, tocontinue;
    cout << "Enter q to go back to the menu: \n";
    to_go_menu = getch();
    if (tolower(to_go_menu) == 'q') {
        return;
    }

    string members_name, phone_number, members_address;
    int choice;

    cout << "-----------------------------\n";
    cout << "1. To add a new member.     \n";
    cout << "2. To remove existing member.\n";
    cout << "-----------------------------\n";

    while (true) {

        cout << "Your choice: ";
        cin >> choice;
        if (cin.fail() || cin.peek() != '\n' || !(choice >= 1 && choice <= 2)) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid input!! \n";
            cout << "Enter a valid choice from the menu(1-2). \n";
        }
        else {
            break;
        }
    }

    if (choice == 1) {

        do {

            bool isMember = false;
            static int id_generator = 1000 + total_members + deleted_members;
            int members_id = id_generator++;

            cin.ignore(100, '\n');
            cout << "Enter the new member's name: ";
            getline(cin, members_name);
            while (true) {
                bool alreadyRegistered = false;
                cout << "Enter " << members_name << "'s phone number +251";
                getline(cin, phone_number);
                bool allDigits = true;
                if (phone_number.length() == 9) {
                    for (char c : phone_number) {
                        if (!isdigit(c)) {
                            allDigits = false;
                            break;
                        }
                    }
                }
                else {
                    cout << "You should put 9 digits for phone number. \n";
                    continue;
                }
                if (allDigits) {
                    phone_number = "+251" + phone_number;
                    for (const auto members : library_members) {
                        if (phone_number == members.phone_number) {
                            alreadyRegistered = true;
                            cout << "This Phone number has been registered for another member. \n";
                            cout << "please, Enter your own phone number. \n";
                            break;
                        }
                    }
                    if (!alreadyRegistered) {
                        break;
                    }
                }
                else {
                    cout << "All should be digits. \n";
                    continue;
                }
            }
            cout << "Enter your address: ";
            getline(cin, members_address);
            for (auto& member : library_members) {
                if (member.members_name == members_name && member.phone_number == phone_number && member.members_address == members_address) {
                    isMember = true;
                    cout << "This member has already been registered. \n";
                    break;
                }
            }

            if (!isMember) {
                char confirm;
                cout << "Do you want to confirm membership(y/n): \n";
                confirm = getch();

                if (tolower(confirm) == 'y') {
                    ++total_members;
                    library_members.emplace_back(members_name, members_id, phone_number, members_address);
                    cout << "----------------------------------------------------------------\n";
                    cout << "Congratulations! You are successfully registered.\n";
                    cout << "Name: " << members_name << "\n";
                    cout << "Your Member ID: " << members_id << "\n";
                    cout << "Please don't forget your Member ID.\n";
                    cout << "----------------------------------------------------------------\n";
                }
                else {
                    --id_generator;
                    cout << "Member registration was unsucessfull!!! \n";
                    cout << "Do you want to go back to the menu(y/n): \n";
                    to_go_menu = getch();
                    if (tolower(to_go_menu) == 'y') {
                        return;
                    }
                }
            }

            cout << "Do you want to continue adding members(y/n): \n";
            tocontinue = getch();

        } while (tolower(tocontinue) == 'y');

        return;

    }
    else if (choice == 2) {

        do {

            string members_name;
            int member_id;
            bool isBorrower = false;
            bool isMember = false;
            cin.ignore(100, '\n');

            cout << "Enter your name: ";
            getline(cin, members_name);
            cout << "Enter your membership id: ";
            cin >> member_id;

            for (const auto& borrow : book_transactions) {
                if (borrow.members_name == members_name && borrow.members_id == member_id) {
                    isBorrower = true;
                    isMember = true;
                    cout << "--------------------------------------------------\n";
                    cout << "You have borrowed book " << borrow.book_title << '\n';
                    cout << "Please, return the book first. or \n";
                    cout << "pay for the book to be unregistered!! \n";
                    cout << "--------------------------------------------------\n";
                    break;
                }
            }

            if (!isBorrower) {
                auto member = library_members.begin();
                while (member != library_members.end()) {
                    if (member->members_name == members_name && member->members_id == member_id) {
                        char confirm;
                        isMember = true;
                        cout << "Do you confirm to be removed from the membersip(y/n): \n";
                        confirm = getch();
                        if (tolower(confirm) == 'y') {
                            --total_members;
                            ++deleted_members;
                            cout << "---------------------------------------------------------------\n";
                            cout << member->members_name << " is no longer a member for the library.\n";
                            cout << "---------------------------------------------------------------\n";
                            member = library_members.erase(member);
                        }
                        else {
                            cout << "Unable to remove a member. \n";
                            cout << "Do you want to go back to the menu(y/n): \n";
                            to_go_menu = getch();
                            if (tolower(to_go_menu) == 'y') {
                                return;
                            }
                            break;
                        }
                    }
                    else {
                        ++member;
                    }
                }
            }

            if (!isMember) {
                cout << "Member is not found!!! \n";
            }

            cout << "Do you want to continue removing a member: \n";
            tocontinue = getch();

        } while (tolower(tocontinue) == 'y');
        return;
    }

}

void details(vector<Book>& library_books, int totalbooks) {

    char to_go_menu;
    cout << "Enter q to go back to the menu: \n";
    to_go_menu = getch();
    if (tolower(to_go_menu) == 'q') {
        return;
    }

    if (!library_books.empty()) {
        cout << "\t\t-----------------------------------------------------------------------------\n";
        cout << "\t\t--------------------------All Available Books--------------------------------\n";
        int i = 0;
        for (const Book& book : library_books) {
            cout << i + 1 << ". Book title: " << book.name << "\t\t"
                << "Author's name: " << book.author << "\t\t"
                << "Catagory: " << book.catagory << "\t\t"
                << "Quantity: " << book.quantity << "\t\t"
                << "Tag number: " << book.tagnumber << "\t" << '\n';
            i += 1;
        }
        cout << "\t\t------------------------------------------------------------------------------\n";
    }
    else {
        cout << "No books are available \n";
    }
}

void search(vector<Book>& library_books, int& totalbooks, vector<Members>& library_members) {

    char to_go_menu, tocontinue;
    cout << "Enter q to go back to the menu: \n";
    to_go_menu = getch();
    if (tolower(to_go_menu) == 'q') {
        return;
    }
    int choice;
    cout << "---------------------------------\n";
    cout << "1. To search for a book \n";
    cout << "2. To search for a member \n";
    cout << "---------------------------------\n";
    while (true) {
        cout << "Your choice: ";
        cin >> choice;
        if (cin.fail() || cin.peek() != '\n' || !(choice <= 2 && choice >= 1)) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid choice \n";
            cout << "Please, Enter your choice from the menu(1-2). \n";
        }
        else {
            break;
        }
    }

    if (choice == 1) {
        do {
            cin.ignore(100, '\n');
            string seachedBook;
            bool isFound = false;
            if (totalbooks == 0) {
                cout << "Books are not added!!! \n";
                return;
            }
            cout << "Enter the book title you want to search for: ";
            getline(cin, seachedBook);

            for (const auto& book : library_books) {
                if (book.name == seachedBook) {
                    cout << "Book is found !!\n";
                    cout << "----------------------------------------------------------------------------\n";
                    cout << "Book title: " << book.name << " Author's name: " << book.author << " Catagory: " << book.catagory << " Quantity: " << book.quantity << " Tag number: " << book.tagnumber << '\n';
                    cout << "----------------------------------------------------------------------------\n";
                    isFound = true;
                    break;
                }
            }
            if (!isFound) {
                cout << "Book is not found!! \n";
            }
            cout << "Do you want to continue searching(y/n): \n";
            tocontinue = getch();
        } while (tolower(tocontinue) == 'y');
    }
    else if (choice == 2) {
        do {
            cin.ignore(100, '\n');
            string seachedMember;
            int id;
            bool isFound = false;
            if (library_members.empty()) {
                cout << "No transaction hisory found!!! \n";
                return;
            }
            cout << "Enter the members name you want to search for: ";
            getline(cin, seachedMember);
            cout << "Enter " << seachedMember << "'s id: ";
            cin >> id;

            for (const auto& member : library_members) {
                if (member.members_name == seachedMember && member.members_id == id) {
                    cout << "----------------------------------------------------------------------------\n";
                    cout << "Member's name: " << member.members_name << " Id: " << member.members_id << " Phone: " << member.phone_number << " Address: " << member.members_address << '\n';
                    cout << "----------------------------------------------------------------------------\n";
                    isFound = true;
                    break;
                }
            }
            if (!isFound) {
                cout << seachedMember << " is not a member!! \n";
            }
            cout << "Do you want to continue searching members(y/n): \n";
            tocontinue = getch();
        } while (tolower(tocontinue) == 'y');

    }


}
void borrow(vector<Book>& library_books, int totalbooks, vector<Transactions>& book_transactions, const vector<Members>& library_members, vector<History>& transaction_history) {

    char to_go_menu, tocontinue;
    cout << "Enter q to go back to the menu: \n";
    to_go_menu = getch();
    if (tolower(to_go_menu) == 'q') {
        return;
    }

    do {
        string bookName;
        cin.ignore(100, '\n');
        cout << "Enter the book name you want to borrow: ";
        getline(cin, bookName);

        Book* book_found = nullptr;
        for (auto& book : library_books) {
            if (book.name == bookName) {
                book_found = &book;
                break;
            }
        }

        if (book_found == nullptr) {
            cout << "Book not found!\n";
        }
        else if (book_found->quantity <= 0) {
            cout << "No more copies available.\n";
        }
        else {
            string borrowerName;
            int id;
            cout << "Enter your name: ";
            getline(cin, borrowerName);
            cout << "Enter your id: ";
            cin >> id;

            const Members* borrower = nullptr;
            for (const auto& member : library_members) {
                if (member.members_name == borrowerName && member.members_id == id) {
                    borrower = &member;
                    break;
                }
            }

            if (borrower == nullptr) {
                cout << "You are not a member. Please register first.\n";
            }
            else {
                bool isBorrower = false;
                for (const auto& transaction : book_transactions) {
                    if (transaction.members_name == borrowerName && transaction.book_title == bookName) {
                        cout << "You already borrowed a book. Please return that book first.\n";
                        isBorrower = true;
                        break;
                    }
                }

                if (!isBorrower) {
                    book_found->quantity--;

                    time_t now = time(nullptr);
                    tm today = *localtime(&now);
                    Date borrow_date, return_date;

                    borrow_date.day = today.tm_mday;
                    borrow_date.month = today.tm_mon + 1;
                    borrow_date.year = today.tm_year + 1900;

                    today.tm_mday += 21;
                    time_t after_21_days = mktime(&today);
                    tm returndate = *localtime(&after_21_days);
                    return_date.day = returndate.tm_mday;
                    return_date.month = returndate.tm_mon + 1;
                    return_date.year = returndate.tm_year + 1900;

                    char confirm;
                    cout << "Do you want to confirm the borrow(y/n): \n";
                    confirm = getch();
                    if (tolower(confirm) == 'y') {
                        transaction_history.emplace_back(borrower->members_name, book_found->name, borrow_date, return_date, "Borrowed");
                        book_transactions.emplace_back(borrower->members_name, borrower->members_id, borrower->phone_number, borrower->members_address, borrow_date, return_date, book_found->name, book_found->price);
                        cout << "----------------------------------------------------------------------------------------\n";
                        cout << "Dear " << borrower->members_name << ", you have successfully borrowed \"" << book_found->name << "\".\n";
                        cout << "Return date: " << return_date.day << "/" << return_date.month << "/" << return_date.year << " G.C.\n";
                        cout << "----------------------------------------------------------------------------------------\n";
                    }
                    else {
                        cout << "Unable to borrow a book. \n";
                    }
                }
            }
        }

        cout << "Do you want to continue borrowing (y/n): \n";
        tocontinue = getch();

    } while (tolower(tocontinue) == 'y');
}

void report(vector<Transactions> books_transactions, vector<Members>& library_members, int totalfees, int totalbooks, vector<History>& transaction_history, int totalmembers) {

    char to_go_menu;
    int choice;
    cout << "Enter q to go back to the menu: \n";
    to_go_menu = getch();
    if (tolower(to_go_menu) == 'q') {
        return;
    }

    cout << "--------------------------------------\n";
    cout << "1. All members details. \n";
    cout << "2. All borrowed books details.  \n";
    cout << "3. All transaction history \n";
    cout << "--------------------------------------\n";

    while (true) {
        cout << "Your choice: \n";
        cin >> choice;
        if (cin.fail() || cin.peek() != '\n' || choice < 1 || choice >3) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid input!! \n";
            cout << "Enter a valid choice. \n";
        }
        else {
            break;
        }
    }

    if (choice == 1) {

        if (library_members.size() != 0) {
            cout << "Total books added " << totalbooks << '\n';
            cout << "Total members " << totalmembers << '\n';
            cout << "Total fees paid " << totalfees << '\n';
            cout << "\t\t----------------------------------------------------------------------------\n";
            cout << "\t\t------------------------All member's details--------------------------------\n";
            for (const auto& member : library_members) {
                cout << "Member's name: " << member.members_name << "\t id: " << member.members_id << "\t phone number: " << member.phone_number << "\t address: " << member.members_address << '\n';
            }
            cout << "\t\t----------------------------------------------------------------------------\n";
        }
        else {
            cout << "No Members found!! \n";

        }

    }
    else if (choice == 2) {

        if (books_transactions.size() != 0) {
            cout << "Total books added " << totalbooks << '\n';
            cout << "Total members " << totalmembers << '\n';
            cout << "Total fees paid " << totalfees << '\n';
            cout << "\t\t----------------------------------------------------------------------------\n";
            cout << "\t\t--------------------------All Borrowed Books--------------------------------\n";
            for (const auto& transactions : books_transactions) {

                cout << "Borrwer's name: " << transactions.members_name << "\t id: " << transactions.members_id << "\t phone number: " << transactions.phone_number;
                cout << "\t Book title: " << transactions.book_title << "\t Borrow date: " << transactions.borrow_date.day << "/" << transactions.borrow_date.month << "/" << transactions.borrow_date.year << "\t Return date: " << transactions.return_date.day << "/" << transactions.return_date.month << "/" << transactions.return_date.year << '\n';
            }
            cout << "\t\t----------------------------------------------------------------------------\n";
        }
        else {
            cout << "No book transactions found!! \n";
        }
    }
    else if (choice == 3) {
        if (transaction_history.size() != 0) {
            cout << "Total books added " << totalbooks << '\n';
            cout << "Total fees paid " << totalfees << '\n';
            cout << "\t\t----------------------------------------------------------------------------\n";
            cout << "\t\t------------------------All transaction details-----------------------------\n";
            int i = 0;
            cout << "\t\t Member's name " << "\t\t" << "Book's title " << "\t" << "Borrow date " << "\t" << "Return date " << "\t" << "Status " << '\n';
            for (const auto& transaction : transaction_history) {
                i += 1;
                cout << "\t\t " << i << ". " << transaction.member_name << "\t\t" << transaction.book_name << "\t\t" << transaction.borrow_date.day << "/" << transaction.borrow_date.month << "/" << transaction.borrow_date.year << "\t\t" << transaction.return_date.day << "/" << transaction.return_date.month << "/" << transaction.return_date.year << "\t\t" << transaction.book_status << '\n';
            }
            cout << "\t\t----------------------------------------------------------------------------\n";
        }
        else {
            cout << "No transaction history found!! \n";

        }
    }

}

void returnBook(vector<Transactions>& book_transactions, vector<Book>& library_books, vector<History>& transaction_history) {

    char to_go_menu, tocontinue;
    bool isFound = false;
    cout << "Enter q to go back to the menu: \n";
    to_go_menu = getch();
    if (tolower(to_go_menu) == 'q') {
        return;
    }
    do {
        cin.ignore(100, '\n');
        string borrower_name, book_name;
        int id;
        cout << "Enter your name: ";
        getline(cin, borrower_name);
        cout << "Enter your id: ";
        cin >> id;
        cin.ignore();
        cout << "Enter the book name to return: ";
        getline(cin, book_name);

        auto to_be_returned = book_transactions.begin();
        while (to_be_returned != book_transactions.end()) {
            if (to_be_returned->members_name == borrower_name && to_be_returned->book_title == book_name && to_be_returned->members_id == id) {
                isFound = true;
                tm timeStruct = {};
                timeStruct.tm_mday = to_be_returned->return_date.day;
                timeStruct.tm_mon = to_be_returned->return_date.month - 1;
                timeStruct.tm_year = to_be_returned->return_date.year - 1900;
                time_t return_period = mktime(&timeStruct);
                time_t today = time(nullptr);

                double seconds_diff = difftime(return_period, today);
                int days_difference = static_cast<int>(seconds_diff / (60 * 60 * 24));
                if (days_difference < 0) {
                    cout << "Your passed the return date. so please pay your fee. \n";
                    break;
                }

                cout << "-----------------------------------------------------------------------------\n";
                cout << "Book \"" << to_be_returned->book_title << "\" returned successfully by " << to_be_returned->members_name << ".\n";
                cout << "-----------------------------------------------------------------------------\n";
                string returned_book_title = to_be_returned->book_title;
                transaction_history.emplace_back(to_be_returned->members_name, to_be_returned->book_title, to_be_returned->borrow_date, to_be_returned->return_date, "Returned");
                to_be_returned = book_transactions.erase(to_be_returned);
                for (auto& book : library_books) {
                    if (book.name == returned_book_title) {
                        ++book.quantity;
                        break;
                    }
                }

                break;
            }
            else {
                ++to_be_returned;
            }
        }
        if (!isFound) {
            cout << "No matching borrow record found.\n";
        }
        cout << "Do you want to continue returning books(y/n): \n";
        tocontinue = getch();
    } while (tolower(tocontinue) == 'y');
}

void calculateFees(vector<Transactions>& book_transactions, vector<Book>& library_books, int& totalfees, vector<History>& transaction_history) {
    string name, bookname;
    char to_go_menu, tocontinue;
    int choice, id;
    cout << "Enter q to go back to the menu: \n";
    to_go_menu = getch();
    if (tolower(to_go_menu) == 'q') {
        return;
    }

    cout << "--------------------------------------\n";
    cout << "1. Late book return. \n";
    cout << "2. For lost book. \n";
    cout << "3. To renew the return date. \n";
    cout << "--------------------------------------\n";

    while (true) {
        cout << "Your chocie: \n";
        cin >> choice;
        if (cin.fail() || cin.peek() != '\n' || !(choice >= 1 && choice <= 3)) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid input!! \n";
            cout << "Enter valid choice from the menu(1-3). \n";
        }
        else {
            break;
        }
    }

    if (choice == 1) {

        do {

            cin.ignore();
            cout << "Enter borrower's name: ";
            getline(cin, name);
            cout << "Enter your id: ";
            cin >> id;
            cin.ignore();
            cout << "Enter the book you borrowed: ";
            getline(cin, bookname);
            bool isFound = false;

            auto transaction = book_transactions.begin();
            while (transaction != book_transactions.end()) {
                if (transaction->members_name == name && transaction->book_title == bookname && transaction->members_id == id) {

                    isFound = true;
                    cout << "Borrowed: " << transaction->book_title << "\t Return Date: " << transaction->return_date.day << "/" << transaction->return_date.month << "/" << transaction->return_date.year << " G.C.\n";
                    tm timeStruct = {};
                    timeStruct.tm_mday = transaction->return_date.day;
                    timeStruct.tm_mon = transaction->return_date.month - 1;
                    timeStruct.tm_year = transaction->return_date.year - 1900;
                    timeStruct.tm_hour = 0;
                    timeStruct.tm_min = 0;
                    timeStruct.tm_sec = 0;
                    time_t late_return_time = mktime(&timeStruct);
                    time_t now = time(nullptr);
                    tm now_tm = *localtime(&now);
                    now_tm.tm_hour = 0;
                    now_tm.tm_min = 0;
                    now_tm.tm_sec = 0;
                    time_t today = mktime(&now_tm);

                    double seconds_diff = difftime(today, late_return_time);
                    int days_difference = static_cast<int>(seconds_diff / (60 * 60 * 24));
                    float fee;
                    if (days_difference >= 1) {
                        fee = days_difference * FEE_RATE;
                        cout << "Your fee is " << fixed << setprecision(2) << fee << " birr." << "\n";
                        totalfees += fee;

                    }
                    else {
                        cout << "You are still up for the return date.\n";
                        cout << "Please, you will not pay any fee.\n";
                    }

                    transaction_history.emplace_back(transaction->members_name, transaction->book_title, transaction->borrow_date, transaction->return_date, "Late Return");
                    transaction = book_transactions.erase(transaction);;
                    for (auto& book : library_books) {
                        if (transaction->book_title == book.name) {
                            ++book.quantity;
                        }
                    }
                    break;

                }
            }
            if (!isFound) {
                cout << "No active borrow found for this member.\n";
            }

            cout << "Do you want to continue calculate late book return fees. \n ";
            tocontinue = getch();
        } while (tolower(tocontinue) == 'y');

        return;

    }
    else if (choice == 2) {
        do {
            cin.ignore(100, '\n');
            cout << "Enter borrower's name: ";
            getline(cin, name);
            cout << "Enter borrower's id: ";
            cin >> id;
            cin.ignore();
            cout << "Enter the book borrowed: ";
            getline(cin, bookname);
            bool isFound = false;
            for (const auto& transaction : book_transactions) {
                if (transaction.members_name == name && transaction.book_title == bookname && transaction.members_id == id) {
                    isFound = true;
                    break;
                }
            }

            if (isFound) {
                auto lost_book = book_transactions.begin();
                while (lost_book != book_transactions.end()) {
                    if (lost_book->members_name == name && lost_book->book_title == bookname) {
                        cout << "----------------------------------------------\n";
                        cout << "You fee is " << lost_book->book_price << " Birr.  \n ";
                        cout << "----------------------------------------------\n";
                        totalfees += lost_book->book_price;
                        transaction_history.emplace_back(lost_book->members_name, lost_book->book_title, lost_book->borrow_date, lost_book->return_date, "Lost");
                        lost_book = book_transactions.erase(lost_book);
                    }
                    else {
                        ++lost_book;
                    }
                }
            }
        

            if (!isFound) {
                cout << "No active borrow found for this member.\n";
            }


            cout << "Do you want to continue calculating fees for lost books: \n";
            tocontinue = getch();
        } while (tolower(tocontinue) == 'y');
        return;
    }
    else if (choice == 3) {

        do {
            cin.ignore(100, '\n');
            cout << "Enter borrower's name: ";
            getline(cin, name);
            cout << "Enter borrower's id: ";
            cin >> id;
            cin.ignore();
            cout << "Enter the book you borrowed: ";
            getline(cin, bookname);
            bool isFound = false;

            for (auto& return_date_renewal : book_transactions) {
                if (return_date_renewal.members_name == name && return_date_renewal.book_title == bookname && return_date_renewal.members_id == id) {
                    isFound = true;
                    return_date_renewal.borrow_date.day = return_date_renewal.return_date.day;
                    return_date_renewal.borrow_date.month = return_date_renewal.return_date.month;
                    return_date_renewal.borrow_date.year = return_date_renewal.return_date.year;

                    tm timeStruct = {};
                    timeStruct.tm_mday = return_date_renewal.return_date.day;
                    timeStruct.tm_mon = return_date_renewal.return_date.month - 1;
                    timeStruct.tm_year = return_date_renewal.return_date.year - 1900;
                    tm old_return_date = timeStruct;
                    time_t old_return_date_time = mktime(&old_return_date);
                    tm today = *localtime(&old_return_date_time);
                    today.tm_mday += 21;
                    time_t after_21_days = mktime(&today);
                    tm new_return_date = *localtime(&after_21_days);
                    return_date_renewal.return_date.day = new_return_date.tm_mday;
                    return_date_renewal.return_date.month = new_return_date.tm_mon + 1;
                    return_date_renewal.return_date.year = new_return_date.tm_year + 1900;
                    transaction_history.emplace_back(return_date_renewal.members_name, return_date_renewal.book_title, return_date_renewal.borrow_date, return_date_renewal.return_date, "Renewed return date");
                    cout << "-----------------------------------------------\n";
                    cout << "Dear " << return_date_renewal.members_name << "\n";
                    cout << "Your new return date will be (dd/mm/yy) " << return_date_renewal.return_date.day << "/" << return_date_renewal.return_date.month << "/" << return_date_renewal.return_date.year << " G.C. \n";
                    cout << "-----------------------------------------------\n";
                    break;
                }
            }
            if (!isFound) {
                cout << "Borrow record is not found for this book.\n";
            }

            cout << "Do you want to continue renewing return dates: \n";
            tocontinue = getch();
        } while (tolower(tocontinue) == 'y');
    }
}

void saveBooksToFile(const vector<Book>& books) {
    ofstream outFile(BOOKS_FILE);
    if (!outFile.is_open()) {
        cout << "Unable to open books file for writing! \n";
        return;
    }
    for (const auto& book : books) {
        outFile << book.name << "\t" << book.author << "\t" << book.catagory << "\t" << book.quantity << "\t" << book.tagnumber << "\t" << book.price << "\n";
    }
    outFile.close();
}

void loadBooksFromFile(vector<Book>& books, int& totalbooks) {
    Book temp;
    string line;
    books.clear();
    ifstream inFile(BOOKS_FILE);
    if (!inFile.is_open() && books.empty()) {
        return;
    }
    else if (!inFile.is_open()) {
        cout << "Unable to open transactions file for reading! \n";
        return;
    }
    while (getline(inFile, temp.name, '\t')) {
        getline(inFile, temp.author, '\t');
        getline(inFile, temp.catagory, '\t');
        getline(inFile, line, '\t');
        temp.quantity = stoi(line);
        getline(inFile, line, '\t');
        temp.tagnumber = stoi(line);
        getline(inFile, line, '\n');
        temp.price = stod(line);
        books.push_back(temp);
        totalbooks++;
    }
    inFile.close();
}

void saveMembersToFile(const vector<Members>& members, int& library_members, int total_fees, int deleted_members) {
    ofstream outFile(MEMBERS_FILE);
    if (!outFile.is_open()) {
        cout << "Unable to open members file for writing! \n";
        return;
    }
    outFile << library_members << "\n";
    outFile << total_fees << "\n";
    outFile << deleted_members << "\n";
    for (const auto& member : members) {
        outFile << member.members_name << "\t" << member.members_id << "\t" << member.phone_number << "\t" << member.members_address << "\n";
    }
    outFile.close();
}

void loadMembersFromFile(vector<Members>& members, int& library_membres, int& total_fees, int& deleted_members) {
    ifstream inFile(MEMBERS_FILE);
    members.clear();
    if (!inFile.is_open() && members.empty()) {
        return;
    }
    else if (!inFile.is_open()) {
        cout << "Unable to open transactions file for reading! \n";
        return;
    }

    Members temp;
    string line;
    inFile >> library_membres;
    inFile >> total_fees;
    inFile >> deleted_members;
    inFile.ignore();
    while (getline(inFile, temp.members_name, '\t')) {
        getline(inFile, line, '\t');
        temp.members_id = stoi(line);
        getline(inFile, temp.phone_number, '\t');
        getline(inFile, temp.members_address);
        members.push_back(temp);
    }
    inFile.close();
}

void saveTransactionsToFile(const vector<Transactions>& transactions) {
    ofstream outFile(TRANSACTIONS_FILE);
    if (!outFile.is_open()) {
        cout << "Unable to open transactions file for writing! \n";
        return;
    }

    for (const auto& T : transactions) {
        outFile << T.members_name << "\t" << T.members_id << "\t" << T.phone_number << "\t" << T.book_title << "\t" << T.borrow_date.day << "\t" << T.borrow_date.month << "\t" << T.borrow_date.year << "\t" << T.return_date.day << "\t" << T.return_date.month << "\t" << T.return_date.year << "\t" << T.members_address << "\n";
    }
    outFile.close();
}

void loadTransactionsFromFile(vector<Transactions>& transactions) {
    ifstream inFile(TRANSACTIONS_FILE);
    transactions.clear();
    if (!inFile.is_open() && transactions.empty()) {
        return;
    }
    else if (!inFile.is_open()) {
        cout << "Unable to open transactions file for reading! \n";
        return;
    }

    Transactions temp;
    string line;

    while (getline(inFile, temp.members_name, '\t')) {

        getline(inFile, line, '\t');
        temp.members_id = stoi(line);
        getline(inFile, temp.phone_number, '\t');
        getline(inFile, temp.book_title, '\t');
        getline(inFile, line, '\t');

        temp.borrow_date.day = stoi(line);
        getline(inFile, line, '\t');
        temp.borrow_date.month = stoi(line);
        getline(inFile, line, '\t');
        temp.borrow_date.year = stoi(line);

        getline(inFile, line, '\t');
        temp.return_date.day = stoi(line);
        getline(inFile, line, '\t');
        temp.return_date.month = stoi(line);
        getline(inFile, line, '\t');
        temp.return_date.year = stoi(line);

        getline(inFile, temp.members_address);

        transactions.push_back(temp);
    }
    inFile.close();
}
void saveTransactionHistoryToFile(const vector<History>& transaction_history) {
    ofstream outFile(HISTORY_FILE);
    if (!outFile.is_open()) {
        cout << "Unable to open transactions file for writing! \n";
        return;
    }
    for (const auto& T : transaction_history) {
        outFile << T.member_name << "\t" << T.book_name << "\t" << T.borrow_date.day << "\t" << T.borrow_date.month << "\t" << T.borrow_date.year << "\t" << T.return_date.day << "\t" << T.return_date.month << "\t" << T.return_date.year << "\t" << T.book_status << "\n";
    }
    outFile.close();
}
void loadTransactionHistoryFromFile(vector<History>& transaction_history) {

    ifstream inFile(HISTORY_FILE);
    transaction_history.clear();
    if (!inFile.is_open() && transaction_history.empty()) {
        return;
    }
    else if (!inFile.is_open()) {
        cout << "Unable to open transaction history file for reading! \n";
        return;
    }

    History temp;
    string line;

    while (getline(inFile, temp.member_name, '\t')) {

        getline(inFile, temp.book_name, '\t');
        getline(inFile, line, '\t');
        temp.borrow_date.day = stoi(line);
        getline(inFile, line, '\t');
        temp.borrow_date.month = stoi(line);
        getline(inFile, line, '\t');
        temp.borrow_date.year = stoi(line);

        getline(inFile, line, '\t');
        temp.return_date.day = stoi(line);
        getline(inFile, line, '\t');
        temp.return_date.month = stoi(line);
        getline(inFile, line, '\t');
        temp.return_date.year = stoi(line);

        getline(inFile, temp.book_status);

        transaction_history.push_back(temp);
    }

    inFile.close();
}