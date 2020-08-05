/*
Daniel Meyer
0405182
11-6-14
Journal 4B
Value Producing Methods
 */
package journal.pkg4b;

import java.util.Scanner;
import java.text.NumberFormat;
public class Journal4B 
{
    Scanner in = new Scanner(System.in);
    
    public int getEvenValue()
    {
        System.out.println("Enter a number");
        int val;
        val = in.nextInt();
        while(val % 2 != 0)
        {
            System.out.println("Enter a number");
            val = in.nextInt(); 
        }
        return val;
    }
    
    public static void main(String[] args) 
    {
        Journal4B c = new Journal4B();
        int x = c.getEvenValue();
        System.out.println(x + " is an even number");
    }
    
}
