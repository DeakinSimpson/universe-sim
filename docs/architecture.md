flowchart TD
    Program["Program.cs"] --> App["App.Run()"]

    App -->|creates| Window["IWindow"]
    App -->|creates| Camera["Camera"]
    App -->|creates| Controller["Controller(camera)"]

    App -->|"window.Load fires"| Load["Load handler"]
    Load -->|creates| Renderer["Renderer(window)"]
    Load -->|creates| Scene["Scene(renderer, camera, window)"]
    Load -->|"input.Keyboards[].KeyDown"| KeyDown["Escape / E toggle wireframe"]
    Load -->|"controller.onLoad(input)"| Controller

    Load -->|creates| Engine["Engine(window, updatables, renderables)"]
    Engine -->|"window.Update"| HandleUpdate["HandleUpdate(dt)"]
    Engine -->|"window.Render"| HandleRender["HandleRender(dt)"]

    HandleUpdate -->|"Update(dt)"| Controller
    HandleUpdate -->|"Update(dt)"| Scene
    Controller -->|"MoveForward / Strafe / Rotate / Zoom"| Camera

    HandleRender -->|"Render(dt)"| Scene
    Scene -->|"Render(...)"| SolarSystem["SolarSystem"]
    SolarSystem -->|"Render(...)"| Planet["Planet"]
    Planet -->|"renderObject(...)"| Renderer
    Renderer -->|"view/projection"| Camera

    App -->|"window.FramebufferResize"| Resize["renderer?.getGL().Viewport(...)"]