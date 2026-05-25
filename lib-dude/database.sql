CREATE DATABASE IF NOT EXISTS libdude_db;
USE libdude_db;

CREATE TABLE IF NOT EXISTS Books (
    book_id INT PRIMARY KEY AUTO_INCREMENT,
    title VARCHAR(100) NOT NULL,
    author VARCHAR(100),
    total_copies INT,
    available_copies INT
);

CREATE TABLE IF NOT EXISTS Students (
    roll_no VARCHAR(20) PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    course VARCHAR(20)
);

CREATE TABLE IF NOT EXISTS Issue_Returns (
    transaction_id INT PRIMARY KEY AUTO_INCREMENT,
    book_id INT,
    roll_no VARCHAR(20),
    issue_date DATE,
    return_date DATE NULL,
    status VARCHAR(10) DEFAULT 'ISSUED',
    FOREIGN KEY (book_id) REFERENCES Books(book_id),
    FOREIGN KEY (roll_no) REFERENCES Students(roll_no)
);

-- Initial Dummy Data for Testing
INSERT INTO Books (title, author, total_copies, available_copies) VALUES ('Let Us C', 'Yashavant Kanetkar', 5, 5);
INSERT INTO Students (roll_no, name, course) VALUES ('BCA101', 'Adarsh', 'BCA');
