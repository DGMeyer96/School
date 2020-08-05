/*
Daniel Meyer
0405182
12-11-14
Journal 8B
Constructors
 */
package journal.pkg8c;

import java.util.Random;
import java.util.Scanner;

public class Journal8C 
{

    
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        Random rdm = new Random();
        
        Double dbl[] = new Double[10];
        
        for(int i = 0; i < dbl.length; i++)
        {
            dbl[i] = rdm.nextDouble();
            System.out.println(dbl[i].toString());
        }

    }
    
}