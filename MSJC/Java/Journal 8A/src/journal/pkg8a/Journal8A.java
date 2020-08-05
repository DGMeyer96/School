/*
Daniel Meyer
0405182
12-11-14
Journal 8A
Creating Classes
 */
package journal.pkg8a;

import java.util.Random;
import java.util.Scanner;

public class Journal8A 
{

    
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        
        Rectangle r1 = new Rectangle();
        Rectangle r2 = new Rectangle();
        
        Box b1 = new Box();
        Box b2 = new Box();
        
        r1.setRectangle(4,3);
        r2.setRectangle(6,5);
        
        b1.setBox(4,3,2);
        b2.setBox(6,5,7);
        
        System.out.println("The area of r1 is " + r1.area());
        System.out.println("The area of r2 is " + r2.area());
        
        System.out.println("The area of b1 is " + b1.areaBox());
        System.out.println("The area of b2 is " + b2.areaBox());
    }
    
}
