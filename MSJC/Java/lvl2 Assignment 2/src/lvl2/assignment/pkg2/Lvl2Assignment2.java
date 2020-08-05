/*
Daniel Meyer
0405182
8-30-15
Assignment 2/3
GUI Application and Inner Class
 */
package lvl2.assignment.pkg2;

import java.util.Scanner;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Lvl2Assignment2 extends JFrame
{
    
    Container content = this.getContentPane();
    boolean toggle = false;
    
    JLabel lblInput = new JLabel();
    JLabel lblSum = new JLabel();
    JLabel lblSumNums = new JLabel();
    JLabel lblReverse = new JLabel();
    JLabel lblReverseNums = new JLabel();
    JLabel lblArray = new JLabel();
    JLabel lblArray1 = new JLabel();
    JLabel lblArray2 = new JLabel();
    JLabel lblArray3 = new JLabel();
    JLabel lblColor = new JLabel();
    
    JTextField tfInput = new JTextField(3);
    
    JRadioButton rbtnRed = new JRadioButton("Red", false);
    JRadioButton rbtnBlue = new JRadioButton("Blue", false);
    JRadioButton rbtnGreen = new JRadioButton("Green", false);
    ButtonGroup group = new ButtonGroup();
    
    JButton btnCompute = new JButton();
    
    
    
    public int sumNums(int input)
    {
        int sum = 0;
        
        while(input != 0)
        {
            sum += input % 10;
            input /= 10;
        }
        
        return sum;
    }
    
    public String reverseNums(int input)
    {
        StringBuffer sb = new StringBuffer("");
        
        int rev = 0;
        
        while(input != 0)
        {
            rev = input % 10; //<---- reverse order
            input /= 10;
            sb.insert(0, rev);
        }
        
        return sb.reverse().toString();
    }
    
    public int[] getArray(int input)
    {
        int[] array = new int[3];
        
        String digits = Integer.toString(input);
        
        for(int i = 0; i < 3; i++)
        {
            int x = (int)digits.charAt(i) - 48;
            
            array[i] = x;
        }
        
        return array;
    }
    
    public Lvl2Assignment2()
    {
        this.setVisible(true);
        this.setSize(400, 300);
        this.setTitle("GUI Application and Inner Class");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        SpringLayout layout = new SpringLayout();
        content.setLayout(layout);
        
        
        
        lblInput.setText("Enter  3-Digit Number:");
        content.add(lblInput);
        layout.putConstraint(SpringLayout.WEST, lblInput, 10, SpringLayout.NORTH, content);
        layout.putConstraint(SpringLayout.NORTH, lblInput, 10, SpringLayout.NORTH, content);
        content.add(tfInput);
        layout.putConstraint(SpringLayout.EAST, tfInput, 215, SpringLayout.WEST, content);
        layout.putConstraint(SpringLayout.NORTH, tfInput, 10, SpringLayout.NORTH, content);
        
        lblSum.setText("Sum:");
        content.add(lblSum);
        layout.putConstraint(SpringLayout.WEST, lblSum, 10, SpringLayout.WEST, content);
        layout.putConstraint(SpringLayout.NORTH, lblSum, 20, SpringLayout.SOUTH, lblInput);
        content.add(lblSumNums);
        layout.putConstraint(SpringLayout.EAST, lblSumNums, 205, SpringLayout.WEST, content);
        layout.putConstraint(SpringLayout.NORTH, lblSumNums, 20, SpringLayout.SOUTH, lblInput);
        
        lblReverse.setText("Reverse:");
        content.add(lblReverse);
        layout.putConstraint(SpringLayout.WEST, lblReverse, 10, SpringLayout.WEST, content);
        layout.putConstraint(SpringLayout.NORTH, lblReverse, 20, SpringLayout.SOUTH, lblSum);
        content.add(lblReverseNums);
        layout.putConstraint(SpringLayout.EAST, lblReverseNums, 205, SpringLayout.WEST, content);
        layout.putConstraint(SpringLayout.NORTH, lblReverseNums, 20, SpringLayout.SOUTH, lblSum);
        
        
        
        lblArray.setText("Array:");
        content.add(lblArray);
        layout.putConstraint(SpringLayout.WEST, lblArray, 10, SpringLayout.WEST, content);
        layout.putConstraint(SpringLayout.NORTH, lblArray, 20, SpringLayout.SOUTH, lblReverse);
        
        content.add(lblArray1);
        layout.putConstraint(SpringLayout.WEST, lblArray1, 70, SpringLayout.EAST, lblArray);
        layout.putConstraint(SpringLayout.NORTH, lblArray1, 20, SpringLayout.SOUTH, lblReverse);
        
        content.add(lblArray2);
        layout.putConstraint(SpringLayout.WEST, lblArray2, 70, SpringLayout.EAST, lblArray1);
        layout.putConstraint(SpringLayout.NORTH, lblArray2, 20, SpringLayout.SOUTH, lblReverse);
        
        content.add(lblArray3);
        layout.putConstraint(SpringLayout.WEST, lblArray3, 70, SpringLayout.EAST, lblArray2);
        layout.putConstraint(SpringLayout.NORTH, lblArray3, 20, SpringLayout.SOUTH, lblReverse);
        
        
        
        lblColor.setText("Text Color:");
        content.add(lblColor);
        layout.putConstraint(SpringLayout.WEST, lblColor, 10, SpringLayout.WEST, content);
        layout.putConstraint(SpringLayout.NORTH, lblColor, 20, SpringLayout.SOUTH, lblArray);
        
        content.add(rbtnRed);
        layout.putConstraint(SpringLayout.EAST, rbtnRed, 70, SpringLayout.EAST, lblColor);
        layout.putConstraint(SpringLayout.NORTH, rbtnRed, 20, SpringLayout.SOUTH, lblArray);
        rbtnRed.addActionListener(new Radio());
        
        content.add(rbtnBlue);
        layout.putConstraint(SpringLayout.EAST, rbtnBlue, 80, SpringLayout.EAST, rbtnRed);
        layout.putConstraint(SpringLayout.NORTH, rbtnBlue, 20, SpringLayout.SOUTH, lblArray);
        rbtnBlue.addActionListener(new Radio());
        
        content.add(rbtnGreen);
        layout.putConstraint(SpringLayout.EAST, rbtnGreen, 80, SpringLayout.EAST, rbtnBlue);
        layout.putConstraint(SpringLayout.NORTH, rbtnGreen, 20, SpringLayout.SOUTH, lblArray);
        rbtnGreen.addActionListener(new Radio());
        
        
        
        btnCompute.setText("Compute");
        content.add(btnCompute);
        layout.putConstraint(SpringLayout.WEST, btnCompute, 150, SpringLayout.WEST, content);
        layout.putConstraint(SpringLayout.NORTH, btnCompute, 200, SpringLayout.NORTH, content);
        btnCompute.addActionListener(new Compute()); 
        
        
    }
    
    private class Radio implements ActionListener
    {
        public void actionPerformed(ActionEvent ae) 
        {
            JRadioButton rbtn = (JRadioButton) ae.getSource();
            
            if(rbtn == rbtnRed)
            {
                rbtnRed.setSelected(true);
                
                if(rbtnRed.isSelected() == true)
                {
                    lblSumNums.setForeground(Color.RED);
                    lblReverseNums.setForeground(Color.RED);
                    lblArray1.setForeground(Color.RED);
                    lblArray2.setForeground(Color.RED);
                    lblArray3.setForeground(Color.RED);
                }
            
            }
            else if(rbtn == rbtnBlue)
            {
                rbtnBlue.setSelected(true);
            
                if(rbtnBlue.isSelected() == true)
                {
                    lblSumNums.setForeground(Color.BLUE);
                    lblReverseNums.setForeground(Color.BLUE);
                    lblArray1.setForeground(Color.BLUE);
                    lblArray2.setForeground(Color.BLUE);
                    lblArray3.setForeground(Color.BLUE);
                }
            
            }
            else if(rbtn == rbtnGreen)
            {
                rbtnGreen.setSelected(true);
            
                if(rbtnGreen.isSelected() == true)
                {
                    lblSumNums.setForeground(Color.GREEN);
                    lblReverseNums.setForeground(Color.GREEN);
                    lblArray1.setForeground(Color.GREEN);
                    lblArray2.setForeground(Color.GREEN);
                    lblArray3.setForeground(Color.GREEN); 
                }
            
            }
            
        }
    }
        
    private class Compute implements ActionListener
    {
        public void actionPerformed(ActionEvent ae) 
        {
            Lvl2Assignment2 con = new Lvl2Assignment2();
            
            int sum;
            String str1, str2, str3;
            String num;
            
            String str = tfInput.getText();
            int digit = Integer.parseInt(str);
            sum = con.sumNums(digit);
            num = "" + sum;
            lblSumNums.setText(num);
            lblReverseNums.setText(con.reverseNums(digit));
            int arr[] = con.getArray(digit);
            
            str1 = "" + arr[0];
            str2 = "" + arr[1];
            str3 = "" + arr[2];
            
            lblArray1.setText(str1);
            lblArray2.setText(str2);
            lblArray3.setText(str3);
       
        }
    }
    
    /*
    public void actionPerformed(ActionEvent ae) 
    {
        JRadioButton rbtn = (JRadioButton) ae.getSource();
        JButton btn = (JButton) ae.getSource();
        Lvl2Assignment2 con = new Lvl2Assignment2();
        
        int sum;
        String str1, str2, str3;
        
        
        
        if(rbtn == rbtnRed)
        {
            rbtnRed.setSelected(true);
            //rbtnBlue.setSelected(false);
            //rbtnGreen.setSelected(false);
            //if(rbtnRed == true)
            if(rbtnRed.isSelected() == true)
            {
                lblSumNums.setForeground(Color.RED);
                lblReverseNums.setForeground(Color.RED);
                lblArray1.setForeground(Color.RED);
                lblArray2.setForeground(Color.RED);
                lblArray3.setForeground(Color.RED);
            }
            
        }
        else if(rbtn == rbtnBlue)
        {
            rbtnBlue.setSelected(true);
            //rbtnRed.setSelected(false);
            //rbtnGreen.setSelected(false);
            
            if(rbtnBlue.isSelected() == true)
            {
                lblSumNums.setForeground(Color.BLUE);
                lblReverseNums.setForeground(Color.BLUE);
                lblArray1.setForeground(Color.BLUE);
                lblArray2.setForeground(Color.BLUE);
                lblArray3.setForeground(Color.BLUE);
            }
            
        }
        else if(rbtn == rbtnGreen)
        {
            rbtnGreen.setSelected(true);
            //rbtnRed.setSelected(false);
            //rbtnBlue.setSelected(false);
            
            if(rbtnGreen.isSelected() == true)
            {
               lblSumNums.setForeground(Color.GREEN);
               lblReverseNums.setForeground(Color.GREEN);
               lblArray1.setForeground(Color.GREEN);
               lblArray2.setForeground(Color.GREEN);
               lblArray3.setForeground(Color.GREEN); 
            }
            
        }
        
        if(btn == btnCompute)
        {
            String str = tfInput.getText();
            int digit = Integer.parseInt(str);
            sum = con.sumNums(digit);
            lblSumNums.setText(con.reverseNums(digit));
            int arr[] = con.getArray(digit);
            
            str1 = "" + arr[0];
            str2 = "" + arr[1];
            str3 = "" + arr[2];
            
            lblArray1.setText(str1);
            lblArray2.setText(str2);
            lblArray3.setText(str3);
            
        }
    }
    */
    
    public void mouseClicked(MouseEvent me)
    {
        
    }
    
    public void mousePressed(MouseEvent me) 
    {
        
    }

    public void mouseReleased(MouseEvent me) 
    {
        
    }

    public void mouseEntered(MouseEvent me) 
    {
        
    }

    public void mouseExited(MouseEvent me) 
    {
        
    }
    
    public static void main(String[] args) 
    {

        Lvl2Assignment2 con = new Lvl2Assignment2();      
        
    }
    
}
