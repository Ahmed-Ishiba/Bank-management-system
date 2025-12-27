#include "bank_sys.h"
#include <ctype.h>

account acc[100];

double dailywithdraw[100] = {0};

int count = 0;

date getCurrentDate(void) {
    time_t now = time(NULL);
    struct tm tm_now = *localtime(&now);

    date d;
    d.month = tm_now.tm_mon + 1;   
    d.year  = tm_now.tm_year + 1900;

    return d;
}



void Load() {
    char line[500];
    char *token;
   
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fgets(line, sizeof(line), file) && count < 100) {
        line[strcspn(line, "\r\n")] = 0; 

        token = strtok(line, ",");
        if (token) strcpy(acc[count].account_num, token);

        token = strtok(NULL, ",");
        if (token) strcpy(acc[count].name, token);

        token = strtok(NULL, ",");
        if (token) strcpy(acc[count].address, token);

        token = strtok(NULL, ",");
        if (token) acc[count].balance = atof(token);

        token = strtok(NULL, ",");
        if (token) strcpy(acc[count].mobile, token);

        token = strtok(NULL, ",");
        if (token) sscanf(token, "%d-%d", &acc[count].openingDate.month, &acc[count].openingDate.year);

        token = strtok(NULL, ",");
        if (token) {
            while (*token == ' ') token++; 
            strcpy(acc[count].status, token);
        }

        count++;
    }

    fclose(file);
    printf("Loaded %d accounts from file successfully\n", count);
}
void bank_system_init(void) {
    // Initialization code for the bank system
    printf("Bank system initialized.\n");
}


int login() ///////TOCHECK
{
    printf("=== Login ===\n");
    FILE *file;
    char username[50];
    char password[50];
    char stored_username[50];
    char stored_password[50];
    int found ;
    
    do{
    file = fopen("users.txt", "r");
    found = 0;
    
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }
   
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);
    while (fscanf(file, "%s %s", stored_username, stored_password) != EOF)
        {
            if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0)
            {
                printf("Login successful!\n");
                found = 1;
                break;
            }
        }
        fclose(file);
        if (found == 0)
            printf("Invalid username or password, please try again.\n");
    } while (found == 0);

   
    return 1;
}


int check_exist(double acc_num) {
    // Check if account exists
    return acc_num; // Placeholder return value
}

int check_status(double acc_num) {
    // Check account status
    return acc_num; // Placeholder return value
}

int check_accountNumbers(double acc_num_1, double acc_num_2) {
    return (acc_num_1 == acc_num_2);
}


void add (){
   FILE *fp = fopen("accounts.txt", "a");
    
    if (fp == NULL) {
         printf("Error opening file.\n");
         return;
    }
    account acc;
    printf("Enter account number: ");
    scanf("%s", acc.account_num);
    // if(!isdigit(acc.account_num)){
    //     printf("Account number must be numeric.\n");
    //     fclose(fp);
    //     return;

    // }
    getchar(); 
    
    char trans_name[100];
    snprintf(trans_name, sizeof(trans_name), "%s.txt", acc.account_num);
    FILE *transaction_fp = fopen(trans_name, "w");
    transaction_fp = fopen(trans_name, "a");
    fclose(transaction_fp);
    FILE *check_fp = fopen("accounts.txt", "r");
    char line[256];
    while (fgets(line, sizeof(line), check_fp)) {
        char temp[256];
        strcpy(temp, line);
        char *token = strtok(temp, ","); // account number
        if (strcmp(token, acc.account_num) == 0) {
            printf("Error: Account number %s already exists.\n", acc.account_num);
            fclose(fp);
            fclose(check_fp);
            return;
        }
    }

    printf("Enter name: ");
    
    fgets(acc.name, sizeof(acc.name), stdin);
    
    acc.name[strcspn(acc.name, "\n")] = 0; // remove newline
    
    printf("Enter address: ");
    
    fgets(acc.address, sizeof(acc.address), stdin);
    acc.address[strcspn(acc.address, "\n")] = 0; // remove newline
    
    printf("Enter balance: ");
    scanf("%f", &acc.balance);
    getchar(); // consume newline
    
    printf("Enter mobile: ");
    fgets(acc.mobile, sizeof(acc.mobile), stdin);
    acc.mobile[strcspn(acc.mobile, "\n")] = 0; // remove newline
    
    date currentDate = getCurrentDate();
    acc.openingDate.month = currentDate.month;
    acc.openingDate.year = currentDate.year;

    //sprintf(acc.openingDate, "%02d-%04d", currentDate.month, currentDate.year);
    strcpy(acc.status, " active"); // default status
    fprintf(fp, "%s,%s,%s,%.2f,%s,%02d-%04d,%s\n", acc.account_num, acc.name, acc.address, acc.balance, acc.mobile, acc.openingDate.month, acc.openingDate.year, acc.status);
    fclose(fp);
    fclose(check_fp);
    printf("Account added successfully.\n");
    return;


}


