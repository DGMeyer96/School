/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package test;

import java.util.Random;
import java.util.Scanner;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Test extends JFrame implements ActionListener
{
    /*
    public int[] createArray(int size)
    {
        Random r = new Random();
        int[] ar = new int[size];

        for(int i = 0; i < size; i++)
            ar[i] = r.nextInt(100) + 1;
        return ar;
    }
    
    public void findLargest(int[] ar)
    {
        for(int i = 0; i < ar.length; i++)
        {
            if(ar[i] > ar[0])
                ar[0] = ar[i];
        }
        //return ar[0];
        System.out.println("The largest number is " + ar[0]);
    }
    */
    
    /*
    public int[] createEvens(int size)
    {
        Random r = new Random();
        int[] num = new int[size];
        
        for(int i = 0; i < size; i++)
        {
            num[i] = r.nextInt(101);
        }
        return num;
    }
    
    public void evenSums(int[] num)
    {
        int sum = 0;
        for(int i = 0; i < num.length; i++)
        {
            if(num[i] % 2 == 0)
                sum = sum + num[i];
        }
        System.out.println("The sum of the even numbers is " + sum);
    }
    */
    
    Container content = this.getContentPane();
    
    JButton btnRed = new JButton("Red");
    JButton btnGreen = new JButton("Green");
    JButton btnBlue = new JButton("Blue");
    
    public Test()
    {
        this.setVisible(true);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setSize(400,300);
        this.setTitle("Exam 4 Question 3");
        
        content.setLayout(new GridLayout(1,3, 20,20));
        
        btnRed.addActionListener(this);
        btnGreen.addActionListener(this);
        btnBlue.addActionListener(this);
        
        content.add(btnRed);
        content.add(btnGreen);
        content.add(btnBlue);
    }
        
    public void actionPerformed(ActionEvent ae) 
    {
        Object src = ae.getSource();
        if(src == btnRed)
            content.setBackground(Color.red);
        else if(src == btnGreen)
            content.setBackground(Color.green);
        else if(src == btnBlue)
            content.setBackground(Color.blue);
    }
    
    public static void main(String[] args) 
    {
        /*
        Test con = new Test();
        Scanner in = new Scanner(System.in);
        System.out.println("Enter how many numbers to generate.");
        int size = in.nextInt();
        con.findLargest(con.createArray(size));
        */
        
        /*
        Test con = new Test();
        Scanner in = new Scanner(System.in);
        System.out.println("Enter how many numbers to generate.");
        int size = in.nextInt();
        con.evenSums(con.createEvens(size));
        */
        
        Test gui = new Test();
    }
    
}
