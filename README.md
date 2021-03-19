# OpenGL
trying to learn opengl with c++

Learned openGL watching the Cherno youtube channel.

Do not know how to use cmake or premake yet

wasd keys to move and rotate

space bar to launch rocket

to compile:

	Preprocessor definitions:
		GLEW_STATIC
		WIN_32

	Include directories:
		src\vendor
		$(SolutionDir)dependencies\glw\include
		$(SolutionDir)dependencies\glew\include

	Library directories:
		$(SolutionDir)dependencies\glw\lib-vc2019
		$(SolutionDir)dependencies\glew\lib\Release\Win32

	Libraries:
		glfw3.lib
		opengl32.lib
		user32.lib
		gdi32.lib
		shell32.lib
		glew32s.lib