void Delete() {
    FILE *fp = fopen("accounts.txt", "r");
    FILE *temp_fp = fopen("temp.txt", "w");
    if (fp == NULL || temp_fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    char target[20];
    char line[256];
    int count = 0;
    float balance = 0.0;
    printf("Enter account number to delete: ");
    scanf("%s", target);

    while (fgets(line, sizeof(line), fp)) {
        char temp[256];
        strcpy(temp, line);
        char *token = strtok(temp, ",");  // account number
        if (strcmp(token, target) == 0) {
            count++;
            strtok(NULL, ","); // name
            strtok(NULL, ","); // address
            token = strtok(NULL, ","); // balance
            sscanf(token, "%f", &balance);
        }
    }
    if (count == 0) {
        printf("Account number %s does not exist.\n", target);
        fclose(fp);
        fclose(temp_fp);
        remove("temp.txt");
        return;
    }
    if (count > 1) {
        printf("Error: duplicate account number %s found.\n", target);
        fclose(fp);
        fclose(temp_fp);
        remove("temp.txt");
        return;
    }
    if (balance > 0 || balance < 0) {
        printf("Deletion rejected: account balance is greater than zero.\n");
        fclose(fp);
        fclose(temp_fp);
        remove("temp.txt");
        return;
    }
    /* ---------- SECOND PASS: delete ---------- */
    rewind(fp);
    while (fgets(line, sizeof(line), fp)) {
        char temp[256];
        strcpy(temp, line);
        char *token = strtok(temp, ",");
        if (strcmp(token, target) != 0) {
            fputs(line, temp_fp);  // keep record
        }
        // else → skip line (delete)
    }
    fclose(fp);
    fclose(temp_fp);
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
    printf("Account %s deleted successfully.\n", target);
    return;
}

void deposit()
{
    FILE *fp = fopen("accounts.txt", "r");
    
    FILE *temp_fp = fopen("temp.txt", "w");
    if (fp == NULL || temp_fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    //account acc[100];
    char target[20];
    char line[256];
    char target_name[100];
    int count = 0;
    float balance = 0.0;
    printf("Enter account number to deposit: ");
    scanf("%s", target);
    // report part
    snprintf(target_name, sizeof(target_name), "%s.txt", target);
    FILE *transaction_fp = fopen(target_name, "a");
    
    printf("Enter deposit amount: ");
    float deposit_amount;
    scanf("%f", &deposit_amount);
    if (deposit_amount <= 0) {
        printf("Deposit amount must be positive.\n");
        fclose(fp);
        fclose(temp_fp);
        remove("temp.txt");
        return;
    }
    else if (deposit_amount > 10000) {
        printf("Deposit amount exceeds the limit of 10000.\n");
        fclose(fp);
        fclose(temp_fp);
        remove("temp.txt");
        return;
    }
    while (fgets(line, sizeof(line), fp)) {
        char temp[256];
        strcpy(temp, line);
        char *token = strtok(temp, ",");  // account number
        if (strcmp(token, target) == 0) {
            
            count++;
            strtok(NULL, ","); // name
            strtok(NULL, ","); // address
            char *balance_str = strtok(NULL, ","); // balance
            sscanf(balance_str, "%f", &balance);
        }
    }
    if (count == 0) {
        printf("Account number %s does not exist.\n", target);
        fclose(fp);
        fclose(temp_fp);
        remove("temp.txt");
        return;
    }
    if (balance < 0) {
        printf("Account has negative balance. Deposit not allowed.\n");
        fclose(fp);
        fclose(temp_fp);
        remove("temp.txt");
        return;
    }
    rewind(fp);
    /* ---------- SECOND PASS: process deposit ---------- */
    while (fgets(line, sizeof(line), fp)) {
        char temp[256];
        strcpy(temp, line);
        char *token = strtok(temp, ",");  // account number
        if (strcmp(token, target) == 0) {
            char *name = strtok(NULL, ","); // name
            char *address = strtok(NULL, ","); // address
            char *balance_str = strtok(NULL, ","); // balance
            char *mobile = strtok(NULL, ","); // mobile
            char *date_opened = strtok(NULL, ","); // date opened
            char *status = strtok(NULL, ","); // status
            printf("Status: %s\n", status);
            if(!(strcmp(status," active")) && !(strcmp(status,"active")))
            {
            printf("Account is not active.\n");
            fclose(fp);
            fclose(temp_fp);
            remove("temp.txt");
            return;
            }
            float current_balance;
            sscanf(balance_str, "%f", &current_balance);
            current_balance += deposit_amount;

            //report part
            fprintf(transaction_fp, "%s %.2f\n","deposited: ", deposit_amount);
            
            fprintf(temp_fp, "%s,%s,%s,%.2f,%s,%s,%s\n", token, name, address, current_balance, mobile, date_opened, status);
        } else {
            fputs(line, temp_fp);
        }
    }
    fclose(fp);
    fclose(transaction_fp);
    fclose(temp_fp);
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
    printf("Deposit of %.2f to account %s successful.\n", deposit_amount, target);
    return ;
}


void change_status() 
{
    FILE *fp = fopen("accounts.txt", "r");
    FILE *temp_fp = fopen("temp.txt", "w"); 
    if (fp == NULL || temp_fp == NULL) {
        printf("Error opening file.\n");
        return;}
    char target[20];
    char line[256];
    int count = 0;
    printf("Enter account number to change status: ");
    scanf("%s", target);
    /* ---------- FIRST PASS: count ---------- */
     while (fgets(line, sizeof(line), fp)) {
        char temp[256];
        strcpy(temp, line);
        char *token = strtok(temp, ",");  // account number
        if (strcmp(token, target) == 0) {
            count++;
        }
    }
    if (count == 0) {
        printf("Account number %s does not exist.\n", target);
        fclose(fp);
        fclose(temp_fp);
        remove("temp.txt");
        return;
    }
    if (count > 1) {
        printf("Error: duplicate account number %s found.\n", target);
        fclose(fp);
        fclose(temp_fp);
        remove("temp.txt");
        return;
    }
    printf(" What is the new status? (Active/Inactive): ");
    char new_status[10];
    scanf("%s", new_status);
    getchar(); // consume newline
    /* ---------- SECOND PASS: change status ---------- */
    rewind(fp);
    while (fgets(line, sizeof(line), fp)) {
        char temp[256];
        strcpy(temp, line);
        char *token = strtok(temp, ",");  // account number
        char *name = strtok(NULL, ","); // name
        char *address = strtok(NULL, ","); // address
        char *balance = strtok(NULL, ","); // balance
        char *mobile = strtok(NULL, ","); // mobile
        char *date_opened = strtok(NULL, ","); // date opened
        char *status = strtok(NULL, ","); // status
        status[strcspn(status, "\n")] = 0; // remove newline
        if (strcmp(token, target) == 0 && (strcmp(status, " Active") == 0 || strcmp(status, " active") == 0)) {
            if(strcmp(new_status, "Inactive") == 0 || strcmp(new_status, "inactive") == 0) {
            // Change status to " inactive"
            fprintf(temp_fp, "%s,%s,%s,%s,%s,%s, inactive\n", token, name, address, balance, mobile, date_opened);
            printf("Account number %s status changed to Inactive.\n", target);
            } else if(strcmp(new_status, "Active") == 0 || strcmp(new_status, "active") == 0) {
                // Already Active
                printf("Do you want to change the status to (Active) and it is already (Active)?\n");
                int choice;
                printf("1. Yes\n2. No\n");
                scanf("%d", &choice);
                if(choice == 1) {
                    fputs(line, temp_fp);
                    printf("Account number %s status remains Active.\n", target);
                } else {
                    printf("No changes made to account number %s.\n", target);
                    fclose(fp);
                    fclose(temp_fp);
                    remove("temp.txt");
                   return ;
                }
            }
        }else if(strcmp(token, target) == 0 && (strcmp(status, " Inactive") == 0 || strcmp(status, " inactive") == 0)) {
            if(strcmp(new_status, "Active") == 0 || strcmp(new_status, "active") == 0) {
            // Change status to " activein9700000007"
            fprintf(temp_fp, "%s,%s,%s,%s,%s,%s, active\n", token, name, address, balance, mobile, date_opened);
            printf("Account number %s status changed to Active.\n", target);
        } else if(strcmp(new_status, "Inactive") == 0 || strcmp(new_status, "inactive") == 0) {
                // Already Inactive
                printf("Do you want to change the status to (Inactive) and it is already (Inactive)?\n");
                int choice;
                printf("1. Yes\n2. No\n");
                scanf("%d", &choice);
                if(choice == 1) {
                    fputs(line, temp_fp);
                    printf("Account number %s status remains Inactive.\n", target);
                } else {
                    printf("No changes made to account number %s.\n", target);
                    fclose(fp);
                    fclose(temp_fp);
                    remove("temp.txt");
                   return ;
                }
            }
        }
        else {
            fputs(line, temp_fp);
        }
    }
    fclose(fp);
    fclose(temp_fp);
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
    return ;
}

void modify () {
    FILE *fp = fopen("accounts.txt", "r");
    FILE *temp_fp = fopen("temp.txt", "w");
    if (fp == NULL || temp_fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    char target[20];
    char line[256];
    int found = 0;
    printf("Enter account number to modify: ");
    scanf("%s", target);
    getchar(); // consume newline

    while (fgets(line, sizeof(line), fp)) {
        char copy[256];
        strcpy(copy, line);
        char *token = strtok(line, ",");           // account number
        char *name = strtok(NULL, ",");            // name
        char *email = strtok(NULL, ",");           // email (address)
        char *balance = strtok(NULL, ",");         // balance
        char *mobile = strtok(NULL, ",");          // mobile
        char *date_opened = strtok(NULL, ",");     // date opened
        char *status = strtok(NULL, ",\n");        // status
        if (strcmp(token, target) == 0) {
            found = 1;
            char input[100];
            printf("Current Name: %s\nNew Name (Enter to keep): ", name);
            fgets(input, sizeof(input), stdin);
            if (input[0] != '\n') {
                input[strcspn(input, "\n")] = 0;// remove newline of fgets to store correctly in file 
                strcpy(name, input);
            }
            printf("Current Mobile: %s\nNew Mobile (Enter to keep): ", mobile);
            fgets(input, sizeof(input), stdin);
            if (input[0] != '\n') {
                input[strcspn(input, "\n")] = 0;
                strcpy(mobile, input);
            }
            printf("Current Email: %s\nNew Email (Enter to keep): ", email);
            fgets(input, sizeof(input), stdin);
            if (input[0] != '\n') {
                input[strcspn(input, "\n")] = 0;
                strcpy(email, input);
            }
            fprintf(temp_fp, "%s,%s,%s,%s,%s,%s,%s\n",
                    token, name, email, balance, mobile, date_opened, status);
        } else {
            fputs(copy, temp_fp);
        }
    }
    if (!found) {
        printf("Account number not found.\n");
        remove("temp.txt");
        return;
    }
    fclose(fp);
    fclose(temp_fp);
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
    printf("Account number %s modified successfully.\n", target);
    return;
}
///////////////////////////////////////////////
#define FOREGROUND_BLUE 0x0001
#define FOREGROUND_RED 0x0004
#define FOREGROUND_INTENSITY 0x0008
///////////////////////////////////////////////
void menu(){
    int choice;
    int decision;
    Load();                 

    while (1) {
    setColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    printf("-------MENU------\n");
    setColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);
    printf("1.ADD\n");
    printf("2.DELETE\n");
    printf("3.MODIFY\n");
    printf("4.SEARCH\n");
    printf("5.ADVANCED SEARCH\n");
    printf("6.CHANGE STATUS\n");
    printf("7.WITHDRAW\n");
    printf("8.DEPOSIT\n");
    printf("9.TRANSFER\n");
    printf("10.REPORT\n");
    printf("11.PRINT\n");
    printf("12.DELETE MULTIPLE ACCOUNTS\n");
    printf("13.QUIT\n");
    printf("Choose an option: ");
    scanf("%d",&choice);

        switch (choice) {
            case 1:
            add();
            break;

            case 2:
            Delete();
            break;
            
            case 3:
            modify();
            break;

            case 4:
            search();
            break;

            case 5:
            Advanced_search();
            break;

            case 6:
            change_status();
            break;

            case 7:
            Withdraw();
            break;

            case 8:
            deposit();
            break;

            case 9:
            Transfer();
            break;

            case 10:
            report();
            break;

            case 11:
            print();
            break;
            
            case 12:
            delete_multi();
            break;


            case 13:
            quit_program();
            break;

            default:
                printf("Invalid option.\n");
                printf("Press 0 to return to menu\n");
                printf("Press 1 to quit program\n");
                printf("Your choice: ");
                scanf("%d", &decision);

                if (decision == 0) {
                    continue;
                }
                else if (decision == 1) {
                    quit_program();
                    return;
                }
                else {
                    printf("Invalid input. Returning to menu.\n");
                }
        }
    }
}

void quit(void) {
    printf("Program has been terminated\n");
    exit(0);
}

void print() {
    if(count == 0) {
        printf("No accounts loaded.\n");
        return;
    }

    int choice;
    printf("\nChoose sorting option:\n");
    printf("1. Name\n2. Balance\n3. Date Opened\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            sortByName(acc, count);
            break;
        case 2:
            sortByBalance(acc, count);
            break;
        case 3:
            sortByDate(acc, count);
            break;
        default:
            printf("Invalid choice. Printing unsorted.\n");
    }

    printAccounts(acc, count);
}

void printAccounts(account arr[], int n) {
    printf("\n%-12s %-18s %-22s %-15s %-14s %-6s %-20s\n",
           "AccNum", "Name", "Address", "Balance", "Mobile", "DateOpened", "Status");
    printf("---------------------------------------------------------------------------------------------------------------\n");
    for(int i=0;i<n;i++){
        printf("%-12s %-18s %-22s %-15.2f %-14s %02d-%04d %-20s\n",
               arr[i].account_num,
               arr[i].name,
               arr[i].address,
               arr[i].balance,
               arr[i].mobile,
               arr[i].openingDate.month,
               arr[i].openingDate.year,
               arr[i].status);
    }
}
void setColor(int color) {
    // Color output not supported on this platform
    (void)color; // Suppress unused parameter warning
}

void save()
{
    FILE *file = fopen("accounts.txt", "w");
    if (file == NULL)
    {
        printf("Error saving accounts file.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s,%s,%s,%.2lf,%s,%d-%d,%s\n",
                acc[i].account_num,
                acc[i].name,
                acc[i].address,
                acc[i].balance,
                acc[i].mobile,
                acc[i].openingDate.month,
                acc[i].openingDate.year,
                acc[i].status);
    }

    fclose(file);
}

void search()
{
    FILE *file = fopen("accounts.txt", "r");
    char line[200];
    char accountNumber[50], name[50], email[50];
    char balance[50], phoneNumber[50], dateopened[50], status[50];
    int found = 0;
    char searchAccountNumber[50];
    printf("Enter Account Number to search: ");
    scanf("%s", searchAccountNumber);

    
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0';

        char *token = strtok(line, ",");
        if(token == NULL) continue;
        strcpy(accountNumber, token);

        token = strtok(NULL, ",");
        if(token == NULL) continue;
        strcpy(name, token);
        token = strtok(NULL, ",");
        if(token == NULL) continue;
        strcpy(email, token);

        token = strtok(NULL, ",");
        if(token == NULL) continue;
        strcpy(balance, token);

        token = strtok(NULL, ",");
        if(token == NULL) continue;
        strcpy(phoneNumber, token);
        token = strtok(NULL, ",");
        if(token == NULL) continue;
        strcpy(dateopened, token);

        token = strtok(NULL, ",");
        if(token == NULL) continue;
        strcpy(status, token);

        if (strcmp(accountNumber, searchAccountNumber) == 0)
        {
            printf("Account Number: %s\n", accountNumber);
            printf("Name: %s\n", name);
            printf("Email: %s\n", email);
            printf("Balance: %s\n", balance);
            printf("Phone Number: %s\n", phoneNumber);
            printf("Date Opened: %s\n", dateopened);
            printf("Status: %s\n", status);
            found = 1;
        }
    }
    fclose(file);

    if (!found)
    {
        printf("Account with Account Number %s not found.\n", searchAccountNumber);
    }
}

void Advanced_search()
{
    FILE *file;
    char line[200];
    char accountNumber[50], name[50], email[50];
    char balance[50], phoneNumber[50], dateopened[50], status[50];
    int found = 0;
    char keyword[50];
    printf("Enter key word: ");
    scanf("%s", keyword);

    file = fopen("accounts.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0';

        char *token = strtok(line, ",");
        if(token == NULL) continue;
        strcpy(accountNumber, token);

        token = strtok(NULL, ",");
        if(token == NULL) continue;
        strcpy(name, token);
        token = strtok(NULL, ",");
        if(token == NULL) continue;
        strcpy(email, token);

        token = strtok(NULL, ",");
        if(token == NULL) continue;
        strcpy(balance, token);

        token = strtok(NULL, ",");
        if(token == NULL) continue;
        strcpy(phoneNumber, token);
        token = strtok(NULL, ",");
        if(token == NULL) continue;
        strcpy(dateopened, token);

        token = strtok(NULL, ",");
        if(token == NULL) continue;
        strcpy(status, token);

        if (strstr(name, keyword)!=NULL)
        {
            printf("Account Number: %s\n", accountNumber);
            printf("Name: %s\n", name);
            printf("Email: %s\n", email);
            printf("Balance: %s\n", balance);
            printf("Phone Number: %s\n", phoneNumber);
            printf("Date Opened: %s\n", dateopened);
            printf("Status: %s\n", status);
            printf("--------------------------\n");
            found = 1;
        }
    }
    fclose(file);

    if (!found)
    {
        printf("Account with Account name %s not found.\n", keyword);
    }
}

int CheckDailyLimit(double currentDailyLimit, double amount) {
    if (currentDailyLimit + amount > 50000)
        return 0;
    return 1;
}

void Transfer(void) {
    char sndAcc[50], recAcc[50];
    double amount;
    char send_file[100], receive_file[100];
    int Snd_index = -1, Rec_index = -1;

    printf("Enter Sender Account Number: ");
    scanf("%s", sndAcc);
    printf("Enter Receiver Account Number: ");
    scanf("%s", recAcc);

    if(strcmp(sndAcc, recAcc) == 0) {
        printf("Sender and Receiver Account Numbers cannot be the same.\n");
        return;
    }

    printf("Enter Amount to Transfer: ");
    scanf("%lf", &amount);

    // Find sender and receiver in acc[]
    for(int i = 0; i < count; i++) {
        if(strcmp(acc[i].account_num, sndAcc) == 0) Snd_index = i;
        if(strcmp(acc[i].account_num, recAcc) == 0) Rec_index = i;
    }

    // Check if accounts exist
    if(Snd_index == -1 && Rec_index == -1) {
        printf("Both Sender and Receiver Accounts not found.\n");
        return;
    }
    if(Snd_index == -1) {
        printf("Sender Account not found.\n");
        
        return;
    }
    if(Rec_index == -1) {
        printf("Receiver Account not found.\n");
        
        return;
    }

    // Validate transfer amount
    if(amount <= 0) {
        printf("Transfer amount must be positive.\n");
        return;
    }

    // Validate account status
    if(!(strcmp(acc[Snd_index].status, " active"))) {
        printf("Sender Account is not active.\n");
        return;
    }
    if(!(strcmp(acc[Rec_index].status, " active"))) {
        printf("Receiver Account is not active.\n");
        return;
    }

    // Validate balance
    if(acc[Snd_index].balance < amount) {
        printf("Insufficient balance in Sender Account.\n");
        return;
    }

    // Prepare transaction files
    snprintf(send_file, sizeof(send_file), "%s.txt", sndAcc);
    FILE *send_fp = fopen(send_file, "a");
    if(!send_fp) {
        printf("Error opening sender transaction file.\n");
        return;
    }

    snprintf(receive_file, sizeof(receive_file), "%s.txt", recAcc);
    FILE *receive_fp = fopen(receive_file, "a");
    if(!receive_fp) {
        printf("Error opening receiver transaction file.\n");
        fclose(send_fp);
        return;
    }

    // Perform transfer
    acc[Snd_index].balance -= amount;
    acc[Rec_index].balance += amount;

    // Log transactions
    fprintf(send_fp, "Transferred: %.2f to %s\n", amount, recAcc);
    fprintf(receive_fp, "Received: %.2f from %s\n", amount, sndAcc);

    fclose(send_fp);
    fclose(receive_fp);

    // Save updated balances
    save();

    printf("Transfer of %.2lf from Account %s to Account %s successful.\n", amount, sndAcc, recAcc);
}
//////////////////////////////////////////////////////////////////////////
void loadDailyWithdrawals() {
    FILE *file = fopen("daily_withdrawals.txt", "r");
    if (file == NULL) {
        return;
    }

    for (int i = 0; i < count; i++) {
        fscanf(file, "%lf", &dailywithdraw[i]);
    }

    fclose(file);
}

void saveDailyWithdrawals() {
    FILE *file = fopen("daily_withdrawals.txt", "w");
    if (file == NULL) {
        printf("Error saving daily withdrawals file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%.2lf\n", dailywithdraw[i]);
    }

    fclose(file);
}


void Withdraw() {
    char accNum[50];
    
    char target_name[100];
    double amount;
    int i,index=-1;
    
    printf("Enter Account Number: ");
    scanf("%s", accNum);
    
    snprintf(target_name, sizeof(target_name), "%s.txt", accNum);
    FILE *transaction_fp = fopen(target_name, "a");
        
    printf("Enter amount to withdraw: ");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Invalid amount. Withdrawal amount must be positive.\n");
        fclose(transaction_fp);
        return;
    }
    if (amount > 10000) {
        printf("Withdrawal amount exceeds the maximum limit of 10000.\n");
        fclose(transaction_fp);
        return;
    }

       for(i=0;i<count;i++)
       {
        if(strcmp(acc[i].account_num,accNum)==0)
        {
            index=i;
            break;
        }
       }
         if(index==-1)
         {
          printf("Account not found.\n");
          fclose(transaction_fp);
          return;
         }
         if(strcmp(acc[index].status,"active")!=0)
            {
            printf("Account is not active.\n");
            fclose(transaction_fp);
            return;
            }
        if (acc[index].balance < amount) {
        printf("No enough balance.\n");
        fclose(transaction_fp);
        return;
        }
        if (!CheckDailyLimit(dailywithdraw[index], amount)) {
            printf("Daily withdrawal limit exceeded.\n");
            fclose(transaction_fp);
            return;
        }
        acc[index].balance -= amount;
        dailywithdraw[index] += amount;
        fprintf(transaction_fp, "%s %.2f\n","withdrawn: ", amount);
        fclose(transaction_fp);
       save();
       saveDailyWithdrawals();
        
    printf("Withdrawal of %.2lf from account %s successful, New balance: %.2lf\n", amount, accNum, acc[index].balance);
    printf("Total withdrawn today: %.2lf\n", dailywithdraw[index]);


}

