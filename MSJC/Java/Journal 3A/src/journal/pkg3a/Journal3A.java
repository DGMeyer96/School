/*
Daniel Meyer
0405182
11-1-14
Journal 3C
For Loops
 */
package journal.pkg3a;

/**
 *
 * @author User
 */
import java.util.Scanner;
public class Journal3A 
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        /*
        int count;
        System.out.println("How many numbers do you want to enter?");
        count = in.nextInt();
        
        int num;
        int sum = 0;
        
        for(int i = 0; i < count; i++)
        {
            System.out.println("Enter a number");
            num = in.nextInt();
            sum+=num;
        }
        System.out.println("The sum of the numbers is " + sum);
        */
        
        for(int row = 0; row < 10; row++)
        {
            for(int col = 0; col < 10; col++)
            {
                System.out.print(row * col + "\t");
            }
            System.out.print("\n");
        }
    }
    
}
