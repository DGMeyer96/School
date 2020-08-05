/*
Daniel Meyer
0405182
10-25-14
Assignment 4
Making Descisions
 */
package assignment.pkg4;

/**
 *
 * @author User
 */
import java.util.Scanner;
import java.text.NumberFormat;

public class Assignment4 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        
        double mileage;
        double price;
        double mileageRate;   
        
        System.out.println("Enter the number of miles driven");
        mileage = in.nextDouble();   
        
        if (mileage <= 100)
        {
            mileageRate = .25 * mileage;
        }
        else 
        {    
            mileageRate = .15 * (mileage % 100) + (.25 * 100);
        }
        price = mileageRate;
        NumberFormat fmt = NumberFormat.getCurrencyInstance();
        System.out.println("You are owed " + fmt.format(price));
    }
    
}
