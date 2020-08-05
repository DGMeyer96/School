/*
Daniel Meyer
0405182
11-8-14
Assignment 12
Method Overloading
 */
package assignment.pkg12;

import java.util.Scanner;
public class Assignment12 
{

    public int sumNumber(int num1)
    {
        int sum = 0;
        while(num1 > 0)
        {
            sum+= num1 % 10;
            num1 = num1 / 10;
        }
        return sum;
    }

    public int sumNumber(int num1, int num2)
    {
        int sum = 0;
        while(num1 > 0 & num2 > 0)
        {
            sum+= (num1 % 10) + (num2 % 10);
            num1 = num1 / 10;
            num2 = num2 / 10;
        }
        return sum;
    }
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        Assignment12 con = new Assignment12();
        
        System.out.println("Enter two three digit numbers.");
        int set1 = in.nextInt();
        int set2 = in.nextInt();
        
        int sum = con.sumNumber(set1,set2);
        System.out.println("The sum of the digits is " + sum);
    }
    
}
