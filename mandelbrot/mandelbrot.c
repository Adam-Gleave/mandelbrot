#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

// Dimensions and formula iterations
#define WIDTH 600
#define HEIGHT 600
#define MAX_ITER 16

GLFWwindow* glfw_init() {
    GLFWwindow* window;
    if (!window) {
    	printf("Window creation failed.");
    }

    glfwInit();
    window = glfwCreateWindow(WIDTH, HEIGHT, "Mandelbrot", NULL, NULL);
    glfwMakeContextCurrent(window);

    return window;
}

char* gen_pix() {
	// Pixel buffer pointer
	char* pix_map = malloc(3 * HEIGHT * WIDTH * sizeof(char));

	int row;

	for (row = 0; row < HEIGHT; row++) {
		int col;

		for (col = 0; col < WIDTH; col++) {
			// Map pixel co-ords to equation variables
			double c_real = (col - WIDTH / 2.0f) * 4.0f / WIDTH;
			double c_imag = (row - HEIGHT / 2.0f) * 4.0f / WIDTH;
			double x = 0;
			double y = 0;

			// Iteration counter
			int iteration = 0;

			// Subsitute into equation
			while (x*x + y*y <= 4 && iteration < MAX_ITER) {
				double x_new = x*x - y*y + c_real;
				y = 2*x*y + c_imag;
				x = x_new;

				// Increment iterations
				iteration++;
			}

			char* pix_data;

			// Color image
			if (iteration < MAX_ITER) {
				int div = MAX_ITER - iteration;
				snprintf(pix_map, 3, "%c%c%c", (int)(255 / div), 
					(int)(255 / (div * 0.5)), 
					128 - (int)(128 / div));
			}
			else {
				snprintf(pix_map, 3, "%c%c%c", 0, 0, 0);
			}

			pix_map += 3;
		}
	}

	return pix_map;
}

void main_loop(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {
    	double time = glfwGetTime();

    	glClear(GL_COLOR_BUFFER_BIT);
    	glfwSwapBuffers(window);
    	glfwSwapInterval(1);
    	glfwPollEvents();

    	gen_pix();
    }
}

int main() {
	GLFWwindow* window = glfw_init();
	main_loop(window);
    glfwTerminate();

    return 0;
}
