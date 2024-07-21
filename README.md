LİBRARY MANAGEMENT TOOL

This system, developed using the C programming language, is aimed at efficiently managing various aspects of library operations such as book inventory, user records, and the borrowing/returning process.

Our system addresses several key functionalities necessary for daily library management, including:

Book Management: Adding new books to the library’s collection, removing books that are no longer needed, and listing all books currently available.

Borrowing and Returning Books: Handling the process of borrowing books, including updating stock and calculating return dates. It also manages the return process, including handling overdue books and calculating any applicable fees.

User Management: Maintaining user records, allowing for the addition, modification, and deletion of user information.

The system uses file-based storage to keep track of books and user records, ensuring that data remains persistent between sessions. It is designed to be straightforward and efficient, making it suitable for small to medium-sized libraries or as a prototype for larger systems. Each function is designed to address a specific aspect of library management, providing a complete overview of how the system handles different tasks.We will also include examples of the system's outputs to demonstrate how these functions work in practice, providing a clear picture of how the system performs its operations. Whether you're a library administrator looking for a robust tool or a student studying library management systems, this guide will help you understand the functionality and application of our system.

FUNCTIONS AND PURPOSES


-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

|Function	                                                  Description	                                                                                 Example Output

|add_book	                                                  Adds a new book to the library’s inventory.	                                                 "Book information saved successfully!"

|delete_book	                                              Deletes a book from the library’s inventory based on its barcode.                            "Book deleted successfully!"

|list_books	                                                Lists all books currently in the library’s inventory.	                                       "List of all books printed."

|borrow_book	                                              Handles the borrowing process, updates book stock, and records borrowing details.            "Borrowing process complete. Return by 04/08/24."

|return_book	                                              Processes the return of a borrowed book, updates stock, and calculates any delay fees.	     "Return process successful. Amount due: 0"

|list_borrowed_books                                       	Lists all borrowed books with their details such as date of issue and return date.	         "List of borrowed books printed."

|delete_user                                               	Deletes a user from the system based on their ID.	                                           "User deletion succeeded.


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
