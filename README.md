# DZGEngine
2D Renderine(possible game) engine in C++ written using VulkanAPI 
Disclaimer : Windows only!

Used libraries:
    GLM (mathematics)
    GLFW (windowing and input library)
    STB_Image ( Image loading library)

Setup to run the project:

1) Download VulkanSDK https://vulkan.lunarg.com/sdk/home#windows
Select these components during installation:
    ![image](https://github.com/zemi-taj-fromaz/DZGEngine/assets/99961022/433e455f-aa3c-4731-899d-607608e973b4)

        To confirm the installation -> open the Bin folder in the installation directory and run vkcube.exe
        If you see an image like this it means it went well:
    ![image](https://github.com/zemi-taj-fromaz/DZGEngine/assets/99961022/715b30e3-2b17-41a5-b0b9-a9e68ad9abfb)

    
2) Download GLFW https://www.glfw.org/download.html

        Download precompiled binaries

3) Add appropriate directories to "<AdditionalLibraryDirectories>" under project properties in Visual Studio
    ![Snimka zaslona 2024-06-22 175139](https://github.com/zemi-taj-fromaz/STCEngine/assets/99961022/5c8f3b8d-a492-4db1-a627-8d6d38be876e)



4) Add appropriate directories to "<AdditionalIncludeDirectories>" under project properties in Visual Studio
![Snimka zaslona 2024-06-22 175426](https://github.com/zemi-taj-fromaz/STCEngine/assets/99961022/eb75fe87-a005-4e9a-b3fe-a0189d9e1a5e)

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



