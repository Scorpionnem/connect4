/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 08:55:37 by mbatty            #+#    #+#             */
/*   Updated: 2025/11/06 11:53:46 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"
#include "Board.hpp"
#include "HumanPlayer.hpp"

/*
	6 height
	7 width

	x x x x x x x
	x x x x x x x
	x x x x x x x
	x x x x x x x
	x x x x x x x
	x x x x x x x
*/

# include "Window.hpp"
Window	window;
Game	game;

void	Game::loop()
{
	window.resetImg();
	_board.print();

	if (_player == 0)
	{
		_action = _player1->play();
		if (_action != -1 && _board.getY(_action) != -1)
		{
			_board.set(Board::Player::PLAYER1, _action);
			_player = 1;
		}
	}
	else if (_player == 1)
	{
		_action = _player2->play();
		if (_action != -1 && _board.getY(_action) != -1)
		{
			_board.set(Board::Player::PLAYER2, _action);
			_player = 0;
		}
	}

	window.renderImg();
	window.mouseX = 0;
	window.mouseY = 0;
	window.mouseClick = 0;
}

int	Window::closeHook()
{
	mlx_loop_end(window.getMLX());
	return (0);
}

int	Window::loopHook()
{
	game.loop();
	return (0);
}

int	main(void)
{
	game.run();

	window.open();

	window.close();
}
