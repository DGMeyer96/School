/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lvl2.assignment.pkg5.test;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Lvl2Assignment5Test extends JFrame implements 
        AdjustmentListener, ActionListener
{

    Container content = this.getContentPane();
    
    JTextField tf = new JTextField(10);
    JLabel lbl = new JLabel("", JLabel.CENTER);
    
    Spinner sp1 = new Spinner();
    Spinner sp2 = new Spinner(1, -5, 5);
    Spinner sp3 = new Spinner(10, 5, 20, this);

    public Lvl2Assignment5Test()
    {
        content.setLayout(new FlowLayout()); 
        this.setSize(400, 300);                 
        this.setVisible(true);       
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
        this.setTitle("Test Spinner");
        content.add(lbl, "North");

        JPanel p = new JPanel();
        p.add(sp1);
        p.add(sp2);
        p.add(sp3);
        sp3.setStepValue(2);
        p.add(tf);
        content.add(p, "Center");
        tf.addActionListener(this);       
        
    }
    public void actionPerformed(ActionEvent ae)
    {
        String svalue = tf.getText();
        int value = Integer.parseInt(svalue);
        sp1.setStepValue(value);
        sp2.setStepValue(value);
        sp3.setStepValue(value);
    }

    public void adjustmentValueChanged(AdjustmentEvent ae)
    {
        lbl.setText("sp1=" + sp1.getValue() +
              ", sp2 = " + sp2.getValue() +
              ", sp3 = " + sp3.getValue());

       
    }

    
    public static void main(String[] args) 
    {
        Lvl2Assignment5Test l3 = new Lvl2Assignment5Test();
        Spinner p = new Spinner();
    }
}