void sortByName(account arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j].name, arr[j + 1].name) > 0) {
                account temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sortByBalance(account arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].balance < arr[j + 1].balance) {
                account temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sortByDate(account arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int cmp = arr[j].openingDate.year - arr[j + 1].openingDate.year;
            if (cmp == 0) {
                cmp = arr[j].openingDate.month - arr[j + 1].openingDate.month;
            }
            if (cmp < 0) {
                account temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void quit_program(void) {
    printf("Program has been terminated\n");
    exit(0);
}

void report(void) {
    char acc_num[50];
    printf("=== REPORT ===\n");
    printf("Enter account number: ");
    scanf("%s", acc_num);
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%s.txt",acc_num);
    FILE *file = fopen(buffer, "r");
    if (file == NULL) {
        printf("Error opening transaction file for account %s account may be missing.\n", acc_num);
        return;
    }
    char line[100];
    printf("Transaction History for Account %s:\n", acc_num);
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);  
}

void delete_multi(void) {
    int choice;

    printf("\nDELETE MULTIPLE ACCOUNTS\n");
    printf("1. By Date (YYYY-MM-DD)\n");
    printf("2. Inactive accounts > 90 days with zero balance\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            deleteByDate();
            break;
        case 2:
            deleteInactive();
            break;
        default:
            printf("Invalid choice.\n");
    }
}

void deleteByDate(void) {
    int month, year, day;
    int deleted = 0;

    printf("Enter date (YYYY-MM-DD): ");
    scanf("%d-%d-%d", &year, &month, &day);
    FILE *fp = fopen("accounts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if(!fp || !temp) {
        printf("Error opening file.\n");
        return;
    }

    char line[512];
    while(fgets(line, sizeof(line), fp)) {
        char copy[512];
        strcpy(copy, line);

        strtok(copy, ","); // acc num
        strtok(NULL, ","); // name
        strtok(NULL, ","); // address
        strtok(NULL, ","); // balance
        strtok(NULL, ","); // mobile
        char *date = strtok(NULL, ","); // MM-YYYY

        int acc_month, acc_year;
        sscanf(date, "%d-%d", &acc_month, &acc_year);

        if(acc_month == month && acc_year == year) {
            deleted++;   
        } else {
            fputs(line, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if(deleted == 0) {
        printf("No account created on the given date.\n");
        remove("temp.txt");
    } else {
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
        printf("Deleted %d account(s) successfully.\n", deleted);
    }
}

void deleteInactive(void) {
    int deleted = 0;
    date today = getCurrentDate();

    FILE *fp = fopen("accounts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if(!fp || !temp) {
        printf("Error opening file.\n");
        return;
    }

    char line[512];
    while(fgets(line, sizeof(line), fp)) {
        char copy[512];
        strcpy(copy, line);

        strtok(copy, ","); // acc num
        strtok(NULL, ","); // name
        strtok(NULL, ","); // address
        char *bal = strtok(NULL, ",");
        strtok(NULL, ","); // mobile
        char *date = strtok(NULL, ","); // MM-YYYY
        char *status = strtok(NULL, ",");

        double balance = atof(bal);
        int m, y;
        sscanf(date, "%d-%d", &m, &y);

        int months_diff = (today.year - y) * 12 + (today.month - m);

        if(strcmp(status, "inactive") == 0 &&
           balance == 0 &&
           months_diff > 3) {
            deleted++;
        } else {
            fputs(line, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if(deleted == 0) {
        printf("No inactive accounts for more than 90 days with zero balance.\n");
        remove("temp.txt");
    } else {
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
        printf("Deleted %d inactive account(s).\n", deleted);
    }
}
