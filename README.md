LİBRARY MANAGEMENT TOOL

This system, developed using the C programming language, is aimed at efficiently managing various aspects of library operations such as book inventory, user records, and the borrowing/returning process.

Our system addresses several key functionalities necessary for daily library management, including:

Book Management: Adding new books to the library’s collection, removing books that are no longer needed, and listing all books currently available.

Borrowing and Returning Books: Handling the process of borrowing books, including updating stock and calculating return dates. It also manages the return process, including handling overdue books and calculating any applicable fees.

User Management: Maintaining user records, allowing for the addition, modification, and deletion of user information.

The system uses file-based storage to keep track of books and user records, ensuring that data remains persistent between sessions. It is designed to be straightforward and efficient, making it suitable for small to medium-sized libraries or as a prototype for larger systems. Each function is designed to address a specific aspect of library management, providing a complete overview of how the system handles different tasks.We will also include examples of the system's outputs to demonstrate how these functions work in practice, providing a clear picture of how the system performs its operations. Whether you're a library administrator looking for a robust tool or a student studying library management systems, this guide will help you understand the functionality and application of our system.

Function Explanations

1. add_book
2. Purpose: Adds a new book to the library’s inventory.

How It Works:

Prompts the user to enter details like barcode, book name, author, sort, and stock.
Validates the input.
Writes the new book record to the file.

2. delete_book
Purpose: Removes a book from the inventory based on its barcode.

How It Works:

Reads the book records from the file.
Creates a new file excluding the book to be deleted.
Replaces the old file with the new one.

3. borrow_book
Purpose: Handles the borrowing process, updates book stock, and records borrowing details.

How It Works:

Prompts the user to enter the date of issue.
Calculates the mandatory return date (14 days later).
Updates the book’s stock and records the borrowing details.

4. return_book
Purpose: Processes the return of a borrowed book, updates stock, and calculates any delay fees.

How It Works:

Prompts the user to enter the book’s barcode.
Updates the stock and calculates delay fees.
Removes the record from the borrowing file.

5. delete_user
Purpose: Deletes a user from the system based on their ID.

How It Works:

Reads user records from the file.
Creates a new file excluding the user to be deleted.
Replaces the old file with the new one.

6.Listing Function
Purpose: Lists what you want to list: books, borrowed books, users.

How It Works:

Reads Records from the File: Opens the respective data file (e.g., book.dat, oduncKitap_kayitlari.dat, or user.dat) in read mode.

Prints Details: Iterates through the file records, printing out details such as barcode, book name, author, and stock for books; borrowing details like barcode, issue date, return date, delay, and amount due for borrowed books; and user details such as ID, name, and contact information for users.

Handles Errors: Checks for file reading errors and handles them appropriately by displaying an error message if necessary.
