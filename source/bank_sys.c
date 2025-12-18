#include "bank_sys.h"

#include <stdio.h>
#include <stdlib.h>

void login() {
    char username[50];
    char password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
}
