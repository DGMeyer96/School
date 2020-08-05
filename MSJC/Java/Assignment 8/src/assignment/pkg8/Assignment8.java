/*
Daniel Meyer
0405182
11-1-14
Assignment 8
The while Loop
 */
package assignment.pkg8;

/**
 *
 * @author User
 */
import java.util.Scanner;
import java.util.Random;
public class Assignment8 
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        Random rdm = new Random();
        
        System.out.println("I am thinking of a number between 1 and 10 \nCan you guess it?");
        int count = 1;
        int score = 10;
        int num = rdm.nextInt(10) + 1;
        int guess = in.nextInt();
        
        if(guess > 10)
            System.out.println("Must be a number between 1 and 10 \nTry Again");
        
        while(guess != num)
        {
            System.out.println("Sorry, wrong guess \nTry Again");
            guess = in.nextInt();
            score = score - 2;
            count++;
        }
        System.out.println("It took you " + count + " guesses to guess " + num + "\n You have " + score + " points");
    }
    
}
