# Lib-Dude 📚

**Lib-Dude** is a fast, console-based offline Library Management System built using **C++** and **MySQL**. It is designed to efficiently manage book inventories, student records, and issue/return logs for academic institutions like KIT Mirzamurad.

## 🚀 Features
* **C++ & MySQL Integration:** Utilizes the MySQL C-API for seamless and secure database transactions.
* **Inventory Management:** Add new books and monitor currently available stock in real-time.
* **Transaction Tracking:** Automatically handles the logic for issuing books (decreases stock) and processing returns (increases stock).

## 🛠️ Prerequisites
* G++ Compiler
* MySQL Server
* MySQL C-Client Library (`libmysqlclient-dev`)

## ⚙️ Setup & Installation

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/adarsh-bro/lib-dude.git](https://github.com/adarsh-bro/lib-dude.git)
   cd lib-dude

2. **Configure the Database**

   Import the provided database.sql file into your MySQL server to generate the required libdude_db database and tables.

   ```bash
   mysql -u root -p < database.sql


4. **Compile the Source Code**
   
Compile the C++ file and link the MySQL client library:

g++ lib_dude.cpp -o lib_dude -lmysqlclient
    

5. **Run the Application**

./lib_dude


## 📄 License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

  
