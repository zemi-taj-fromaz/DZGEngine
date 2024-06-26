@echo off
setlocal

set "glslcPath=C:\VulkanSDK\1.3.283.0\Bin\glslc.exe"

echo "...compiling shaders"

rem Compile each shader with relative paths
"%glslcPath%" TriangleShader.vert -o TriangleShadervert.spv
"%glslcPath%" TriangleShader.frag -o TriangleShaderfrag.spv
"%glslcPath%" PillarShader.vert -o PillarShadervert.spv
"%glslcPath%" PillarShader.frag -o PillarShaderfrag.spv

echo "Compilation Done"

pause