/*
Daniel Meyer
0405182
11-27-14
Journal 7A
Event Preferences
 */
package journal.pkg7a;

import java.util.Scanner;
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class Journal7A extends JFrame implements ActionListener
{

    Container content = this.getContentPane();
    JButton btnGreen = new JButton("Green");
    JButton btnBlue = new JButton("Blue");
    JButton btnRed = new JButton("Red");
       
    public Journal7A()
    {
        content.setLayout(new FlowLayout());
        this.setVisible(true);
        this.setSize(300,300);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("First GUI App");
        content.add(btnBlue, BorderLayout.SOUTH);
        content.add(btnGreen, BorderLayout.SOUTH);
        content.add(btnRed, BorderLayout.SOUTH);
        btnBlue.addActionListener(this);
        btnGreen.addActionListener(this);
        btnRed.addActionListener(this);
    }
    
    public void actionPerformed(ActionEvent ae)
    {
        JButton btn = (JButton) ae.getSource();
        if(btn == btnBlue)
            content.setBackground(Color.BLUE);
        else if(btn == btnGreen)
            content.setBackground(Color.GREEN);
        else if(btn == btnRed)
            content.setBackground(Color.RED);
    }
    
    public static void main(String[] args) 
    {
        Journal7A gui = new Journal7A();
        
    }
    
}
