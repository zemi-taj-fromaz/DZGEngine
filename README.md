# DZGEngine
2D Renderine(possible game) engine in C++ written using VulkanAPI

Used libraries:
    GLM (mathematics)
    GLFW (windowing and input library)
    STB_Image ( Image loading library)
    Tiny Obj Loader (.obj loader library)
    VkBootstrap (boilerplate code abstraction)
    VMA (Vulkan memory allocator)

Setup to run the project:

1) Download VulkanSDK https://vulkan.lunarg.com/sdk/home#windows
Select these components during installation:
    ![image](https://github.com/zemi-taj-fromaz/DZGEngine/assets/99961022/433e455f-aa3c-4731-899d-607608e973b4)

        To confirm the installation -> open the Bin folder in the installation directory and run vkcube.exe
        If you see an image like this it means it went well:
    ![image](https://github.com/zemi-taj-fromaz/DZGEngine/assets/99961022/715b30e3-2b17-41a5-b0b9-a9e68ad9abfb)

    
2) Download GLFW https://www.glfw.org/download.html

        Download precompiled binaries

3) Add appropriate directories to C++->General->"Additional include directiories" under project properties in Visual Studio
        ![alt text](image-2.png)

4) Add appropriate paths to Linker->General->Additional Library directories
        ![alt text](image-3.png)

5) Set proper path
        
        In "resources/compile.bat" set a proper to glslc.exe for shader compilation. Run this script initially and after that -  in the case of initial shader adding

        example: set "glslcPath=C:\VulkanSDK\1.3.283.0\Bin\glslc.exe"

//----------------------------------------------------------------------------------------------------------------------------------

Currently developed scenes using this engine

# Tetri$

Enjoy the classic tetris experience enhanced by the sounds of Kuku$, Shegrt Hladnich (Tata Hladni) & Vuk Oreb
![image](https://github.com/zemi-taj-fromaz/DZGEngine/assets/99961022/88b69327-32a5-4540-8e63-d54dc31a9753)

# JetPug

A pug with a jetpack (flappy bird rip-off)
![image](https://github.com/zemi-taj-fromaz/DZGEngine/assets/99961022/e93c6b06-abe3-4b74-bc19-8303243d8aab)



