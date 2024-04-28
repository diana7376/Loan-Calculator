#include <stdio.h>

int main() {
    double principal, interest_rate, payment, total_amount_paid = 0.0;
    int num_payments;

    // Get user input for loan parameters
    printf("Enter the principal amount (e.g., 10000): ");
    scanf("%lf", &principal);

    printf("Enter the annual interest rate (e.g., 5 for 5%%): ");
    scanf("%lf", &interest_rate);

    // Convert annual interest rate to monthly rate for calculation
    interest_rate /= 100.0; // Convert percentage to decimal
    interest_rate /= 12.0;  // Divide by 12 for monthly interest

    printf("Enter the number of payments (e.g., 120 for 10 years): ");
    scanf("%d", &num_payments);

    // Calculate monthly payment using the loan payment formula
    payment = (principal * interest_rate) / (1 - pow(1 + interest_rate, -num_payments));

    // Display loan summary
    printf("\nLoan Summary:\n");
    printf("  Principal amount:  %.2lf\n", principal);
    printf("  Interest rate:     %.2f%% per month\n", interest_rate * 100);
    printf("  Number of payments: %d\n", num_payments);
    printf("  Monthly payment:   %.2lf\n\n", payment);

    // Display detailed payment plan
    printf("Payment Plan:\n");
    printf("  Month | Payment        | Interest       | Principal       | Balance\n");
    printf("-------+-----------------+-----------------+-----------------+--------\n");

    double remaining_balance = principal;
    for (int month = 1; month <= num_payments; month++) {
        double interest_paid = remaining_balance * interest_rate;
        double principal_paid = payment - interest_paid;
        remaining_balance -= principal_paid;

        printf("  %3d | %.2lf            | %.2lf            | %.2lf           | %.2lf\n",
               month, payment, interest_paid, principal_paid, remaining_balance);

        // Track total amount paid for each month
        total_amount_paid += payment;
    }

    // Display total amount paid after the payment plan
    printf("Loaned amount : %.2lf", principal);
    printf("\nTotal amount paid: %.2lf\n", total_amount_paid);

    return 0;
}
