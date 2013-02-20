#pragma once

class Utils {
	static inline int random(int min, int max)
	{	
		return (int)((max - min) * rand()/(float)RAND_MAX + min);
	}
};
