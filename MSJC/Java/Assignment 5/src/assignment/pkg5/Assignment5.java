/*
Daniel Meyer
0405182
10-25-14
Assignment 5
The Conditional Operator
 */
package assignment.pkg5;

/**
 *
 * @author User
 */
import java.util.Scanner;
import java.text.NumberFormat;

public class Assignment5 
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        NumberFormat fmt = NumberFormat.getCurrencyInstance();
        
        double mileage;
        double price;
        
        System.out.println("Enter the number of miles driven");
        mileage = in.nextDouble();
        
        price = mileage <= 100 ? .25 * mileage : .15 * (mileage % 100) + (.25 * 100); 
                
        System.out.println("You are owed " + fmt.format(price));
    }
    
}
