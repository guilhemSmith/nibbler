/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Arguments.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 13:58:27 by gsmith            #+#    #+#             */
/*   Updated: 2020/03/05 13:49:44 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGUMENTS_HPP
# define ARGUMENTS_HPP

# include <exception>

// temporary define to be replace with static attribute from lib class or main.
# define STARTINGLIB_MIN 1
# define STARTINGLIB_MAX 3
# define WIDTH_MAX 40
# define WIDTH_MIN 15
# define HEIGHT_MAX 40
# define HEIGHT_MIN 15

class Arguments {
public:
	Arguments(void);
	~Arguments(void);

	void			init(int argc, char * argv[]);
	int				getStartingLib(void);
	int				getWidth(void);
	int				getHeight(void);

private:
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