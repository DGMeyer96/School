/*
Daniel Meyer
0405182
11-1-14
Assignment 9
Primed Loops & Some Parsing
 */
package assignment.pkg9;

/**
 *
 * @author User
 */
import java.util.Scanner;
public class Assignment9 
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);

        double theSin;
        double theCos;
        double theTan;
        double theSqrt;
        double theLog;
        
        System.out.println("This calculator requires you to enter a function and a number");
        System.out.println("The functions are as follows:");
        System.out.println("S - sine");
        System.out.println("C - cosine");
        System.out.println("T - tangent");
        System.out.println("R - square root");
        System.out.println("N - natural log");
        System.out.println("X - eXit the program\n");
        System.out.println("Please enter a function, then a value");
        String input = in.nextLine();
        
        char operation = input.charAt(0);
        String sValue = input.substring(2);
        double dValue = Double.parseDouble(sValue);
        
        while(Character.toUpperCase(operation)!= 'X');
        {
            switch(Character.toUpperCase(operation))
            {
                case 'S':
                    theSin = Math.sin(dValue);
                    System.out.println("The sine of your number is " + theSin);
                    break;
                case 'C':
                    theCos = Math.cos(dValue);
                    System.out.println("The cosine of your number is " + theCos);
                    break;
                case 'T':
                    theTan = Math.tan(dValue);
                    System.out.println("The tangent of your number is " + theTan);
                    break;
                case 'R':
                    theSqrt = Math.sqrt(dValue);
                    System.out.println("The square root of your number is " + theSqrt);
                    break;
                case 'N':
                    theLog = Math.log(dValue);
                    System.out.println("The natural log of your number is " + theLog);
                    break;
                case 'X':
                    System.out.println("Thanks for using the calculator");
                    break;
                default:
                System.out.println("Invalid Input");
            }
      
            System.out.println("This calculator requires you to enter a function and a number");
            System.out.println("The functions are as follows:");
            System.out.println("S - sine");
            System.out.println("C - cosine");
            System.out.println("T - tangent");
            System.out.println("R - square root");
            System.out.println("N - natural log");
            System.out.println("X - eXit the program\n");
            System.out.println("Please enter a function, then a value");
            input = in.nextLine();
        
            operation = input.charAt(0);
            sValue = input.substring(2);
            dValue = Double.parseDouble(sValue);
        }
    }
    
}
