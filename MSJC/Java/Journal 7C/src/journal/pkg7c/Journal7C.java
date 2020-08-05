/*
Daniel Meyer
0405182
12-6-14
Journal 7C
JCheckBoxes
 */
package journal.pkg7c;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Journal7C extends JFrame implements ItemListener
{

    Container content = this.getContentPane();
    
    JCheckBox chkApples = new JCheckBox("Apples");
    JCheckBox chkOranges = new JCheckBox("Oranges");
    JCheckBox chkGrapes = new JCheckBox("Grapes");
    JCheckBox chkPeaches = new JCheckBox("Peaches");
    JLabel lblOutput = new JLabel(" ");
    JPanel pnl = new JPanel();
    
    public Journal7C()
    {
        this.setVisible(true);
        this.setSize(400,300);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("Using JCheckBoxes App");
        
        pnl.setLayout(new GridLayout(3,1, 5,5));
        pnl.add(chkApples);
        pnl.add(chkOranges);
        pnl.add(chkGrapes);
        pnl.add(chkPeaches);
        
        content.add(pnl, BorderLayout.SOUTH);
        content.add(lblOutput, BorderLayout.NORTH);
        
        chkApples.addItemListener(this);
        chkOranges.addItemListener(this);
        chkGrapes.addItemListener(this);
        chkPeaches.addItemListener(this);
        
    }
    
    public void itemStateChanged(ItemEvent ie) 
    {
        JCheckBox chk = (JCheckBox) ie.getSource();
        if(chk == chkApples)
        {
            if(chk.isSelected())
                lblOutput.setText("Apples Selected");
        }
        
        if(chk == chkOranges)
        {
            if(chk.isSelected())
                lblOutput.setText("Oranges Selected");
        }
        
        if(chk == chkGrapes)
        {
            if(chk.isSelected())
                lblOutput.setText("Grapes Selected");
        }
        
        if(chk == chkPeaches)
        {
            if(chk.isSelected())
                lblOutput.setText("Peaches Selected");
        }
    }
    
    public static void main(String[] args) 
    {
        Journal7C gui = new Journal7C();
    }
    
}
