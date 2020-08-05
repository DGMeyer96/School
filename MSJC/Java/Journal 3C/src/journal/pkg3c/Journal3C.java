/*
Daniel Meyer
0405182
11-1-14
Journal 3C
While Loops
 */
package journal.pkg3c;

/**
 *
 * @author User
 */
import java.util.Scanner;
import java.util.Random;
public class Journal3C 
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        /*
        Scanner in = new Scanner(System.in);
        Random rdm = new Random();
        
        
        System.out.println("Do you want to play? (y/n)");
        String answer = in.nextLine();
        
        while(answer.equals("y"));
        {
            System.out.println("Guess a number between 1 and 10");
            int count = 1;
            int guess = in.nextInt();
            int num = rdm.nextInt(10) + 1;

            while(guess != num)
            {
                System.out.println("Guess a number between 1 and 10");
                guess = in.nextInt();
                count++;
            }
            System.out.println("It took " + count + " guesses to guess correctly");
            System.out.println("Do you want to play again? (y/n)");
            answer = in.nextLine();
            
        }
        */
        
        Scanner in = new Scanner(System.in);
        Random rdm = new Random();
        
        System.out.println("Do you want to play? (y/n)");
        String answer = in.nextLine();
        
        while(answer.equals("y"))
        {
            System.out.println("Guess a number between 1 and 10");
            int count = 1;
            int guess = in.nextInt();
            int num = rdm.nextInt(10) + 1;
            
            while(guess != num)
            {
                System.out.println("Guess a number between 1 and 10");
                guess = in.nextInt();
                count++;
            //System.out.println("It took " + count + " guesses to guess correctly");
            }
            System.out.println("It took " + count + " guesses to guess correctly");
            
            System.out.println("Do you want to play again? (y/n)");
            answer = in.nextLine();
        }
    }
}
