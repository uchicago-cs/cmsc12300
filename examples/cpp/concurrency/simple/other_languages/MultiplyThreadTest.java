/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Java implementation of async.cpp (spawn a single
 * thread to perform an operation asynchronously).
 *
 * This is the class that creates a MultiplyThread
 * and waits for it to complete.
 *
 */

import java.lang.System;
import java.lang.InterruptedException;  

public class MultiplyThreadTest
{
    public static void main(String[] args)
    {
        MultiplyThread mt = new MultiplyThread(2, 3);

        mt.start();

        try {
		    mt.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
            System.exit(1);
        }

        System.out.println("The thread returned " + mt.getResult());        
   }
}
