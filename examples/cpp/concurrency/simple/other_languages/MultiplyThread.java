/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Java implementation of async.cpp (spawn a single
 * thread to perform an operation asynchronously).
 *
 * The MultiplyThread is a subclass of Thread,
 * and is run from class MultiplyThreadTest
 *
 */

public class MultiplyThread extends Thread
{
    private int a, b, result;

    public MultiplyThread(int a, int b)
    {
        this.a = a;
        this.b = b;
    }

    public void run()
    {
        this.result = this.a * this.b;

    }

    public int getResult()
    {
        return this.result;
    }
}
