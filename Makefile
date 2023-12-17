program:
	clang++ project.cpp ../DrawingProject/location.cpp ../DrawingProject/colour.cpp ../DrawingProject/area.cpp ../DrawingProject/button.cpp ../DrawingProject/window.cpp ../DrawingProject/log.cpp ../DrawingProject/image.cpp -lSDL2 -lSDL2_image -Wno-writable-strings -Wno-switch -Wno-sizeof-pointer-div -Wno-return-stack-address
	./a.out