/*
Daniel Meyer
0405182
9-9-15 
Assignent 4
Constructors
 */
package lvl2.assignment.pkg4;

import java.util.Scanner;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Lvl2Assignment4 extends JFrame implements ActionListener
{
    
    Container content = this.getContentPane();
    
    StrMetric sMetric = new StrMetric();
    
    JButton run = new JButton("Run");
    
    JTextField tf = new JTextField(50);
    JLabel lblTf = new JLabel("Enter a sentence:");
    
    JLabel lblInfo = new JLabel("Here's some information about your string");
    JLabel lblASCII = new JLabel("ASCII Sum:");
    JLabel lblSum = new JLabel();
    JLabel lblVowels = new JLabel("Number of Vowels:");
    JLabel lblNumVowels = new JLabel();
    JLabel lblDigits = new JLabel("Number of Digits:");
    JLabel lblNumDigits = new JLabel();
    JLabel lblUpper = new JLabel("Uppercase Letters:");
    JLabel lblNumUpper = new JLabel();
    JLabel lblLower = new JLabel("Lowercase Letters:");
    JLabel lblNumLower = new JLabel();
    
    public Lvl2Assignment4()
    {
        this.setVisible(true);
        this.setSize(400,300);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("Lab 4 - Constructors");
        //run.addActionListener(this);
        SpringLayout layout = new SpringLayout();
        content.setLayout(layout);
        
        content.add(lblTf);
        layout.putConstraint(SpringLayout.WEST, lblTf, 15, SpringLayout.NORTH, content);
        layout.putConstraint(SpringLayout.NORTH, lblTf, 5, SpringLayout.NORTH, content);
        
        content.add(tf);
        layout.putConstraint(SpringLayout.WEST, tf, 20, SpringLayout.EAST, lblTf);
        layout.putConstraint(SpringLayout.NORTH, tf, 5, SpringLayout.NORTH, content);
        
        content.add(lblInfo);
        layout.putConstraint(SpringLayout.WEST, lblInfo, 5, SpringLayout.NORTH, content);
        layout.putConstraint(SpringLayout.NORTH, lblInfo, 30, SpringLayout.NORTH, lblTf);
        
        content.add(lblASCII);
        layout.putConstraint(SpringLayout.WEST, lblASCII, 5, SpringLayout.NORTH, content);
        layout.putConstraint(SpringLayout.NORTH, lblASCII, 20, SpringLayout.NORTH, lblInfo);
        content.add(lblSum);
        layout.putConstraint(SpringLayout.WEST, lblSum, 200, SpringLayout.WEST, content);
        layout.putConstraint(SpringLayout.NORTH, lblSum, 20, SpringLayout.NORTH, lblInfo);
        //lblSum.setText("test");
        
        content.add(lblVowels);
        layout.putConstraint(SpringLayout.WEST, lblVowels, 5, SpringLayout.NORTH, content);
        layout.putConstraint(SpringLayout.NORTH, lblVowels, 20, SpringLayout.NORTH, lblASCII); 
        content.add(lblNumVowels);
        layout.putConstraint(SpringLayout.WEST, lblNumVowels, 200, SpringLayout.WEST, content);
        layout.putConstraint(SpringLayout.NORTH, lblNumVowels, 20, SpringLayout.NORTH, lblASCII);
        //lblNumVowels.setText("test");
        
        content.add(lblDigits);
        layout.putConstraint(SpringLayout.WEST, lblDigits, 5, SpringLayout.NORTH, content);
        layout.putConstraint(SpringLayout.NORTH, lblDigits, 20, SpringLayout.NORTH, lblVowels); 
        content.add(lblNumDigits);
        layout.putConstraint(SpringLayout.WEST, lblNumDigits, 200, SpringLayout.WEST, content);
        layout.putConstraint(SpringLayout.NORTH, lblNumDigits, 20, SpringLayout.NORTH, lblVowels);
        //lblNumDigits.setText("test");
        
        content.add(lblUpper);
        layout.putConstraint(SpringLayout.WEST, lblUpper, 5, SpringLayout.NORTH, content);
        layout.putConstraint(SpringLayout.NORTH, lblUpper, 20, SpringLayout.NORTH, lblDigits); 
        content.add(lblNumUpper);
        layout.putConstraint(SpringLayout.WEST, lblNumUpper, 200, SpringLayout.WEST, content);
        layout.putConstraint(SpringLayout.NORTH, lblNumUpper, 20, SpringLayout.NORTH, lblDigits);
        //lblNumUpper.setText("test");
        
        content.add(lblLower);
        layout.putConstraint(SpringLayout.WEST, lblLower, 5, SpringLayout.NORTH, content);
        layout.putConstraint(SpringLayout.NORTH, lblLower, 20, SpringLayout.NORTH, lblUpper);
        content.add(lblNumLower);
        layout.putConstraint(SpringLayout.WEST, lblNumLower, 200, SpringLayout.WEST, content);
        layout.putConstraint(SpringLayout.NORTH, lblNumLower, 20, SpringLayout.NORTH, lblUpper);
        //lblNumLower.setText("test");
        
        content.add(run);
        layout.putConstraint(SpringLayout.WEST, run, 160, SpringLayout.NORTH, content);
        layout.putConstraint(SpringLayout.SOUTH, run, 0, SpringLayout.SOUTH, content);
        run.addActionListener(this);
    }
    
    public void actionPerformed(ActionEvent ae) 
    {
            String str = tf.getText();
            sMetric.setString(str);
            
            /*
            lblSum.setText("" + sMetric.getSumASCII(str));
            lblNumVowels.setText("" + sMetric.getNumVowels(str));
            lblNumDigits.setText("" + sMetric.getNumDigits(str));
            lblNumUpper.setText("" + sMetric.getNumUpperCase(str));
            lblNumLower.setText("" + sMetric.getLowerCaseDigit(str));    
            */
            
            
            
    }
    
    public static void main(String[] args) 
    {
        Lvl2Assignment4 con = new Lvl2Assignment4();
    }
    
}
