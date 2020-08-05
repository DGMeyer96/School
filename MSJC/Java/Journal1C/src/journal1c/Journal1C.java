/*
Daniel Meyer
0405182
10-17-14
Journal 1C
Math Operators
 */
package journal1c;

/**
 *
 * @author User
 */
import java.util.Scanner;

public class Journal1C 
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        
        int nickels;
        
        System.out.println("Enter your Nickels.");
        nickels = in.nextInt();
        
        int dollars = nickels / 20;
        int change = nickels % 20;
        
        System.out.println("You have $" + dollars + "." + change);
    }
    
}
