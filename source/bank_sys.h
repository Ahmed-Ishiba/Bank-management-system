#ifndef BANK_SYS_H
#define BANK_SYS_H


typedef struct{
    int day;
    int month;
    int year;
}date;

typedef struct {
    char accountNumber[10];   
    char name[50];
    char email[50];
    char mobile[11];
    double balance;
    date dateOpened;
    int status;
    double dailyWithdraw;
} account; 

extern int check_exist(double acc_num);
extern int check_status(double acc_num);
extern int check_accountNumbers(double acc_num_1, double acc_num_2);


extern void bank_system_init(void);

extern void login(void);

extern void Load(void);

extern void query_search(double acc_num);

extern void advanced_search(char name[]);

extern void add(void);

extern void delete(double acc_num);

extern void modify(double acc_num);

extern void change_status(double acc_num);

extern void check_limit(double acc_num);

extern void withdraw(double acc_num, double amount);

extern void deposit(double acc_num, double amount);

extern void transfer(double from_acc, double to_acc, double amount);

extern void report(int acc_num);

extern void print(int acc_num);

extern void save(void);

extern void quit(void);

extern void menu(void);

extern void delete_multi(void);


#endif // BANK_SYS_H