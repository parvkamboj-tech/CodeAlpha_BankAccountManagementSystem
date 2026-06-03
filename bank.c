/*
    Bank Account Management System
    Made by: [PARV KAMBOJ]
    Internship Task 4 - CodeAlpha
    Language: C
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store account details
struct Account {
    int accNumber;
    char name[50];
    float balance;
};

// Function to deposit money
void deposit(struct Account *acc) {
    float amount;
    printf("\nEnter amount to deposit: Rs. ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount! Please enter a positive value.\n");
        return;
    }

    acc->balance += amount;
    printf("Rs. %.2f deposited successfully!\n", amount);
    printf("New Balance: Rs. %.2f\n", acc->balance);

    // Save updated balance to file
    FILE *fp = fopen("account.dat", "wb");
    if (fp != NULL) {
        fwrite(acc, sizeof(struct Account), 1, fp);
        fclose(fp);
    }
}

// Function to withdraw money
void withdraw(struct Account *acc) {
    float amount;
    printf("\nEnter amount to withdraw: Rs. ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    if (amount > acc->balance) {
        printf("Sorry! Insufficient balance.\n");
        printf("Available Balance: Rs. %.2f\n", acc->balance);
        return;
    }

    acc->balance -= amount;
    printf("Rs. %.2f withdrawn successfully!\n", amount);
    printf("Remaining Balance: Rs. %.2f\n", acc->balance);

    // Save updated balance to file
    FILE *fp = fopen("account.dat", "wb");
    if (fp != NULL) {
        fwrite(acc, sizeof(struct Account), 1, fp);
        fclose(fp);
    }
}

// Function to check balance
void checkBalance(struct Account acc) {
    printf("\n------------------------------\n");
    printf("  Account Holder : %s\n", acc.name);
    printf("  Account Number : %d\n", acc.accNumber);
    printf("  Current Balance: Rs. %.2f\n", acc.balance);
    printf("------------------------------\n");
}

// Function to load account from file
int loadAccount(struct Account *acc) {
    FILE *fp = fopen("account.dat", "rb");
    if (fp == NULL) {
        return 0; // File doesn't exist yet
    }
    fread(acc, sizeof(struct Account), 1, fp);
    fclose(fp);
    return 1;
}

// Function to create a new account
void createAccount(struct Account *acc) {
    printf("\n=== Create New Account ===\n");
    printf("Enter Account Number: ");
    scanf("%d", &acc->accNumber);
    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]", acc->name);
    printf("Enter Initial Deposit Amount: Rs. ");
    scanf("%f", &acc->balance);

    // Save to file
    FILE *fp = fopen("account.dat", "wb");
    if (fp != NULL) {
        fwrite(acc, sizeof(struct Account), 1, fp);
        fclose(fp);
        printf("\nAccount created successfully!\n");
    } else {
        printf("Error creating account!\n");
    }
}

int main() {
    struct Account acc;
    int choice;
    int accountExists;

    printf("====================================\n");
    printf("   WELCOME TO ABC BANK SYSTEM   \n");
    printf("====================================\n");

    // Try to load existing account
    accountExists = loadAccount(&acc);

    if (!accountExists) {
        printf("\nNo account found. Let's create one!\n");
        createAccount(&acc);
    } else {
        printf("\nAccount loaded successfully! Welcome, %s!\n", acc.name);
    }

    // Main menu loop
    while (1) {
        printf("\n======= MAIN MENU =======\n");
        printf("1. Deposit Money\n");
        printf("2. Withdraw Money\n");
        printf("3. Balance Enquiry\n");
        printf("4. Exit\n");
        printf("=========================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                deposit(&acc);
                break;

            case 2:
                withdraw(&acc);
                break;

            case 3:
                checkBalance(acc);
                break;

            case 4:
                printf("\nThank you for using ABC Bank!\n");
                printf("Goodbye, %s!\n", acc.name);
                exit(0);

            default:
                printf("Wrong choice! Please enter 1-4.\n");
        }
    }

    return 0;
}
