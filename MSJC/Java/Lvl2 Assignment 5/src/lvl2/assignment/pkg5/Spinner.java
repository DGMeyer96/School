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

public class Spinner extends JPanel implements AdjustmentListener
{

    //JPanel layout = new JPanel(new BorderLayout());
    
    private JScrollBar theBar = new JScrollBar();
    private JLabel theLabel = new JLabel("    ", JLabel.RIGHT);
    
    public Spinner()
    {
        this(1, 1, 10, null);
    }
    
    public Spinner(int value, int min, int max)
    {
        this(value, min, max, null);
    }
    
    public Spinner(int value, int min, int max, AdjustmentListener listener)
    {
        
        theBar.setOrientation(JScrollBar.VERTICAL);
        theBar.setValues(max - value + min, 1, min, max - 1);
        
        theBar.setValue(max - value + min);
        theBar.setMinimum(min);
        theBar.setMaximum(max - 1);
        
        theBar.addAdjustmentListener(this);
        if(listener == null)
        {
            theBar.addAdjustmentListener(listener);
        }
        
        Font fnt = new Font("monospaced", Font.BOLD, 12);
        theLabel.setFont(fnt);
        
        JPanel layout = new JPanel(new BorderLayout());
        layout.add(theLabel, BorderLayout.CENTER);
        layout.add(theBar, BorderLayout.EAST);
        
        setValue();
        getPreferredSize();
        getValue();
        
    }
    
    
    
    public int getValue()
    {
        int max;
        int min;
        int value;
        int current;
        
        max = theBar.getMaximum();
        min = theBar.getMinimum();
        value = theBar.getValue();
        
        current = (max - 1) - value + min;
        
        return current;
    }
    
    public void setValue()
    {
        int max;
        int min;
        int value;
        int current;
        
        max = theBar.getMaximum();
        min = theBar.getMinimum();
        value = theBar.getValue();
        
        current = (max - 1) - value + min;
        
        theBar.setValue(current);
        
        theLabel.setText("" + getValue() + "");
    }
    
    public void Value(int num)
    {
        theBar.setUnitIncrement(num);
    }
    
    public void adjustmentValueChanged(AdjustmentEvent adjust)
    {
        theLabel.setText("" + getValue() + "");
    }
    
    public Dimension getPreferredSize() 
    { 
        return new Dimension(theBar.getPreferredSize().width + 
                   theLabel.getPreferredSize().width, 
                   theLabel.getPreferredSize().height); 
    }
    
}
