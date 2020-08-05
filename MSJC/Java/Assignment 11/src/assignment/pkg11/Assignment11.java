/*
Daniel Meyer
0405182
11-7-14
Assignment 11
Methods, Loops, and Descisions
 */
package assignment.pkg11;

import java.util.Scanner;
public class Assignment11 
{

    public int sumConsonants(char c, char d)
    {
        if(Character.isUpperCase(c & d))
        {
            if((c & d) != 'A' || c != 'E' || c != 'I' || c != 'O' || c != 'U')
            {
                int x = (int)c;
                int y = (int)d;
                int sum = x + y;
                return sum;
            }
            else
                return -1;
        }
        else
            return -1;
        
    }
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        Assignment11 con = new Assignment11();
        
        System.out.println("Enter two uppercase letters.");
        char a;
        char b;
        String s = in.nextLine();
        a = s.charAt(0);
        b = s.charAt(1);
        
        int sum = con.sumConsonants(a,b);
        System.out.println("The sum of the consonants is " + sum);
    }
    
}
