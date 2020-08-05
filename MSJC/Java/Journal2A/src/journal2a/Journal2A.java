/*
Daniel Meyer
0405182
10-24-14
Journal 2A
The Boolean Type
 */
package journal2a;

/**
 *
 * @author User
 */
import java.util.Scanner;

public class Journal2A 
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        
        int x, y;
        
        System.out.println("Enter 2 values");
        x = in.nextInt();
        y = in.nextInt();
        
        boolean truth = x > y;
        if(truth)
            System.out.println(x + " is the smaller number.");
        else
            System.out.println(y + " is the smaller number.");
        if(truth != true)
            System.out.println(x + " is less than " + y);
        else
            System.out.println(x + " is greater than " + y);
        
    }
    
}
