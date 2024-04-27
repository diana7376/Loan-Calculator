import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;

public class LoanCalc {
    public static void main(String[] args) throws IOException {
        // reads bytes and decodes into characters
        InputStreamReader reader = new InputStreamReader(System.in, StandardCharsets.UTF_8);
        // reads text from character-input stream
        BufferedReader in = new BufferedReader(reader);

        // ----------------------- Prompting user for input ----------------------------
        double loan;
        do{
            System.out.println("Loan amount: ");
            String loanAmount = in.readLine();
            loan = Double.parseDouble(loanAmount);
            if(loan <= 99){
                System.out.println("Loan amount must be greater than $99\n");
            }
        }while(loan <= 99);

        int term;
        do{
            System.out.println("Loan term in years: ");
            String termInYears = in.readLine();
            term = Integer.parseInt(termInYears);
            if(term <= 0){
                System.out.println("Loan term must be at least one year\n");
            }
            else if(term > 50){
                System.out.println("Loan term cannot exceed 50 years\n");
            }
        }while(term <=0 || term > 50);       

        double rate;
        do{
            System.out.println("Interest rate per year: ");
            String annualRate = in.readLine();
            rate = Double.parseDouble(annualRate);
            if(rate < 0){
                System.out.println("Interest rate cannot be negative\n");
            }            
        }while(rate < 0);

        double downPay;
        do{
            System.out.println("Downpayment: ");
            String downPayment = in.readLine();
            downPay = Double.parseDouble(downPayment);
            if(downPay < 0){
                System.out.println("Downpayment cannot be negative, but can be $0\n");
            }
            else if(downPay>=loan){
                System.out.println("Downpayment cannot equal or exceed your loan amount\n");
            }
        }while(downPay < 0 || downPay >= loan);
        System.out.println();
        // ------------------------ End Prompting User ---------------------------------
        
        // Call functions
        double monthlyPayment = calculateMonthlyPayment(loan, term, rate, downPay);
        double totalInterestAccrued = calculateInterestAccrued(monthlyPayment, loan, downPay, term);
        
        // Print Results
        System.out.println("Monthly Payments: ");
        System.out.print("$");
        System.out.printf("%.2f", monthlyPayment);
        System.out.println();
        System.out.println("Total Accrued Interest: ");
        System.out.println("$" + (int)Math.round(totalInterestAccrued));
    }
    /**
    Returns monthly payment amount on a loan.
    @param  loan      Loan amount
    @param  term      Loan term in years
    @param  rate      Interest rate per year on a loan
    @param  downPay   Downpayment on a loan
    @return           Monthly payment on a loan
    */
    public static double calculateMonthlyPayment(double loan, int term, double rate, double downPay )
    {
        double monthlyRate = (rate/100.0) / 12;
        int termsInMonths = term * 12;
        loan -= downPay;
        double monthlyPayment = (monthlyRate * loan)/(1-Math.pow((1+monthlyRate), -termsInMonths));
        return monthlyPayment;
    }

    /**
    Returns total interest accrued for the period of a loan.
    @param  loan             Loan amount
    @param  term             Loan term in years
    @param  downPay          Downpayment on a loan
    @param  monthlyPayment   Monthly payment on a loan
    @return                  Total interest accrued
    */    
    public static double calculateInterestAccrued(double monthlyPayment, double loan, double downPay, int term)
    {
        int termsInMonths = term * 12;
        loan -= downPay;
        double totalCost = monthlyPayment * termsInMonths;
        double totalInterestAccrued = totalCost - loan;
        return totalInterestAccrued;
    }
    
}