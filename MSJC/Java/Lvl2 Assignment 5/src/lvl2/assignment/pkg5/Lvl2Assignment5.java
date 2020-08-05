/*
Daniel Meyer
0405182
9-14-15
Assignment 5
Object Construction and Composition
 */
package lvl2.assignment.pkg5;

import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

public class Lvl2Assignment5 extends JFrame implements AdjustmentListener, ActionListener
{

    Container content = this.getContentPane();
    
    public Lvl2Assignment5()
    {
        //Spinner spin = new Spinner();
        content.setLayout(new FlowLayout());
        this.setSize(400, 300);
        this.setVisible(true);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("Test Spinner");
        
        content.add(new Spinner(5, 1, 10, null));
        content.add(new Spinner(1, -5, 5, null));
        
        //JPanel p = new JPanel();
    }
    
    public void actionPerformed(ActionEvent ae) 
    {
        
    }
    
    public void adjustmentValueChanged(AdjustmentEvent ae) 
    {
        
    }
    
    public static void main(String[] args) 
    {
        Lvl2Assignment5 con = new Lvl2Assignment5();
        Spinner p = new Spinner();
    }  

}
