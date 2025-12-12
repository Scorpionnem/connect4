/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanPlayer.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:59:47 by mbatty            #+#    #+#             */
/*   Updated: 2025/12/12 11:09:45 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANPLAYER_HPP
# define HUMANPLAYER_HPP

# include "Player.hpp"
# include "Board.hpp"
# include <string>
# include <iostream>

# include "Window.hpp"
extern Window window;

class	HumanPlayer : public Player
{
	public:
		HumanPlayer(){}
		~HumanPlayer(){}

		int	play(Board board, Board::Player you)
		{
			(void)you;(void)board;
			int	play = -1;

			if (window.mouseClick)
				play = 7 * ((float)window.mouseX / (float)Window::WIDTH);

			if (!Board::valid(play, 0))
				return (-1);
			return (play);
		}
};

#endif
