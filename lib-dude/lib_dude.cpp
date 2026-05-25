#include <iostream>
#include <mysql/mysql.h>
#include <string>
#include <iomanip>

using namespace std;

MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

void connectDB() {
    conn = mysql_init(0);
    // Updated database name to libdude_db
    conn = mysql_real_connect(conn, "localhost", "root", "your_password", "libdude_db", 0, NULL, 0);
    if (!conn) {
        cout << "\n[-] Database Connection Failed: " << mysql_error(conn) << endl;
        exit(1);
    }
}

void addBook() {
    string title, author;
    int copies;
    cout << "\n--- Add New Book ---" << endl;
    cout << "Enter Book Title: ";
    cin.ignore(); getline(cin, title);
    cout << "Enter Author Name: "; getline(cin, author);
    cout << "Enter Total Copies: "; cin >> copies;

    string query = "INSERT INTO Books (title, author, total_copies, available_copies) VALUES ('" 
                   + title + "', '" + author + "', " + to_string(copies) + ", " + to_string(copies) + ")";
                   
    if (mysql_query(conn, query.c_str()) == 0) cout << "[+] Book Added Successfully to Lib-Dude!" << endl;
    else cout << "[-] Error: " << mysql_error(conn) << endl;
}

void viewBooks() {
    string query = "SELECT * FROM Books";
    if (mysql_query(conn, query.c_str()) == 0) {
        res = mysql_store_result(conn);
        cout << "\n----------------------------------------------------------------------" << endl;
        cout << left << setw(5) << "ID" << setw(35) << "Title" << setw(20) << "Author" << setw(10) << "Available" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(5) << row[0] << setw(35) << row[1] << setw(20) << row[2] << setw(10) << row[4] << endl;
        }
        cout << "----------------------------------------------------------------------" << endl;
        mysql_free_result(res);
    } else cout << "[-] Error: " << mysql_error(conn) << endl;
}

void issueBook() {
    string roll_no; int book_id;
    cout << "\n--- Issue Book ---" << endl;
    cout << "Enter Student Roll No: "; cin >> roll_no;
    cout << "Enter Book ID: "; cin >> book_id;

    string checkQuery = "SELECT available_copies FROM Books WHERE book_id = " + to_string(book_id);
    if (mysql_query(conn, checkQuery.c_str()) == 0) {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        if (row && stoi(row[0]) > 0) {
            mysql_free_result(res);
            string updateQuery = "UPDATE Books SET available_copies = available_copies - 1 WHERE book_id = " + to_string(book_id);
            string insertQuery = "INSERT INTO Issue_Returns (book_id, roll_no, issue_date) VALUES (" + to_string(book_id) + ", '" + roll_no + "', CURDATE())";
            if (mysql_query(conn, updateQuery.c_str()) == 0 && mysql_query(conn, insertQuery.c_str()) == 0) {
                cout << "[+] Success: Book ID " << book_id << " issued to " << roll_no << "!" << endl;
            }
        } else {
            if (res) mysql_free_result(res);
            cout << "[-] Book is Out of Stock or Invalid ID." << endl;
        }
    }
}

void returnBook() {
    string roll_no; int book_id;
    cout << "\n--- Return Book ---" << endl;
    cout << "Enter Student Roll No: "; cin >> roll_no;
    cout << "Enter Book ID: "; cin >> book_id;

    string checkQuery = "SELECT transaction_id FROM Issue_Returns WHERE book_id = " + to_string(book_id) + " AND roll_no = '" + roll_no + "' AND status = 'ISSUED'";
    if (mysql_query(conn, checkQuery.c_str()) == 0) {
        res = mysql_store_result(conn);
        if (mysql_fetch_row(res)) {
            mysql_free_result(res);
            string updateBook = "UPDATE Books SET available_copies = available_copies + 1 WHERE book_id = " + to_string(book_id);
            string updateTxn = "UPDATE Issue_Returns SET status = 'RETURNED', return_date = CURDATE() WHERE book_id = " + to_string(book_id) + " AND roll_no = '" + roll_no + "' AND status = 'ISSUED'";
            if (mysql_query(conn, updateBook.c_str()) == 0 && mysql_query(conn, updateTxn.c_str()) == 0) {
                cout << "[+] Success: Book ID " << book_id << " returned by " << roll_no << "!" << endl;
            }
        } else {
            cout << "[-] No active issue record found for this Student and Book." << endl;
        }
    }
}

int main() {
    connectDB();
    int choice;
    while (true) {
        cout << "\n=========================================" << endl;
        cout << "   LIB-DUDE: KIT LIBRARY MANAGER   " << endl;
        cout << "=========================================" << endl;
        cout << "1. Add a New Book\n2. View All Books\n3. Issue a Book\n4. Return a Book\n5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: issueBook(); break;
            case 4: returnBook(); break;
            case 5: mysql_close(conn); return 0;
            default: cout << "Invalid choice!" << endl;
        }
    }
}
