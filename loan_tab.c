#include <stdio.h>
#include <math.h>
#include <stdbool.h>


bool validateInputs(double value) {
    if (value == 0) {
        return false;
    } else {
        return true;
    }
}

void amortToFile(double balance, double interestRate, int terms) {

    FILE *file = fopen("Loan_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    double monthlyRate = interestRate / 12;
    double payment = balance * (monthlyRate / (1 - pow(1 + monthlyRate, -terms)));

    fprintf(file, "Loan amount: $%.2f\n", balance);
    fprintf(file, "Interest rate: %.2f%%\n", interestRate * 100);
    fprintf(file, "Number of months: %d\n", terms);
    fprintf(file, "Monthly payment: $%.2f\n", payment);
    fprintf(file, "Total paid: $%.2f\n\n", payment * terms);

    fprintf(file, "Month #\tBalance\t\tInterest\tPrincipal\n");

    for (int count = 0; count < terms; ++count) {
        double interest = balance * monthlyRate;
        double monthlyPrincipal = payment - interest;
        balance -= monthlyPrincipal;

        fprintf(file, "%d\t$%.2f\t$%.2f\t$%.2f\n",
                count + 1, balance, interest, monthlyPrincipal);
    }

    fclose(file);
    printf("Loan data has been saved to Loan_data.txt\n");
}

void getValues() {
    double balance, interestRate;
    int terms;

    printf("Enter the loan amount: ");
    scanf("%lf", &balance);

    printf("Enter the annual interest rate (in percentage): ");
    scanf("%lf", &interestRate);
    interestRate /= 100; // Convert to decimal

    printf("Enter the number of months: ");
    scanf("%d", &terms);

    bool balVal = validateInputs(balance);
    bool intrVal = validateInputs(interestRate);

    if (balVal && intrVal) {
        amortToFile(balance, interestRate, terms);
    } else {
        printf("Please check your inputs and retry - invalid values.\n");
    }
}

int main() {
    getValues();
    return 0;
}
