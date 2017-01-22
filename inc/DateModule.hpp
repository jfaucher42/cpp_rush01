#ifndef DATEMODULE_HPP

# define DATEMODULE_HPP

# include <AMonitorModule.hpp>
# include <ctime>
# include <sstream>

class DateModule: public AMonitorModule
{
	public:
		DateModule(void);
		virtual ~DateModule();

		virtual void	updateModule(void);

	private:
		DateModule(DateModule const&);
		DateModule&		operator=(DateModule const&);
};

#endif
