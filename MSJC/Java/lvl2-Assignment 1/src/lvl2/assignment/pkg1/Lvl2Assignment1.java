/*
Daniel Meyer
0405182
8-20-15
Assignment 1
Console Application
 */
package lvl2.assignment.pkg1;

import java.util.Scanner;

public class Lvl2Assignment1 
{
    public int sumNums(int input)
    {
        int sum = 0;
        
        while(input != 0)
        {
            sum += input % 10;
            input /= 10;
        }
        
        return sum;
    }
    
    public String reverseNums(int input)
    {
        StringBuffer sb = new StringBuffer("");
        
        int rev = 0;
        
        while(input != 0)
        {
            rev = input % 10; //<---- reverse order
            input /= 10;
            sb.insert(0, rev);
        }
        
        return sb.reverse().toString();
    }
    
    public int[] getArray(int input)
    {
        int[] array = new int[3];
        
        String digits = Integer.toString(input);
        
        for(int i = 0; i < 3; i++)
        {
            int x = (int)digits.charAt(i) - 48;
            
            array[i] = x;
        }
        
        return array;
    }
    
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        Lvl2Assignment1 con = new Lvl2Assignment1();
                
        int input;
        
        System.out.println("Enter a 3-digit number");
        input = in.nextInt();
        
        System.out.println("The sum of the digits is " + con.sumNums(input));
        System.out.println("In reverse the digits are " + con.reverseNums(input));
        System.out.println("Printing Array ");
        int arr[] = con.getArray(input);
        
        for(int i = 0; i < 3; i++)
        {
            System.out.println(arr[i]);
        }
    }
    
}
