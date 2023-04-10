#include <random>
#include <iostream>

unsigned int getRandom(unsigned int m_z, unsigned int m_w) {
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

int main() {

	unsigned int a = random();
	unsigned int b = random();

	for (unsigned int i = 0; i < 100; i++) {
		std::cout << getRandom(a + 1, b + 1) << std::endl;
	}

	return 0;
}

