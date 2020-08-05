/*
Daniel Meyer
0405182
10-18-14
Assignment 2
Simple Math
 */
package assignment.pkg3;

/**
 *
 * @author User
 */
import java.util.Scanner;
import java.text.NumberFormat;

public class Assignment3 
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        NumberFormat fmt = NumberFormat.getCurrencyInstance();
        
        int pennies;
        int nickels;
        int dimes;
        int quarters;
        int change;
        
        System.out.println("Enter pennies, nickels, dimes, and quarters.");
        pennies = in.nextInt();
        nickels = in.nextInt();
        dimes = in.nextInt();
        quarters = in.nextInt();
        
        float dollars = pennies / 100F + nickels / 20 + dimes / 10 + quarters / 4;
        
        String strDollars = fmt.format(dollars);
        System.out.println("You have " + strDollars);
    }
    
}
