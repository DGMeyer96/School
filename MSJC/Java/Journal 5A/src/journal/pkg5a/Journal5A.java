/*
Daniel Meyer
0405182
11-20-14
Journal 5A
Single Dimmensional Arrays
 */
package journal.pkg5a;

import javax.swing.*;
import java.util.Scanner;
import java.util.Random;
public class Journal5A 
{

    public int[] createArray(int size)
    {
        int[] array = new int[size];
        Random rdm = new Random();
        for(int i = 0; i < array.length; i++)
            array[i] = rdm.nextInt(101);
        return array;
    }
    
    public int[] printArray(int[] array)
    {
        for(int i = 0; i < array.length; i++)
            System.out.println(array[i]);
        return array;
    }
    
    public int[] div10(int[] array)
    {
        int count = 0;
        for(int i = 0; i < array.length; i++)
        {
            if(array[i] % 10 == 0)
            {
                count++;
            }
        }
        System.out.println("There are " + count + " number(s) divisible by 10.");
        return array;
    }
    
    public static void main(String[] args) 
    {
        Journal5A con = new Journal5A();
        int[] myArray; 
        myArray = con.createArray(10);
        con.printArray(myArray);
        con.div10(myArray);
    }
    
}
