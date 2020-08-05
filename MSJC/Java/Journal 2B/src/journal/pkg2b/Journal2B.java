/*
Daniel Meyer
0405182
10-25-14
Journal 2B
If Statements
 */
package journal.pkg2b;

/**
 *
 * @author User
 */
import java.util.Scanner;

public class Journal2B 
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        int score = 0;
        
        System.out.println("Enter your score");
        score = in.nextInt();
        if(score >= 89 && score <= 100)
        {
            System.out.println("You got an A");
        }
        else if (score >= 80)
        {
            System.out.println("You got a B");
        }
        else if (score >= 70)
        {
            System.out.println("You got a C");
        }
        else if (score >= 60)
        {
            System.out.println("You got a D");
        }
        else
            System.out.println("You got a F");
    }
    
}
