/*
Daniel Meyer
0405182
11-6-14
Journal 4C
Parameter Methods
 */
package journal.pkg4c;

import java.util.Scanner;
import java.text.NumberFormat;
public class Journal4C 
{
    Scanner in = new Scanner(System.in);
    
    public int getValue()
    {
        System.out.println("Enter a number");
        int val;
        val = in.nextInt();
        return val;
    }
    
    public int sumIt(int num)
    {
        return num + num;
    }
    
    public int cubeIt(int num)
    {
        return this.sumIt(num*num*num);
    }
    
    public static void main(String[] args) 
    {
        Journal4C c = new Journal4C();
        int x = c.getValue();
        int y = c.getValue();
        
        System.out.println("The value you entered is " + x);
        
        int sum = c.sumIt(x);
        System.out.println("The sum of " + x + " is " + sum);
        
        int cube = c.cubeIt(x);
        System.out.println("The cube of " + x + " is " + cube);
    }
    
}
