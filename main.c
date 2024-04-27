#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculateMonthlyPayment(double loan, int term, double rate, double downPay);
double calculateInterestAccrued(double monthlyPayment, double loan, double downPay, int term);

int main() {
    double loan;
    do {
        printf("Loan amount: ");
        scanf("%lf", &loan);
        if (loan <= 99) {
            printf("Loan amount must be greater than $99\n");
        }
    } while (loan <= 99);

    int term;
    do {
        printf("Loan term in years: ");
        scanf("%d", &term);
        if (term <= 0) {
            printf("Loan term must be at least one year\n");
        } else if (term > 50) {
            printf("Loan term cannot exceed 50 years\n");
        }
    } while (term <= 0 || term > 50);

    double rate;
    do {
        printf("Interest rate per year: ");
        scanf("%lf", &rate);
        if (rate < 0) {
            printf("Interest rate cannot be negative\n");
        }
    } while (rate < 0);

    double downPay;
    do {
        printf("Downpayment: ");
        scanf("%lf", &downPay);
        if (downPay < 0) {
            printf("Downpayment cannot be negative, but can be $0\n");
        } else if (downPay >= loan) {
            printf("Downpayment cannot equal or exceed your loan amount\n");
        }
    } while (downPay < 0 || downPay >= loan);
    printf("\n");

    double monthlyPayment = calculateMonthlyPayment(loan, term, rate, downPay);
    double totalInterestAccrued = calculateInterestAccrued(monthlyPayment, loan, downPay, term);

    printf("Monthly Payments: $\n");
    printf("%.2f\n", monthlyPayment);
    printf("Total Accrued Interest: $\n");
    printf("%d\n", (int)round(totalInterestAccrued));

    return 0;
}

double calculateMonthlyPayment(double loan, int term, double rate, double downPay) {
    double monthlyRate = (rate / 100.0) / 12;
    int termsInMonths = term * 12;
    loan -= downPay;
    double monthlyPayment = (monthlyRate * loan) / (1 - pow((1 + monthlyRate), -termsInMonths));
    return monthlyPayment;
}

double calculateInterestAccrued(double monthlyPayment, double loan, double downPay, int term) {
    int termsInMonths = term * 12;
    loan -= downPay;
    double totalCost = monthlyPayment * termsInMonths;
    double totalInterestAccrued = totalCost - loan;
    return totalInterestAccrued;
}


