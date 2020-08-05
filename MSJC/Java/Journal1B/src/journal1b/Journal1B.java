/*
Daniel Meyer
0405182
10-17-14
Journal 1B
Console Input
 */
package journal1b;

/**
 *
 * @author User
 */
import java.util.Scanner;

public class Journal1B
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        int num1, num2;
        System.out.println("Enter 2 values ");
        
        num1 = in.nextInt();
        num2 = in.nextInt();
        
        int sum = num1 + num2;
        int difference = num1 - num2;
        int product = num1 * num2;
        int quotient = num1 / num2;
        
        System.out.println("The sum is " + sum); //can also use (num1 + num2) instead of sum.
        System.out.println("The difference is " + difference);
        System.out.println("The product is " + product);
        System.out.println("The quotient is " + quotient);
    }
    
}
