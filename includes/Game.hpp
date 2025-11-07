/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 08:57:09 by mbatty            #+#    #+#             */
/*   Updated: 2025/11/07 09:17:15 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include "Player.hpp"
# include "Board.hpp"

class	Game
{
	public:
		Game(){}
		~Game()
		{
			delete _player1;
			delete _player2;
		}

		void	run();
		void	loop();

		Board	&board() {return (_board);}
	private:
		
		int		_action;
		Player	*_player1;
		Player	*_player2;
		int	_player = 0;

		Board	_board;
};

# include "AIPlayer.hpp"
# include "HumanPlayer.hpp"

#endif
