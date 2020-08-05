/*
Daniel Meyer
0405182
11-21-14
Assignment 13
Arrays as Arguments
 */
package assignment.pkg13;

import java.util.Scanner;
import java.util.Random;

public class Assignment13 
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
    
     public int[] countEvens(int[] array)
    {
        int count = 0;
        for(int i = 0; i < array.length; i++)
        {
            if(array[i] % 2 == 0)
            {
                count++;
            }
        }
        System.out.println("There are " + count + " even number(s).");
        return array;
    }
    
    public static void main(String[] args) 
    {
        Assignment13 con = new Assignment13();
        int[] myArray; 
        myArray = con.createArray(25);
        con.printArray(myArray);
        con.countEvens(myArray);
    }
    
}
