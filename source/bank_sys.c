#include "bank_sys.h"

#include <stdio.h>
#include <stdlib.h>

void bank_system_init(void) {
    // Initialization code for the bank system
    printf("Bank system initialized.\n");
}

void Load(){
       FILE *fp = fopen("accounts.txt", "r");
    if (fp == NULL) {
        printf("Failed to open file");
        return -1;
    }
    char line[300];
    account acc;
    while (fgets(line, sizeof(line), fp) != NULL) {
        char *token = strtok(line, ",");
        strcpy(acc.accountNumber, token);
        token = strtok(NULL, ",");
        strcpy(acc.name, token);
        token = strtok(NULL, ",");
        strcpy(acc.email, token);
        token = strtok(NULL, ",");
        sscanf(token, "%f", &acc.balance);
        token = strtok(NULL, ",");
        strcpy(acc.mobile, token);
        token = strtok(NULL, ",");
        strcpy(acc.dateOpened, token);
        token = strtok(NULL, ",\n");
        strcpy(acc.status, token);
        printf("%s, %s, %s, %.2f, %s, %d, %.2f\n",  acc.accountNumber, acc.name, acc.email,
            acc.balance, acc.mobile, acc.dateOpened.year, acc.status);
    }

    fclose(fp);
    return 0;
}

int check_exist(double acc_num) {
    // Check if account exists
    return 0; // Placeholder return value
}

int check_status(double acc_num) {
    // Check account status
    return 0; // Placeholder return value
}

int check_accountNumbers(double acc_num_1, double acc_num_2) {
    return (acc_num_1 == acc_num_2);
}