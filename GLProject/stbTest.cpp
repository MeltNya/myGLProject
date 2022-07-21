#include<iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
using namespace std;
int main() {
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels; //通道数量
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	for (size_t i = 0; i < 50; i++)
	{
		cout << (int)data[i] << endl;
	}
	stbi_image_free(data);
	while (true)
	{

	}
	return 0;
}