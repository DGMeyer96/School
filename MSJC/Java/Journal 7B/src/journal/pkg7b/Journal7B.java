/*
Daniel Meyer
0405182
12-6-14
Journal 7B
JPanels
 */
package journal.pkg7b;

import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
public class Journal7B extends JFrame
{

    Container content = this.getContentPane();
    
    JButton btnGreen = new JButton("Green");
    JButton btnBlue = new JButton("Blue");
    
    JTextField tfOne = new JTextField();
    JTextField tfTwo = new JTextField();
    JTextField tfThree = new JTextField();
    
    JPanel pnl = new JPanel();

    public Journal7B()
    {
        this.setVisible(true);
        this.setSize(400,300);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("Using JPanels App");
        /*
        pnl.setLayout(new GridLayout(1,2, 5,5));
        pnl.add(btnGreen);
        pnl.add(btnBlue);
        content.add(pnl, BorderLayout.SOUTH);
        */
        pnl.setLayout(new GridLayout(1,3));
        pnl.add(tfOne);
        pnl.add(tfTwo);
        pnl.add(tfThree);
        content.add(pnl, BorderLayout.NORTH);
        
    }
    
    
    public static void main(String[] args) 
    {
        Journal7B gui = new Journal7B();
    }
    
}
