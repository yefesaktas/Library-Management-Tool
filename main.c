#include "Library.h"
#include "Struct.h"
#include "Prototype.h"

int main(void) {
    display_main_menu();
    return 0;
}
int check_mail(char *mail) {
    //strstr checks the given array if it has what you want
    if(strstr(mail,"@gmail.com")!=NULL) {
        return 1;
    }
    return 0;
}
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void fill_date(struct tm *date, int year, int month, int day) {
    date->tm_year = year - 1900; // tm_year is years since 1900
    date->tm_mon = month - 1;    // tm_mon is months since January (0-11)
    date->tm_mday = day;
    date->tm_hour = 0;
    date->tm_min = 0;
    date->tm_sec = 0;
    date->tm_isdst = -1;         // Let mktime determine if DST is in effect
}

void display_main_menu() {
    while (1) {
        int choice;
        printf("\n==== MAIN MENU ====\n");
        printf("    1. Personal Menu\n");
        printf("    2. User Menu\n");
        printf("    0. Exit\n");
        printf("    Please enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            perror("Error reading input. Please enter a valid number.");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        switch (choice) {
            case 1:
                personal_menu();
                break;
            case 2:
                user_menu();
                break;
            case 0:
                printf("Exiting the program...\n");
                return;
            case 5:
                fill_file();
                clear_input_buffer();
                break;
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    }
}

void personal_menu() {
    while (1) {
        int choice;
        printf("\n==== PERSONAL MENU ====\n");
        if(sign_in_personal()!=1) {
            return;
        }
        printf("    1. Personal Registration\n");
        printf("    2. User Management\n");
        printf("    3. Book Management\n");
        printf("    4. Borrowing Management\n");
        printf("    0. Return to Main Menu\n");
        printf("    Please enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            perror("Error reading input. Please enter a valid number.");
            clear_input_buffer();
            continue;
        }

        switch (choice) {
            case 1:
                personal_registration();
                break;
            case 2:
                manage_users();
                break;
            case 3:
                book_menu();
                break;
            case 4:
                borrow_menu();
                break;
            case 0:
                printf("Returning to Main Menu...\n");
                return;
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    }
}
int sign_in_personal() {
    char id[12];
    int flag = 0;
    FILE *personal = fopen("personal.dat", "rb");
    s_personal fpersonal;
    if (personal == NULL) {
        perror("Error opening file");
        return 0;
    }
    printf("\tPLEASE ENTER YOUR ID\n");
    if (fgets(id, sizeof(id), stdin) == NULL) {
        perror("\tError reading ID.\n");
        fclose(personal);
        return 0;
    }
    id[strcspn(id, "\n")] = '\0';
    while (fread(&fpersonal, sizeof(s_personal), 1, personal) == 1) {// dosya sonu kontrolü
        if (strcmp(id, fpersonal.id) == 0) {
            printf("\tPERSONAL SIGN HAS SUCCEEDED %s\n", fpersonal.name);
            flag = 1;
            fclose(personal);
            break;
        }
    }
    fclose(personal);
    if (flag == 0) {
        printf("\tID VERIFICATION HAS JUST FAILED\n");
        return 0;
    }
    return 1;
}
void personal_registration() {
    printf("\n==== PERSONAL REGISTRATION ====\n");
    printf("    Please enter the required personal information to register.\n");
    FILE *rpersonal = fopen("personal.dat", "ab");
    s_personal fs_personal;
    if (rpersonal == NULL) {
        perror("Error opening file");
        return ;
    }
    printf("\tID MAX 11 CHARACTERS: \n");
    if (scanf("%11s", fs_personal.id) == 1) {
        clear_input_buffer();
        printf("\tName (max 19 characters): \n");
        if (fgets(fs_personal.name, sizeof(fs_personal.name), stdin) != NULL) {
            fs_personal.name[strcspn(fs_personal.name, "\n")] = '\0';
            if (strlen(fs_personal.id) == 11 && strlen(fs_personal.name) > 0) {
                if(fwrite(&fs_personal, sizeof(s_personal), 1, rpersonal)==1) {
                    printf("\tPERSONAL REGISTRATION SUCCESSFUL \n");
                }
                else {
                    perror("ERROR WRITING IN THE FILE");//prefixed printing
                }
            }
            else {
                perror("ID or Name length is incorrect.");}}
        else {
            perror("Error reading name.");}}
    else {
        perror("Error reading ID.");}
    fclose(rpersonal);
}

void manage_users() {
    while (1) {
        int choice;
        printf("\n==== USER MANAGEMENT MENU ====\n");
        printf("    1. Register New User\n");
        printf("    2. Delete Existing User\n");
        printf("    3. List All Users\n");
        printf("    0. Return to Personal Menu\n");
        printf("    Please enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            perror("Error reading input. Please enter a valid number.");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        switch (choice) {
            case 1:
                register_user();
                break;
            case 2:
                delete_user();
                break;
            case 3:
                list_users();
                break;
            case 0:
                printf("Returning to Personal Menu...\n");
                return;
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    }
}
void register_user() {
    printf("\n==== REGISTER NEW USER ====\n");
    printf("    Please enter the required information to register a new user.\n");
    FILE *f_memberList = fopen("user.dat", "ab");
    if (f_memberList == NULL) {
        perror("Error opening file");
        return;
    }
    member_struct new_member;
    int input_control_flag = 0;
    printf("\n==== ADD A NEW MEMBER ====\n");
    // Turkish ID number
    printf("\n%d\n",input_control_flag);
    printf("    Enter the member's Turkish ID number (11 digits): ");
    if (scanf("%11s", new_member.m_id) != 1 || strlen(new_member.m_id) != 11) {
        clear_input_buffer();
        input_control_flag = 1;
    }else if (strcmp("exit", new_member.m_id) == 0) {
        fclose(f_memberList);
        return;
    }
    clear_input_buffer();
    // Name and Surname
    printf("\n%d\n",input_control_flag);
    printf("\n    Enter the member's name and surname: ");
    if (fgets(new_member.m_name_surname, sizeof(new_member.m_name_surname), stdin) != NULL) {
        new_member.m_name_surname[strcspn(new_member.m_name_surname, "\n")] = '\0';
        if (strcmp("exit", new_member.m_name_surname) == 0) {
            fclose(f_memberList);
            return;
        }
        if (strlen(new_member.m_name_surname) == 0) {
            input_control_flag = 1;
        }
    } else {
        input_control_flag = 1;
    }
    // Gender
    printf("\n%d\n",input_control_flag);
    printf("\n    Enter the member's gender (M/F): ");
    scanf("%c", &new_member.m_gender);
    if (new_member.m_gender!='M'&&new_member.m_gender!='m'&&new_member.m_gender!='F'&&new_member.m_gender!='f') {
        clear_input_buffer();
        input_control_flag = 1;
    }
    // Date of Birth
    printf("\n%d\n",input_control_flag);
    printf("\n    Enter the member's date of birth (DDMMYYYY): ");
    if (scanf("%8s", new_member.m_dateOFbirth) != 1 || strlen(new_member.m_dateOFbirth) != 8) {
        clear_input_buffer();
        input_control_flag = 1;
    }else if (strcmp("exit", new_member.m_dateOFbirth) == 0) {
        fclose(f_memberList);
        return;
    }
    // Phone Number
    printf("\n%d\n",input_control_flag);
    printf("\n    Enter the member's phone number (05XXXXXXXXX): ");
    if (scanf("%11s", new_member.m_tel) != 1 || strlen(new_member.m_tel) != 11) {
        clear_input_buffer();
        input_control_flag = 1;
    }else if (strcmp("exit", new_member.m_tel) == 0) {
        fclose(f_memberList);
        return;
    }
    // Email Address
    printf("\n%d\n",input_control_flag);
    printf("\n    Enter the member's email address: ");
    if (scanf("%50s", new_member.m_epost) != 1||check_mail(new_member.m_epost)!=1) {
        clear_input_buffer();
        input_control_flag = 1;
    }else if (strcmp("exit", new_member.m_epost) == 0) {
        fclose(f_memberList);
        return;
    }
    // Membership Date
    printf("\n%d\n",input_control_flag);
    printf("\n    Enter the membership date (DDMMYYYY): ");
    if (scanf("%8s", new_member.m_dateOFreg) != 1 || strlen(new_member.m_dateOFreg) != 8) {
        clear_input_buffer();
        input_control_flag = 1;
    }else if (strcmp("exit", new_member.m_dateOFreg) == 0) {
        fclose(f_memberList);
        return;
    }
    clear_input_buffer();
    // Address
    printf("\n%d\n",input_control_flag);
    printf("\n    Enter the member's address: ");
    if (fgets(new_member.m_address, sizeof(new_member.m_address), stdin) != NULL) {
        new_member.m_address[strcspn(new_member.m_address, "\n")] = '\0';
        if (strcmp("exit", new_member.m_address) == 0) {
            fclose(f_memberList);
            return;
        }
        if (strlen(new_member.m_address) == 0) {
            input_control_flag = 1;
        }
    } else {
        clear_input_buffer();
        input_control_flag = 1;
    }
    printf("\n%d\n",input_control_flag);
    if(input_control_flag==0) {
        printf("\nYou have entered the following information:\n");
        printf("    ID: %s\n", new_member.m_id);
        printf("    Name and Surname: %s\n", new_member.m_name_surname);
        printf("    Gender: %c\n", new_member.m_gender);
        printf("    Date of Birth: %s\n", new_member.m_dateOFbirth);
        printf("    Phone Number: %s\n", new_member.m_tel);
        printf("    Email: %s\n", new_member.m_epost);
        printf("    Registration Date: %s\n", new_member.m_dateOFreg);
        printf("    Address: %s\n", new_member.m_address);
        printf("    Is the above information correct? (yes/no): ");
        char choice[5];
        scanf("%4s", choice);
        if (strcmp(choice, "yes") != 0) {
            printf("    Let's try again.\n");
            fclose(f_memberList);
            return;
        }
        // Save to file
        if (fwrite(&new_member, sizeof(member_struct), 1, f_memberList) == 1) {
            printf("\n    Member addition successful.\n");
        } else {
            perror("An error occurred while saving the member data.");
        }
    }
    else {
        perror("    Error saving book information");
    }
    fclose(f_memberList);
}
void delete_user() {
    printf("\n==== DELETE EXISTING USER ====\n");
    printf("    Please enter the user ID of the user you want to delete.\n");
    FILE *fuse = fopen("user.dat", "rb");
    FILE *fuse_new = fopen("usernew.dat", "wb");
    if (fuse == NULL || fuse_new == NULL) {
        perror("Error opening file");
        if (fuse != NULL) fclose(fuse);
        if (fuse_new != NULL) fclose(fuse_new);
        return;
    }
    char idd[12];
    printf("Enter the ID of the user to delete: ");
    if (scanf("%11s", idd) != 1) {
        perror("Error reading input");
        fclose(fuse);
        fclose(fuse_new);
        return;
    }
    member_struct member;
    int deleted = 0;
    while (fread(&member, sizeof(member_struct), 1, fuse) == 1) {
        if (strcmp(member.m_id, idd) != 0) {
            if (fwrite(&member, sizeof(member_struct), 1, fuse_new) != 1) {
                perror("Error writing to new file");
                fclose(fuse);
                fclose(fuse_new);
                return;
            }
        } else {
            deleted = 1;
        }
    }
    fclose(fuse);
    fclose(fuse_new);
    if (deleted) {
        if (remove("user.dat") != 0) {
            perror("Error removing original file");
        }
        if (rename("usernew.dat", "user.dat") != 0) {
            perror("Error renaming new file");
        }
        printf("\nUser deletion succeeded.\n");
    } else {
        printf("\nNo user found with ID '%s'. No changes made.\n", idd);
    }
}
void list_users() {
    FILE *f_memberList = fopen("user.dat", "rb");
    if (f_memberList == NULL) {
        perror("Error opening file");
        return;
    }
    member_struct member;
    int member_count = 0;
    size_t result;
    printf("\n==== LIST OF MEMBERS ====\n");
    while ((result = fread(&member, sizeof(member_struct), 1, f_memberList)) == 1) {
        member_count++;
        printf("\nMember #%d:\n", member_count);
        printf("    ID: %s\n", member.m_id);
        printf("    Name and Surname: %s\n", member.m_name_surname);
        printf("    Gender: %c\n", member.m_gender);
        printf("    Date of Birth: %s\n", member.m_dateOFbirth);
        printf("    Phone Number: %s\n", member.m_tel);
        printf("    Email: %s\n", member.m_epost);
        printf("    Registration Date: %s\n", member.m_dateOFreg);
        printf("    Address: %s\n", member.m_address);
    }
    if (result != 0 && ferror(f_memberList)) {
        perror("Error reading from file");
    } else if (member_count == 0) {
        printf("\nNo members found.\n");
    }
    fclose(f_memberList);
}
void user_menu() {
    while (1) {
        int choice;
        printf("\n==== USER MENU ====\n");
        printf("    1. New User Registration\n");
        printf("    2. User Sign In\n");
        printf("    0. Return to Main Menu\n");
        printf("    Please enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            perror("Error reading input. Please enter a valid number.");
            clear_input_buffer();
            continue;
        }

        switch (choice) {
            case 1:
                register_user();
                break;
            case 2:
                sign_in_user();
                break;
            case 0:
                printf("Returning to Main Menu...\n");
                return;
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    }
}

void sign_in_user() {
    while (1) {
        int choice;
        printf("\n==== USER SIGN IN MENU ====\n");
        if(Is_member()!=1) {
            perror("User sign has failed");
            return;
        }
        printf("    1. Borrow a Book\n");
        printf("    2. Return a Book\n");
        printf("    3. Exit\n");
        printf("    Please enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            perror("Error reading input. Please enter a valid number.");
            clear_input_buffer();
            continue;
        }

        switch (choice) {
            case 1:
                borrow_book();
                break;
            case 2:
                return_book();
                break;
            case 3:
                printf("Exiting Sign In Menu...\n");
                return;
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    }
}
int Is_member() { // (EXISTS -> 1 / NOT EXISTS -> 0)
    FILE *member_file = fopen("user.dat", "rb");
    if (member_file == NULL) {
        perror("Error opening file");
        return 0;
    }
    char member_id[12];
    printf("Enter member ID: ");
    if (scanf("%11s", member_id) != 1) {
        printf("Error reading member ID.\n");
        clear_input_buffer();
        fclose(member_file);
        return 0;
    }
    clear_input_buffer(); // Clear any extra input
    member_struct mem;
    size_t result;
    while ((result = fread(&mem, sizeof(member_struct), 1, member_file)) == 1) {
        if (strcmp(mem.m_id, member_id) == 0) {
            fclose(member_file);
            return 1;
        }
    }
    if (result != 0 && ferror(member_file)) {
        perror("Error reading from file");
    }
    fclose(member_file);
    return 0;
}

void book_menu() {
    while (1) {
        int choice;
        printf("\n==== BOOK MENU ====\n");
        printf("    1. Add a New Book\n");
        printf("    2. Delete an Existing Book\n");
        printf("    3. List All Books\n");
        printf("    0. Return to Personal Menu\n");
        printf("    Please enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            perror("Error reading input. Please enter a valid number.");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        switch (choice) {
            case 1:
                add_book();
                break;
            case 2:
                delete_book();
                break;
            case 3:
                list_books();
                break;
            case 0:
                printf("Returning to Personal Menu...\n");
                return;
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    }
}

void add_book() {
    printf("\n==== ADD A NEW BOOK ====\n");
    printf("    Please enter the required information to add a new book.\n");
    FILE *fbook = fopen("book.dat", "ab");
    if (fbook == NULL) {
        perror("Error opening file");
        fclose(fbook);
        return;
    }
    char choice[5];
    book f_book;
    while (1) {
        int flag = 0;
        int count=0;
        printf("    BARCODE (10 characters): ");
        printf("\n%d\n",flag);
        if (fgets(f_book.barcode, sizeof(f_book.barcode), stdin) != NULL&&strcmp("\n", f_book.barcode)!=0) {
            f_book.barcode[strcspn(f_book.barcode, "\n")] = '\0';
            if (strlen(f_book.barcode) != 10) {
                flag = 1;
                //clear_input_buffer();
            }
            if (strlen(f_book.barcode) > 10) {
                perror("BUFFER OVERFLOW");
                break;
            }
            if(strcmp("exit", f_book.barcode) == 0) {
                break;
            }}else{
            clear_input_buffer();
            flag = 1;}
        clear_input_buffer();
        printf("    BOOK NAME: ");
        printf("\n%d\n",flag);

        if(fgets(f_book.b_name,sizeof(f_book.b_name),stdin) != NULL&&strcmp("\n", f_book.b_name)!=0) {
            f_book.b_name[strcspn(f_book.b_name,"\n")]='\0';
            if(strcmp("exit", f_book.b_name) == 0) {
                break;}}
        else{
            clear_input_buffer();
            flag = 1;}

        printf("\n%d\n",flag);
        printf("    AUTHOR: ");

        if(fgets(f_book.author,sizeof(f_book.author),stdin) != NULL&&strcmp("\n", f_book.author)!=0) {
            f_book.author[strcspn(f_book.author,"\n")]='\0';
            if (strcmp("exit", f_book.author) == 0) {
                break;
            }}else {
            clear_input_buffer();
            flag = 1;
        }
        printf("    SORT: ");

        if (fgets(f_book.b_kind,sizeof(f_book.b_kind),stdin) != NULL&&strcmp("\n", f_book.b_kind)!=0) {
            f_book.b_kind[strcspn(f_book.b_kind,"\n")]='\0';
            if (strcmp("exit", f_book.b_kind) == 0) {
                break;
            }}else {
            clear_input_buffer();
            flag = 1;
        }
        printf("    STOCK: ");

        if (scanf("%d", &f_book.b_stock) != 1) {
            clear_input_buffer();
            flag = 1;
        }
        if (flag == 1) {
            printf("    The information you have entered is not correct. Please try again or type 'exit' to quit.\n");
            clear_input_buffer();
        } else {
            printf("\n    You have entered the following information:\n");
            printf("    BARCODE: %s\n", f_book.barcode);
            printf("    BOOK NAME: %s\n", f_book.b_name);
            printf("    AUTHOR: %s\n", f_book.author);
            printf("    SORT: %s\n", f_book.b_kind);
            printf("    STOCK: %d\n", f_book.b_stock);
            printf("    Is the above information correct? (yes/no): ");
            scanf("%4s", choice);
            if (strcmp(choice, "yes") != 0) {
                clear_input_buffer();
                printf("    Let's try again.\n");
                continue;
            }
            if (fwrite(&f_book, sizeof(book), 1, fbook) == 1) {
                printf("    Book information saved successfully!\n");
            } else {
                perror("    Error saving book information");
            }
            fclose(fbook);
            break;
        }
    }
}
void delete_book() {
    printf("\n==== DELETE AN EXISTING BOOK ====\n");
    printf("    Please enter the book barcode of the book you want to delete.\n");
    FILE *fbook = fopen("book.dat", "rb");
    FILE *fbook_new = fopen("booknew.dat", "wb");
    if (fbook == NULL || fbook_new == NULL) {
        perror("Error opening file");
        if (fbook != NULL) fclose(fbook);
        if (fbook_new != NULL) fclose(fbook_new);
        return;
    }
    book f_book;
    char idd[11];
    printf("\nEnter the barcode of the book you want to delete: ");
    if (scanf("%10s", idd) != 1) {
        printf("\tError reading barcode.\n");
        clear_input_buffer();
        fclose(fbook);
        fclose(fbook_new);
        return;
    }
    clear_input_buffer();
    int found = 0;
    while (fread(&f_book, sizeof(book), 1, fbook) == 1) {
        if (strcmp(idd, f_book.barcode) != 0) {
            if (fwrite(&f_book, sizeof(book), 1, fbook_new) != 1) {
                perror("Error writing to new file");
                fclose(fbook);
                fclose(fbook_new);
                return;
            }
        } else {
            found = 1;
        }
    }
    fclose(fbook);
    fclose(fbook_new);
    if (found) {
        if (remove("book.dat") != 0) {
            perror("Error deleting old file");
        } else if (rename("booknew.dat", "book.dat") != 0) {
            perror("Error renaming new file");
        } else {
            printf("    Book deleted successfully.\n");
        }
    } else {
        printf("    Book with barcode %s not found.\n", idd);
        remove("booknew.dat"); // Clean up if book not found
    }
}
void list_books() {
    printf("\n==== LIST ALL BOOKS ====\n");
    printf("    Listing all books in the system...\n");
    FILE *fbook = fopen("book.dat", "rb");
    if (fbook == NULL) {
        perror("Error opening book.dat");
        return;
    }
    book f_bookl;
    int book_count = 0;
    while (fread(&f_bookl, sizeof(book), 1, fbook) == 1) {
        printf("\n    BOOK #%d\n", ++book_count);
        printf("    BARCODE: %s\n", f_bookl.barcode);
        printf("    BOOK NAME: %s\n", f_bookl.b_name);
        printf("    AUTHOR: %s\n", f_bookl.author);
        printf("    SORT: %s\n", f_bookl.b_kind);
        printf("    STOCK: %d\n", f_bookl.b_stock);
    }
    if (book_count == 0) {
        printf("    No books found in the system.\n");
    }
    fclose(fbook);
}

void borrow_menu() {
    while (1) {
        int choice;
        printf("\n==== BORROW MENU ====\n");
        printf("    1. Borrow a Book\n");
        printf("    2. Return a Book\n");
        printf("    3. List All Borrowed Books\n");
        printf("    0. Return to Personal Menu\n");
        printf("    Please enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            perror("Error reading input. Please enter a valid number.");
            clear_input_buffer();
            continue;
        }

        switch (choice) {
            case 1:
                borrow_book();
                break;
            case 2:
                return_book();
                break;
            case 3:
                list_borrow();
                break;
            case 0:
                printf("Returning to Personal Menu...\n");
                return;
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    }
}
void borrow_book() {
    FILE *fFILE_oduncKayitlar = fopen("oduncKitap_kayitlari.dat", "ab"); // Borrowed book records file
    if (fFILE_oduncKayitlar == NULL) {
        perror("Error opening file");
        return;
    }
    odunc yeni_odunckitap;
    printf("\nThe book's barcode is: ");
    if (scanf("%10s", yeni_odunckitap.kitap_barkod) != 1 || strlen(yeni_odunckitap.kitap_barkod) != 10) {

    }
    printf("\n==== BORROW A BOOK ====\n");
    clear_input_buffer();
    if (Is_inStock(yeni_odunckitap.kitap_barkod)== 1) { // Book is in stock
        // Calculate the return date (14 days later)
        time_t now=time(NULL);
        struct tm *given_date = localtime(&now);
        given_date->tm_mday+=14;
        mktime(given_date);
        strftime(yeni_odunckitap.iade_tarihi, sizeof(yeni_odunckitap.iade_tarihi), "%d/%m/%Y", given_date);
        printf("\nThe mandatory return date (DD/MM/YY) will be %s.\n", yeni_odunckitap.iade_tarihi);
        yeni_odunckitap.gecikme_gun = 0;
        yeni_odunckitap.odenecek_tutar = 0;
        if (fwrite(&yeni_odunckitap, sizeof(odunc), 1, fFILE_oduncKayitlar) == 1) {
            printf("\nThe process of borrowing the book is complete.\n");
        } else {
            perror("Error writing to file");
        }
        fclose(fFILE_oduncKayitlar);
    }
    else { // Book is not in stock
        printf("\nThe book you are looking for is not available in stock :/\n");
        fclose(fFILE_oduncKayitlar);
    }
}
int calc_delay(const char *zorunlu_iade_tarihi) {
    // Get the current date and time
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char today_date_str[11];
    strftime(today_date_str, sizeof(today_date_str), "%d/%m/%Y", &tm);

    printf("Mandatory book return date: %s\n", zorunlu_iade_tarihi);
    printf("Today's date: %s\n", today_date_str);

    // Extract the day, month, and year from the today_date_str
    int today_day, today_month, today_year;
    sscanf(today_date_str, "%2d/%2d/%4d", &today_day, &today_month, &today_year);

    // Extract the day, month, and year from the zorunlu_iade_tarihi
    int due_day, due_month, due_year;
    sscanf(zorunlu_iade_tarihi, "%2d/%2d/%4d", &due_day, &due_month, &due_year);// Convert YY to YYYY (assuming 21st century)

    struct tm due_date = {0};
    struct tm today_date = {0};

    // Fill the struct tm for due date and today's date
    fill_date(&due_date, due_year, due_month, due_day);
    fill_date(&today_date, today_year, today_month, today_day);

    // Convert struct tm to time_t
    time_t due_time = mktime(&due_date);
    time_t today_time = mktime(&today_date);

    // Calculate the difference in seconds and convert to days
    double difference = difftime(today_time, due_time);
    if(difference<=0) {
        return 0;
    }
    int result = difference / (60 * 60 * 24);

    return result;
}
int Is_inStock(char *input_barcode){
    FILE *stock_file = fopen("book.dat", "r+b");
    book scan_book;
    while (fread(&scan_book, sizeof(book), 1, stock_file) == 1){
        if (strcmp(scan_book.barcode, input_barcode) == 0 && scan_book.b_stock > 0){
            scan_book.b_stock--;
            fseek(stock_file,-(long)sizeof(book),SEEK_CUR);
            fwrite(&scan_book,sizeof(book),1,stock_file);
            fclose(stock_file);
            return 1;
        }
    }
    fclose(stock_file);
    return 0;
}
void return_book() {
    FILE *fFILE_oduncKayitlar = fopen("oduncKitap_kayitlari.dat", "rb");
    FILE *fFILE_oduncKayitlar_new = fopen("oduncKitap_kayitlari_new.dat", "wb");
    FILE *stock_file = fopen("book.dat", "rb+");
    if (fFILE_oduncKayitlar == NULL || fFILE_oduncKayitlar_new == NULL || stock_file == NULL) {
        perror("Error opening file");
        if (fFILE_oduncKayitlar) fclose(fFILE_oduncKayitlar);
        if (fFILE_oduncKayitlar_new) fclose(fFILE_oduncKayitlar_new);
        if (stock_file) fclose(stock_file);
        return;
    }

    odunc yeni_odunckitap;
    book find_book;
    char book_barcodd[11];
    int input_control_flag = 0;

    clear_input_buffer();
    printf("\nThe barcode of the book: ");
    if (scanf("%10s", book_barcodd) != 1 || strlen(book_barcodd) != 10) {
        input_control_flag = 1;
    }
    if (strcmp("exit", book_barcodd) == 0) {
        fclose(fFILE_oduncKayitlar);
        fclose(fFILE_oduncKayitlar_new);
        fclose(stock_file);
        return;
    }
    clear_input_buffer();
    if (input_control_flag == 1) {
        printf("You have entered wrong information!\n");
        fclose(fFILE_oduncKayitlar);
        fclose(fFILE_oduncKayitlar_new);
        fclose(stock_file);
        return;
    }

    int check_flag = 0;
    int iade_gecikme;

    while (fread(&yeni_odunckitap, sizeof(odunc), 1, fFILE_oduncKayitlar) == 1) {
        if (strcmp(yeni_odunckitap.kitap_barkod, book_barcodd) == 0) {
            check_flag = 1;
            fseek(stock_file, 0, SEEK_SET);
            while (fread(&find_book, sizeof(book), 1, stock_file) == 1) {
                if (strcmp(find_book.barcode, book_barcodd) == 0) {
                    find_book.b_stock++;
                    fseek(stock_file, -(long)sizeof(book), SEEK_CUR);
                    fwrite(&find_book, sizeof(book), 1, stock_file);
                    break;
                }
            }
            iade_gecikme = calc_delay(yeni_odunckitap.iade_tarihi);
            break;
        }
    }

    if (check_flag == 1) {
        fseek(fFILE_oduncKayitlar, 0, SEEK_SET);
        while (fread(&yeni_odunckitap, sizeof(odunc), 1, fFILE_oduncKayitlar) == 1) {
            if (strcmp(yeni_odunckitap.kitap_barkod, book_barcodd) != 0) {
                fwrite(&yeni_odunckitap, sizeof(odunc), 1, fFILE_oduncKayitlar_new);
            }
        }

        printf("\nThe list of borrowed books has been updated.\n\n");
        printf("The amount the member needs to pay: %d\n", iade_gecikme * 1); // Assume 1 TL penalty per day of delay
        printf("The return process was successful!\n");

        fclose(fFILE_oduncKayitlar);
        fclose(fFILE_oduncKayitlar_new);
        fclose(stock_file);
        remove("oduncKitap_kayitlari.dat");
        rename("oduncKitap_kayitlari_new.dat", "oduncKitap_kayitlari.dat");
    } else {
        printf("The book with the entered barcode number has not been returned.\n");
        fclose(fFILE_oduncKayitlar);
        fclose(fFILE_oduncKayitlar_new);
        fclose(stock_file);
    }
}
void list_borrow() {
    FILE *fFILE_oduncKayitlar_list = fopen("oduncKitap_kayitlari.dat", "rb");
    if (fFILE_oduncKayitlar_list == NULL) {
        perror("Error opening file");
        return;
    }
    odunc oduncl;
    printf("\n==== LIST BORROWED BOOKS ====\n");
    printf("BORROWED BOOK INFORMATION\n");
    while (fread(&oduncl, sizeof(odunc), 1, fFILE_oduncKayitlar_list) == 1) {
        printf("Barcode: %s\n", oduncl.kitap_barkod);
        printf("Date of Issue: %s\n", oduncl.teslim_tarihi);
        printf("Return Date: %s\n", oduncl.iade_tarihi);
        printf("Delay (days): %d\n", oduncl.gecikme_gun);
        printf("Amount Due: %d\n", oduncl.odenecek_tutar);
        printf("\n");
    }
    if (ferror(fFILE_oduncKayitlar_list)) {
        perror("Error reading from file");
    }
    fclose(fFILE_oduncKayitlar_list);
}
void fill_file() {
    FILE *fpersonal = fopen("personal.dat", "wb");
    s_personal fipersonal;
    if (fgets(fipersonal.name, sizeof(fipersonal.name), stdin) != NULL) {
        fipersonal.name[strcspn(fipersonal.name, "\n")] = '\0'; // Remove newline
    }
    if (fgets(fipersonal.id, sizeof(fipersonal.id), stdin) != NULL) {
        fipersonal.id[strcspn(fipersonal.id, "\n")] = '\0'; // Remove newline
    }
    fwrite(&fipersonal,sizeof(s_personal),1,fpersonal);
    fclose(fpersonal);
}


