/*
Daniel Meyer
0405182
10-17-14
Assignment 2 - Console Input
 */
package assignment.pkg2;

/**
 *
 * @author User
 */
import java.util.Scanner;

public class Assignment2 
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        
        double myDbl;
        double anotherDbl;
        int myInt;
        
        System.out.println("Enter two doubles and an int.");
        
        myDbl = in.nextInt();
        anotherDbl = in.nextInt();
        myInt = in.nextInt();
        
        System.out.println("Here are you numbers modified");
        
        System.out.println(myDbl + 1);
        System.out.println(anotherDbl - 2);
        System.out.println(myInt - 1);
        
    }
    
}
