/*
Daniel Meyer
0405182
12-11-14
Journal 8B
Constructors
 */
package journal.pkg8b;

import java.util.Random;
import java.util.Scanner;

public class Journal8B 
{

    
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        
        Rectangle r1 = new Rectangle(4,3);
        Rectangle r2 = new Rectangle(6,5);
        
        System.out.println("The area of r1 is " + r1.area());
        System.out.println("The area of r2 is " + r2.area());
    }
    
}
