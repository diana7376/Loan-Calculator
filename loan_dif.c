#include <stdio.h>
#include <math.h>

// display the menu interface
void displayMenu() {
    printf("+----------------------------------+\n");
    printf("|        Loan Calculator           |\n");
    printf("+----------------------------------+\n");
    printf("| 1. Enter loan parameters         |\n");
    printf("| 2. Calculate payment plan        |\n");
    printf("| 3. Display payment plan          |\n");
    printf("| 4. Display total amount paid     |\n");
    printf("| 5. Save payment plan to CSV file |\n");
    printf("| 6. Save payment plan to text file|\n");
    printf("| 7. Exit                          |\n");
    printf("+----------------------------------+\n");
}

int main() {
    double principal, interest_rate, payment, total_amount_paid = 0.0;
    int num_payments;
    int choice;

    // menu for interaction
    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // user input for loan parameters
                printf("\nEnter the principal amount: ");
                scanf("%lf", &principal);

                printf("Enter the annual interest rate (5 for 5%%): ");
                scanf("%lf", &interest_rate);

                printf("Enter the number of payments (120 for 10 years): ");
                scanf("%d", &num_payments); // Corrected this line

                // convert annual interest rate to monthly rate for calculation
                interest_rate /= 100.0; // percentage to decimal
                interest_rate /= 12.0;  // divide by 12 for monthly interest
                break;

            case 2:
                // calculate monthly payment using the loan payment formula (amortized loan)
                payment = (principal * interest_rate) / (1 - pow(1 + interest_rate, -num_payments));
                printf("\nMonthly payment calculated.\n");
                break;

            case 3:
                // display payment plan
                if (payment == 0) {
                    printf("\nPlease calculate the payment plan first.\n");
                    break;
                }
                printf("\nPayment Plan:\n");
                printf("  Month | Payment        | Interest       | Principal       | Balance\n");
                printf("-------+-----------------+-----------------+-----------------+--------\n");

                double remaining_balance = principal;
                for (int month = 1; month <= num_payments; month++) {
                    double interest_paid = remaining_balance * interest_rate;
                    double principal_paid = payment - interest_paid;
                    remaining_balance -= principal_paid;

                    printf("  %3d | %.2lf            | %.2lf            | %.2lf           | %.2lf\n",
                           month, payment, interest_paid, principal_paid, remaining_balance);

                    // total amount paid for each month
                    total_amount_paid += payment;
                }
                break;

            case 4:
                if (payment == 0) {
                    printf("\nPlease calculate the payment plan first.\n");
                    break;
                }
                printf("\nLoaned amount : %.2lf\n", principal);
                printf("Total amount paid: %.2lf\n", total_amount_paid);
                break;

            case 5:
                // save payment plan to CSV file
                if (payment == 0) {
                    printf("\nPlease calculate the payment plan first.\n");
                    break;
                }
                {
                    FILE *file = fopen("loan_data.csv", "w");
                    if (file != NULL) {
                        fprintf(file, "Month,Payment,Interest,Principal,Balance\n");

                        double remaining_balance = principal;
                        for (int month = 1; month <= num_payments; month++) {
                            double interest_paid = remaining_balance * interest_rate; // the interest paid for this month
                            double principal_paid = payment - interest_paid; // the principal paid for this month
                            remaining_balance -= principal_paid; // update the remaining balance by subtracting the principal paid

                            fprintf(file, "%d,%.2lf,%.2lf,%.2lf,%.2lf\n",
                                    month, payment, interest_paid, principal_paid, remaining_balance);

                            // total amount paid for each month
                            total_amount_paid += payment;
                        }
                        fclose(file);
                        printf("\nPayment plan saved to 'loan_data.csv'.\n");
                    } else {
                        printf("\nError opening file for writing.\n");
                    }
                }
                break;

            case 6:
                // save payment plan to text file
                if (payment == 0) {
                    printf("\nPlease calculate the payment plan first.\n");
                    break;
                }
                {
                    FILE *file = fopen("loan_data.txt", "w");
                    if (file != NULL) {
                        fprintf(file, "Payment Plan:\n");
                        fprintf(file, "Month | Payment | Interest | Principal | Balance\n");

                        double remaining_balance = principal;
                        for (int month = 1; month <= num_payments; month++) {
                            double interest_paid = remaining_balance * interest_rate; // the interest paid for this month
                            double principal_paid = payment - interest_paid; // the principal paid for this month
                            remaining_balance -= principal_paid; // update the remaining balance by subtracting the principal paid

                            fprintf(file, "%d | %.2lf | %.2lf | %.2lf | %.2lf\n",
                                    month, payment, interest_paid, principal_paid, remaining_balance);

                            // total amount paid for each month
                            total_amount_paid += payment;
                        }
                        fclose(file);
                        printf("\nPayment plan saved to 'loan_data.txt'.\n");
                    } else {
                        printf("\nError opening file for writing.\n");
                    }
                }
                break;

            case 7:
                printf("\nWe are waiting for you next time :)\n");
                printf("\nExiting...\n");
                return 0;

            default:
                printf("\nInvalid choice. Please enter a valid option.\n");
                break;
        }
    }

    return 0;
}
