#ifndef UTILS_HPP

# define UTILS_HPP

# include <sys/time.h>
# include <sys/sysctl.h>
# include <unistd.h>
# include <sstream>

template<typename T>
int						use_sysctl(const char *name, T& data, size_t fixed = 0)
{
	size_t		size;

	if (fixed)
		size = fixed;
	else
		size = sizeof(T);
	return sysctlbyname(name, &data, &size, NULL, 0);
}

template<typename T>
std::string		number_to_string(T number)
{
	std::stringstream		ss;

	ss << number;
	return ss.str();
}

#endif
