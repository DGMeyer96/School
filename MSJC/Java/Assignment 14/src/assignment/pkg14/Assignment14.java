/*
Daniel Meyer
0405182
11-22-14
Assignment 14
Two Dimmensional Arrays
 */
package assignment.pkg14;

import java.util.Scanner;
import java.util.Random;
public class Assignment14 
{

    public int[][] create2DArray(int rSize, int cSize)
    {
        Random rdm = new Random();
        int[][] array = new int[rSize][cSize];
        for(int row = 0; row < array.length; row++)
        {
            for(int col = 0; col < array[0].length; col++)
            {
                array[row][col] = rdm.nextInt(101);
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
    
    public int[][] createCoords(int[][] array)
    {
        for(int row = 0; row < array.length; row++)
        {
            for(int col = 0; col < array[0].length; col++)
            {
                if(array[row][col] % 3 == 0)
                        {
                            array[row][col] = -1;
                        }
            }
        }
        return array;
    }
    
    public void fillLocations(int[][] array)
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
  
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        Assignment14 con = new Assignment14();
        
        int[][] myArray;
        myArray = con.create2DArray(10,10);      
        con.print2DArray(myArray);
        con.createCoords(myArray);
        System.out.println("****************************************************");
        System.out.println("\n****************************************************");        
        con.fillLocations(myArray);
    }
    
}
