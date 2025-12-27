#ifndef BANK_SYS_H
#define BANK_SYS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
    int month;
    int year;
    
}date;

typedef struct {
    char account_num[20];
    char name[50];
    char address[100];
    float balance;
    char mobile[15];
    date openingDate;
    char date_opened[15];
    char status[10];
} account;

extern int check_exist(double acc_num);
extern int check_status(double acc_num);
extern int check_accountNumbers(double acc_num_1, double acc_num_2);

extern void bank_system_init(void);

extern int login(void); //////TOCHECK

extern date getCurrentDate(void);

extern void Load(void);

extern void query_search(double acc_num);

extern void search(void);

extern void printAccounts(account arr[], int n);

extern void Advanced_search(void);

extern void add(void);

extern void Delete(void);

extern void modify(void);

extern void change_status(void);

extern int CheckDailyLimit(double currentDailyLimit, double amount);

extern void Withdraw(void);

extern void deposit(void);

extern void Transfer(void);

extern void print(void);

extern void save(void);

extern void quit(void);

extern void menu(void);

extern void setColor(int color);

extern void delete_multi(void);

extern void report(void);

extern void sortByName(account arr[], int n);
extern void sortByBalance(account arr[], int n);
extern void sortByDate(account arr[], int n);
extern void quit_program(void);

#endif // BANK_SYS_H