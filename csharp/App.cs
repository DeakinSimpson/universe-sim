public class App
{
    private bool isRunning;

    // add basic run loop
    public void Run()
    {
        Initiaise();

        while (isRunning)
        {
            Update();

            isRunning = false;
        }

        Shutdown();
    }

    // set initialisation variables
    private void Initiaise()
    {
        isRunning = true;
        WindowObj windowObj = new WindowObj();
    }

    // what gets updated each frame
    private void Update()
    {
        Console.WriteLine("Hello World");
    }

    // cleanup
    private void Shutdown()
    {
        
    }
}