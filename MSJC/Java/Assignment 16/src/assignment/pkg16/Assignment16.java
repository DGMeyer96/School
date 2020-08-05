/*
Daniel Meyer
0405182
11-28-14
Assignment 16
JButtons and JText Fields
 */
package assignment.pkg16;

import java.util.Scanner;
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.text.NumberFormat;

public class Assignment16 extends JFrame implements ActionListener
{

    Container content = this.getContentPane();
    JTextField tfAmount = new JTextField();
    JTextField tfInterest = new JTextField();
    JTextField tfYears = new JTextField();
    JLabel lblPayment = new JLabel();
    JLabel lblTotalCost = new JLabel();
    JButton btnCalc = new JButton("Calculate");
    
    //JLabel lblPayment = new JLabel();
    //JLabel lblTotalCost = new JLabel();
    
    public Assignment16()
    {
        this.setVisible(true);
        this.setSize(400,300);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("First GUI App");
        content.setLayout(new GridLayout(0,2,5,5));
        
        JLabel amt = new JLabel("Amount Borrowed", JLabel.RIGHT);
        //amt.setHorizontalAlignment(JLabel.RIGHT);
        content.add(amt);
        content.add(tfAmount);
        
        JLabel interest = new JLabel("Interest Rate", JLabel.RIGHT);
        //interest.setHorizontalAlignment(JLabel.RIGHT);
        content.add(interest);
        content.add(tfInterest);
        
        JLabel years = new JLabel("Years to Pay", JLabel.RIGHT);
        //years.setHorizontalAlignment(JLabel.RIGHT);
        content.add(years);
        content.add(tfYears);
        
        
        JLabel payment = new JLabel("Monthly Payment", JLabel.RIGHT);
        //payment.setHorizontalAlignment(JLabel.RIGHT);
        content.add(payment);
        content.add(lblPayment);
        
        JLabel totalcost = new JLabel("Total Purchase Cost", JLabel.RIGHT);
        //totalcost.setHorizontalAlignment(JLabel.RIGHT);
        content.add(totalcost);
        content.add(lblTotalCost);
        
        
        /*
        content.add(lblMPayment);
        interest.setHorizontalAlignment(JLabel.RIGHT);
        
        content.add(lblFTotalCost);
        interest.setHorizontalAlignment(JLabel.RIGHT);
        */
        content.add(btnCalc);
        btnCalc.addActionListener(this);
        
    }
    
    public void actionPerformed(ActionEvent ae)
    {
        String amountStr = tfAmount.getText();
        String interestStr = tfInterest.getText();
        String yearsStr = tfYears.getText();
        
        Double amtDbl = new Double(amountStr);
        Double intDbl = new Double(interestStr);
        Double yrsDbl = new Double(yearsStr);
        
        double amount = amtDbl.doubleValue();
        double interest = intDbl.doubleValue();
        double years = yrsDbl.doubleValue();
        
        double actInt = (interest / 100) / 12;
        
        double payment = (amount * actInt) / (1 - (Math.pow(1 / (1 + actInt), years * 12)));
        
        String paymentStr = NumberFormat.getCurrencyInstance().format(payment);
        lblPayment.setText(paymentStr);
        
        double finalCost = (payment * 12) * years;
        
        String finalStr = NumberFormat.getCurrencyInstance().format(finalCost);
        lblTotalCost.setText(finalStr);
        
    }
    
    public static void main(String[] args) 
    {
        Assignment16 gui = new Assignment16();
    }
    
}
