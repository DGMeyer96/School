/*
Daniel Meyer
0405182
9-23-15
Assignment 6
Static Classes and Scroll Bars
 */
package lvl2.assignment.pkg6;

import java.util.Random;
import java.awt.event.*;
import java.awt.*;
import javax.swing.*;

public class Lvl2Assignment6 extends JFrame
{

    Container content = this.getContentPane();
    
    JTextArea tfArea = new JTextArea();
    
    JButton compute = new JButton("Compute");
    
    JLabel lblMean = new JLabel("Mean: \t");
    JLabel lblMedian = new JLabel("Median: \t");
    JLabel lblMin = new JLabel("Min: \t");
    JLabel lblMax = new JLabel("Max: \t");
    JLabel lblSum = new JLabel("Sum: \t");
    
    private static int[] ar = new int[50];
    
    public void fillArray()
    {
        Random rdm = new Random();
        
        for(int i = 0; i < 50; i++)
        {
            ar[i] = rdm.nextInt((50 - 1) + 1) + 1;
        }
    }
    
    public void printArray()
    {
        for(int i= 0; i < 50 ; i++)
        {
            tfArea.append(ar[i] + "\n");
        }
    }   
    
    private class btnClass implements ActionListener
    {
        public void actionPerformed(ActionEvent ae) 
        {
            tfArea.setText("");
            fillArray();
            printArray();
            lblMean.setText("Mean: \t" + Double.toString(ArrayMetrics.mean(ar)));
            lblMax.setText("Max: \t" + Integer.toString(ArrayMetrics.max(ar)));
            lblMin.setText("Min: \t" + Integer.toString(ArrayMetrics.min(ar)));
            lblSum.setText("Sum: \t" + Integer.toString(ArrayMetrics.sum(ar)));
            lblMedian.setText("Median: \t" + Integer.toString(ArrayMetrics.median(ar)));  
        }
    }
    
    public Lvl2Assignment6()
    {
        this.setTitle("Static Class");
        this.setVisible(true);
        this.setSize(400,300);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        SpringLayout layout = new SpringLayout();
        content.setLayout(layout);

        content.add(tfArea);
        layout.putConstraint(SpringLayout.WEST, tfArea, 15, SpringLayout.NORTH, content);
        layout.putConstraint(SpringLayout.NORTH, tfArea, 5, SpringLayout.NORTH, content);
        tfArea.setEditable(false);
        JScrollPane scroll = new JScrollPane(tfArea, 
            JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, 
            JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        scroll.setPreferredSize(new Dimension(110,130));
        content.add(scroll);
        
        content.add(lblMean);
        layout.putConstraint(SpringLayout.WEST, lblMean, 135, SpringLayout.NORTH, content);
        layout.putConstraint(SpringLayout.NORTH, lblMean, 10, SpringLayout.NORTH, content);
        
        content.add(lblMedian);
        layout.putConstraint(SpringLayout.WEST, lblMedian, 135, SpringLayout.NORTH, content);
        layout.putConstraint(SpringLayout.NORTH, lblMedian, 25, SpringLayout.NORTH, lblMean);
        
        content.add(lblMin);
        layout.putConstraint(SpringLayout.WEST, lblMin, 135, SpringLayout.NORTH, content);
        layout.putConstraint(SpringLayout.NORTH, lblMin, 25, SpringLayout.NORTH, lblMedian);
        
        content.add(lblMax);
        layout.putConstraint(SpringLayout.WEST, lblMax, 135, SpringLayout.NORTH, content);
        layout.putConstraint(SpringLayout.NORTH, lblMax, 25, SpringLayout.NORTH, lblMin);
        
        content.add(lblSum);
        layout.putConstraint(SpringLayout.WEST, lblSum, 135, SpringLayout.NORTH, content);
        layout.putConstraint(SpringLayout.NORTH, lblSum, 25, SpringLayout.NORTH, lblMax);

        content.add(compute);
        compute.addActionListener(new btnClass());
        layout.putConstraint(SpringLayout.WEST, compute, 275, SpringLayout.WEST, content);
        layout.putConstraint(SpringLayout.NORTH, compute, 60, SpringLayout.NORTH, content);
        
    }
    
    public static void main(String[] args) 
    {
        Lvl2Assignment6 con = new Lvl2Assignment6();
    }
    
}
