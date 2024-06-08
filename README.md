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

    #1 Download VulkanSDK https://vulkan.lunarg.com/sdk/home#windows
        Select these components during installation:

        ![image](https://github.com/zemi-taj-fromaz/DZGEngine/assets/99961022/c84c5149-f67c-497e-b561-881cb6a8ce99)![vrp](https://github.com/zemi-taj-fromaz/DZGEngine/assets/99961022/842e7468-981c-412c-8e78-9d5c4ac5a813)


        
        ![image](https://github.com/zemi-taj-fromaz/DZGEngine/assets/99961022/6fc34042-e5fa-46d2-98f8-3d7540e21831)


        To confirm the installation -> open the Bin folder in the installation directory and run vkcube.exe
        If you see an image like this it means it went well:
        ![alt text](image-1.png)![image-1](https://github.com/zemi-taj-fromaz/DZGEngine/assets/99961022/59990a03-5a97-438a-9ac5-744a5c94dd11)

    
    #2 Download GLFW https://www.glfw.org/download.html

        Download precompiled binaries

    #3 Add appropriate directories to C++->General->"Additional include directiories" under project properties in Visual Studio
        ![alt text](image-2.png)
    ![image-2](https://github.com/zemi-taj-fromaz/DZGEngine/assets/99961022/886fe805-653e-45bd-99d9-cdc808bc30c6)

    #4 Add appropriate paths to Linker->General->Additional Library directories
        ![alt text](image-3.png)
    ![image-3](https://github.com/zemi-taj-fromaz/DZGEngine/assets/99961022/7ca94725-a4d1-4e67-aeea-d4e094ea55c3)

    #5 Set proper path
        
        In "resources/compile.bat" set a proper to glslc.exe for shader compilation

        example: set "glslcPath=C:\VulkanSDK\1.3.283.0\Bin\glslc.exe"


