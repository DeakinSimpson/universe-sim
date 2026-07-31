public class App
{
    private bool isRunning;

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

    private void Initiaise()
    {
        isRunning = true;
    }

    private void Update()
    {
        Console.WriteLine("Hello World");
    }

    private void Shutdown()
    {
        // cleanup
    }
}