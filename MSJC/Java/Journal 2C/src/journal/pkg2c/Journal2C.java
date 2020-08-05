/*
Daniel Meyer
0405182
10-25-14
Journal 2C
Swtich Statements
 */
package journal.pkg2c;

/**
 *
 * @author User
 */
import java.util.Scanner;

public class Journal2C 
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        int choice;
        double value1;
        double value2;
        
        System.out.println("Enter two values");
        value1 = in.nextDouble();
        value2 = in.nextDouble();
        
        System.out.println("Enter an operation");
        System.out.println("1. Add");
        System.out.println("2. Subtract");
        System.out.println("3. Multiply");
        System.out.println("4. Divide");
        
        choice = in.nextInt();
        switch(choice)
        {
            case 1:
                System.out.println("The sum is " + (value1 + value2));
                break;
            case 2:
                System.out.println("The difference is " + (value1 - value2));
                break;
            case 3:
                System.out.println("The product is " + (value1 * value2));
                break;
            case 4:
                System.out.println("The quotient is " + (value1 / value2));
                break;
            default:
                System.out.println("Invalid Operation");
        }
    } 
}
