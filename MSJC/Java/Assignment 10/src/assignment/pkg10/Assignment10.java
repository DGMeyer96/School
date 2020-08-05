/*
Daniel Meyer
0405182
11-6-14
Assignment 10
Methods
 */
package assignment.pkg10;

import java.util.Scanner;
import java.text.NumberFormat;
public class Assignment10 
{
    Scanner in = new Scanner(System.in);
    
    public double rad2deg(double radians)
    {
        double degrees;
        degrees = radians * 180 / Math.PI;
        return degrees;
    }
    
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        Assignment10 con = new Assignment10();
        
        double theSin;
        double sinDeg;
        double theCos;
        double cosDeg;
        double theTan;
        double tanDeg;
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
  
            switch(Character.toUpperCase(operation))
            {
                case 'S':
                    theSin = Math.sin(dValue);
                    sinDeg = con.rad2deg(theSin);
                    System.out.println("The sine of your number is " + theSin);
                    System.out.println("The sine of your number in degrees is " + sinDeg);
                    break;
                case 'C':
                    theCos = Math.cos(dValue);
                    cosDeg = con.rad2deg(theCos);
                    System.out.println("The cosine of your number is " + theCos);
                    System.out.println("The sine of your number in degrees is " + cosDeg);
                    break;
                case 'T':
                    theTan = Math.tan(dValue);
                    tanDeg = con.rad2deg(theTan);
                    System.out.println("The tangent of your number is " + theTan);
                    System.out.println("The sine of your number in degrees is " + tanDeg);
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
            
    }
    
}
