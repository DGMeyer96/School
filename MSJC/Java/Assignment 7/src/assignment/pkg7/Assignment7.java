/*
Daniel Meyer
0405182
11-1-14
Assignment 7
The for Loop
 */
package assignment.pkg7;

/**
 *
 * @author User
 */
import java.util.Scanner;
public class Assignment7 
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        System.out.println("Please enter a number");
        int num = in.nextInt();
        
        for(int col1 = 1; col1 <= num; col1++)
        {
            for(int col2 = 1; col2 <= num; col2++)
            {
                if(col1 <= col2)
                    System.out.print(col1 + "," + col2 + "\n");
            }
        }
    }
    
}
