/*
Daniel Meyer
0405182
9-29-15
Assignment 7
Execptions
 */
package lvl.pkg2.assignment.pkg7;

import java.lang.Throwable;

public class IntMetricsException extends Throwable
{
    private String errorMsg;
    
    public IntMetricsException(String message)
    {
        this.errorMsg = message;
    }
    
    public String getErrorMsg()
    {
        return this.errorMsg;
    }
}
