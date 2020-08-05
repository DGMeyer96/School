/*
Daniel Meyer
0405182
11-22-14
Journal 5B
2D Arrays
 */
package journal.pkg5b;

import java.util.Scanner;
import java.util.Random;

public class Journal5B 
{

    public int[][] createArray(int rSize, int cSize)
    {
        Random rdm = new Random();
        int[][] array = new int[rSize][cSize];
        for(int row = 0; row < array.length; row++)
        {
            for(int col = 0; col < array[0].length; col++)
            {
                array[row][col] = rdm.nextInt(26);
            }
        }
        return array;
    }
    
    public void print2DArray(int[][] array)
    {
        for(int row = 0; row < array.length; row++)
        {
            for(int col = 0; col < array[0].length; col++)
            {
                System.out.print(array[row][col] + "\t");
            }
            System.out.println("\n");
        }
    }
    
    public int countInstance(int[][] array, int search)
    {
        int count = 0;
        for(int row = 0; row < array.length; row++)
        {
            for(int col = 0; col < array[0].length; col++)
            {
                if(array[row][col] == search)
                {
                    count++;
                    System.out.println(array[search]);
                }  
            }
        }
        return count;
    }
    
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        Journal5B con = new Journal5B();
        
        int[][] myArray;
        myArray = con.createArray(10,10);      
        con.print2DArray(myArray);
        System.out.println("Enter a number to search for.");
        int value = in.nextInt();
        System.out.println("Your number occured " + con.countInstance(myArray, value) + " times.");
    }
}
