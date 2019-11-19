/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Arguments.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 13:58:27 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/19 15:37:51 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGUMENTS_HPP
# define ARGUMENTS_HPP

# include <exception>

// temporary define to be replace with static attribute from lib class or main.
# define STARTINGLIB_MIN 0
# define STARTINGLIB_MAX 2
# define WIDTH_MAX 1600
# define WIDTH_MIN 640
# define HEIGHT_MAX 900
# define HEIGHT_MIN 480

class Arguments {
public:
	Arguments(int argc, char * argv[]);
	~Arguments(void);

	int				getStartingLib(void);
	int				getWidth(void);
	int				getHeight(void);

private:
	Arguments(void);
	Arguments(Arguments const & rhs);
	Arguments &		operator=(Arguments const & rhs) const;

	int				startingLib;
	int				width;
	int				height;

	void			initStartingLib(char * arg);
	void			initWidth(char * arg);
	void			initHeight(char * arg);

public:
	class 			InvalidArguments: public std::exception {
	public:
		InvalidArguments(void);
		InvalidArguments(InvalidArguments const & rhs);
		~InvalidArguments(void);

		virtual char const *	what(void) const throw();
	
	private:
		InvalidArguments &		operator=(InvalidArguments const & rhs) const;

		std::string				usage;
	};
};

#endif