#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool validateInputs(double value) {
    if (value <= 0) {
        return false;
    } else {
        return true;
    }
}

char* amort(double balance, double interestRate, int terms) {
    static char result[10000];
    double monthlyRate = interestRate / 12;
    double payment = balance * (monthlyRate / (1 - pow(1 + monthlyRate, -terms)));
    int result_length = 0;

    result_length += sprintf(result + result_length, "Loan amount: $%.2f\n", balance);
    result_length += sprintf(result + result_length, "Interest rate: %.2f%%\n", interestRate * 100);
    result_length += sprintf(result + result_length, "Number of months: %d\n", terms);
    result_length += sprintf(result + result_length, "Monthly payment: $%.2f\n", payment);
    result_length += sprintf(result + result_length, "Total paid: $%.2f\n\n", payment * terms);

    result_length += sprintf(result + result_length, "Month #\tBalance\t\tInterest\tPrincipal\n");

    for (int count = 0; count < terms; ++count) {
        double interest = balance * monthlyRate;
        double monthlyPrincipal = payment - interest;
        balance -= monthlyPrincipal;

        result_length += sprintf(result + result_length, "%d\t$%.2f\t$%.2f\t$%.2f\n",
                                 count + 1, balance, interest, monthlyPrincipal);
    }

    return result;
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
        printf("%s", amort(balance, interestRate, terms));
    } else {
        printf("Please check your inputs and retry - invalid values.\n");
    }
}

int main() {
    getValues();
    return 0;
}
